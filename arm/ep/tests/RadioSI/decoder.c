
#include <swilib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <spl/coreevent.h>
#include <math.h>
#include <neaacdec.h>
#include "audio.h"
#include "decoder.h"
#include "stream.h"


#ifndef min
#define min(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#define MAX_CHANNELS 6 /* make this higher to support files with
                          more channels */


static int quiet = 0;
void report_bug(const char *text);

static void faad_fprintf(FILE *stream, const char *fmt, ...)
{
    va_list ap;

    if (!quiet)
    {
        va_start(ap, fmt);

        vfprintf(stream, fmt, ap);

        va_end(ap);
    }
}

/* FAAD file buffering routines */
typedef struct {
    long bytes_into_buffer;
    long bytes_consumed;
    long file_offset;
    unsigned char *buffer;
    int at_eof;
    int infile;
} aac_buffer;




static int fill_buffer(aac_buffer *b)
{
    int bread;

    if (b->bytes_consumed > 0)
    {
        if (b->bytes_into_buffer)
        {
            memmove((void*)b->buffer, (void*)(b->buffer + b->bytes_consumed),
                b->bytes_into_buffer*sizeof(unsigned char));
        }

        if (!b->at_eof)
        {
            bread = read_stream((void*)(b->buffer + b->bytes_into_buffer),
                b->bytes_consumed);

            if (bread != b->bytes_consumed)
                b->at_eof = 1;

            b->bytes_into_buffer += bread;
        }

        b->bytes_consumed = 0;

        if (b->bytes_into_buffer > 3)
        {
            if (memcmp(b->buffer, "TAG", 3) == 0)
                b->bytes_into_buffer = 0;
        }
        if (b->bytes_into_buffer > 11)
        {
            if (memcmp(b->buffer, "LYRICSBEGIN", 11) == 0)
                b->bytes_into_buffer = 0;
        }
        if (b->bytes_into_buffer > 8)
        {
            if (memcmp(b->buffer, "APETAGEX", 8) == 0)
                b->bytes_into_buffer = 0;
        }
    }

    return 1;
}

static void advance_buffer(aac_buffer *b, int bytes)
{
    b->file_offset += bytes;
    b->bytes_consumed = bytes;
    b->bytes_into_buffer -= bytes;
	if (b->bytes_into_buffer < 0)
		b->bytes_into_buffer = 0;
}

static int adts_sample_rates[] = {96000,88200,64000,48000,44100,32000,24000,22050,16000,12000,11025,8000,7350,0,0,0};

static int adts_parse(aac_buffer *b, int *bitrate, float *length)
{
    int frames, frame_length;
    int t_framelength = 0;
    int samplerate;
    float frames_per_sec, bytes_per_frame;

    /* Read all frames to ensure correct time and bitrate */
    for (frames = 0; /* */; frames++)
    {
        fill_buffer(b);

        if (b->bytes_into_buffer > 7)
        {
            /* check syncword */
            if (!((b->buffer[0] == 0xFF)&&((b->buffer[1] & 0xF6) == 0xF0)))
                break;

            if (frames == 0)
                samplerate = adts_sample_rates[(b->buffer[2]&0x3c)>>2];

            frame_length = ((((unsigned int)b->buffer[3] & 0x3)) << 11)
                | (((unsigned int)b->buffer[4]) << 3) | (b->buffer[5] >> 5);

            t_framelength += frame_length;

            if (frame_length > b->bytes_into_buffer)
                break;

            advance_buffer(b, frame_length);
        } else {
            break;
        }
    }

    frames_per_sec = (float)samplerate/1024.0f;
    if (frames != 0)
        bytes_per_frame = (float)t_framelength/(float)(frames*1000);
    else
        bytes_per_frame = 0;
    *bitrate = (int)(8. * bytes_per_frame * frames_per_sec + 0.5);
    if (frames_per_sec != 0)
        *length = (float)frames/frames_per_sec;
    else
        *length = 1;

    return 1;
}



uint32_t read_callback(void *user_data, void *buffer, uint32_t length)
{
    return fread(buffer, 1, length, (FILE*)user_data);
}

uint32_t seek_callback(void *user_data, uint64_t position)
{
    return fseek((FILE*)user_data, position, SEEK_SET);
}

/* MicroSoft channel definitions */
#define SPEAKER_FRONT_LEFT             0x1
#define SPEAKER_FRONT_RIGHT            0x2
#define SPEAKER_FRONT_CENTER           0x4
#define SPEAKER_LOW_FREQUENCY          0x8
#define SPEAKER_BACK_LEFT              0x10
#define SPEAKER_BACK_RIGHT             0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER   0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER  0x80
#define SPEAKER_BACK_CENTER            0x100
#define SPEAKER_SIDE_LEFT              0x200
#define SPEAKER_SIDE_RIGHT             0x400
#define SPEAKER_TOP_CENTER             0x800
#define SPEAKER_TOP_FRONT_LEFT         0x1000
#define SPEAKER_TOP_FRONT_CENTER       0x2000
#define SPEAKER_TOP_FRONT_RIGHT        0x4000
#define SPEAKER_TOP_BACK_LEFT          0x8000
#define SPEAKER_TOP_BACK_CENTER        0x10000
#define SPEAKER_TOP_BACK_RIGHT         0x20000
#define SPEAKER_RESERVED               0x80000000

static long aacChannelConfig2wavexChannelMask(NeAACDecFrameInfo *hInfo)
{
    if (hInfo->channels == 6 && hInfo->num_lfe_channels)
    {
        return SPEAKER_FRONT_LEFT + SPEAKER_FRONT_RIGHT +
            SPEAKER_FRONT_CENTER + SPEAKER_LOW_FREQUENCY +
            SPEAKER_BACK_LEFT + SPEAKER_BACK_RIGHT;
    } else {
        return 0;
    }
}

static char *position2string(int position)
{
    switch (position)
    {
    case FRONT_CHANNEL_CENTER: return "Center front";
    case FRONT_CHANNEL_LEFT:   return "Left front";
    case FRONT_CHANNEL_RIGHT:  return "Right front";
    case SIDE_CHANNEL_LEFT:    return "Left side";
    case SIDE_CHANNEL_RIGHT:   return "Right side";
    case BACK_CHANNEL_LEFT:    return "Left back";
    case BACK_CHANNEL_RIGHT:   return "Right back";
    case BACK_CHANNEL_CENTER:  return "Center back";
    case LFE_CHANNEL:          return "LFE";
    case UNKNOWN_CHANNEL:      return "Unknown";
    default: return "";
    }

    return "";
}


static int FindAdtsSRIndex(int sr)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        if (sr == adts_sample_rates[i])
            return i;
    }
    return 16 - 1;
}



int tagsize;
unsigned long samplerate = 0;
unsigned char channels = 0;
void *sample_buffer;


FILE *adtsFile;
unsigned char *adtsData;
int adtsDataSize;

NeAACDecHandle hDecoder = 0;
NeAACDecFrameInfo frameInfo;
NeAACDecConfigurationPtr config;

char percents[200];
int percent, old_percent = -1;
int bread, fileread;
int header_type = 0;
int bitrate = 0;
float length = 0;
int def_srate = 0;
int object_type = LC;
int outputFormat = FAAD_FMT_16BIT;
int downMatrix = 0;
int old_format = 0;
int channel_mask = 0;

int first_time = 1;
aac_buffer b;



void *get_aac_buffer_data(int *size)
{
    *size = b.bytes_into_buffer;
    return b.buffer;
}


int init_decoder(const char *file)
{
    memset(&b, 0, sizeof(aac_buffer));
    b.infile = -1;

    if(file[1] == ':')
        b.infile = open_stream(FS_STREAM, file);
    else
    {
        b.infile = open_stream(INET_STREAM, file);
    }

    if (b.infile < 0)
    {
        /* unable to open file */
        printf("Error opening file\n");
        return 1;
    }


    fileread = size_stream();

    if (!(b.buffer = (unsigned char*)malloc(FAAD_MIN_STREAMSIZE*MAX_CHANNELS+2)))
    {
        printf("Memory allocation error\n");
        return 0;
    }


    bread = read_stream(b.buffer, FAAD_MIN_STREAMSIZE*MAX_CHANNELS);
    b.bytes_into_buffer = bread;
    b.bytes_consumed = 0;
    b.file_offset = 0;

    if (bread != FAAD_MIN_STREAMSIZE*MAX_CHANNELS)
        b.at_eof = 1;

    tagsize = 0;
    if (!memcmp(b.buffer, "ID3", 3))
    {
        /* high bit is not used */
        tagsize = (b.buffer[6] << 21) | (b.buffer[7] << 14) |
                  (b.buffer[8] <<  7) | (b.buffer[9] <<  0);

        tagsize += 10;
        advance_buffer(&b, tagsize);
        fill_buffer(&b);
    }


    hDecoder = NeAACDecOpen();

    /* Set the default object type and samplerate */
    /* This is useful for RAW AAC files */
    config = NeAACDecGetCurrentConfiguration(hDecoder);
    if (def_srate)
        config->defSampleRate = def_srate;
    config->defObjectType = object_type;
    config->outputFormat = outputFormat;
    config->downMatrix = downMatrix;
    config->useOldADTSFormat = old_format;
    //config->dontUpSampleImplicitSBR = 1;
    NeAACDecSetConfiguration(hDecoder, config);



    /* get AAC infos for printing */
    header_type = 0;
    if ((b.buffer[0] == 0xFF) && ((b.buffer[1] & 0xF6) == 0xF0))
    {
        //adts_parse(&b, &bitrate, &length);

        // FIXME
        if(tagsize > FAAD_MIN_STREAMSIZE*MAX_CHANNELS)
        {
            bread = read_stream(b.buffer, FAAD_MIN_STREAMSIZE*MAX_CHANNELS);
        } else {
            advance_buffer(&b, tagsize);
            fill_buffer(&b);
            bread = FAAD_MIN_STREAMSIZE*MAX_CHANNELS;
        }

        //lseek(b.infile, tagsize, SEEK_SET);
        //bread = read(b.infile, b.buffer, FAAD_MIN_STREAMSIZE*MAX_CHANNELS);
        //seek_stream(tagsize, SEEK_SET);
        //read_stream(b.buffer, FAAD_MIN_STREAMSIZE*MAX_CHANNELS);


        if (bread != FAAD_MIN_STREAMSIZE*MAX_CHANNELS)
            b.at_eof = 1;
        else
            b.at_eof = 0;
        b.bytes_into_buffer = bread;
        b.bytes_consumed = 0;
        b.file_offset = tagsize;

        header_type = 1;
    } else if (memcmp(b.buffer, "ADIF", 4) == 0) {
        int skip_size = (b.buffer[4] & 0x80) ? 9 : 0;
        bitrate = ((unsigned int)(b.buffer[4 + skip_size] & 0x0F)<<19) |
            ((unsigned int)b.buffer[5 + skip_size]<<11) |
            ((unsigned int)b.buffer[6 + skip_size]<<3) |
            ((unsigned int)b.buffer[7 + skip_size] & 0xE0);

        length = (float)fileread;
        if (length != 0)
        {
            length = ((float)length*8.f)/((float)bitrate) + 0.5f;
        }

        bitrate = (int)((float)bitrate/1000.0f + 0.5f);

        header_type = 2;
    }


    fill_buffer(&b);
    if ((bread = NeAACDecInit(hDecoder, b.buffer,
        b.bytes_into_buffer, &samplerate, &channels)) < 0)
    {
        /* If some error initializing occured, skip the file */
        faad_fprintf(stderr, "Error initializing decoder library.\n");
        if (b.buffer)
            free(b.buffer);
        NeAACDecClose(hDecoder);
        close_stream();
        return 1;
    }
    advance_buffer(&b, bread);
    fill_buffer(&b);

    return 0;
}



void* get_audio_16bit(void *sample_buffer, char *data, unsigned int samples, int bits_per_sample, int channels, int channelMask)
{
    int ret;
    unsigned int i;
    short *sample_buffer16 = (short*)sample_buffer;

    if (channels == 6 && channelMask)
    {
        for (i = 0; i < samples; i += channels)
        {
            short r1, r2, r3, r4, r5, r6;
            r1 = sample_buffer16[i];
            r2 = sample_buffer16[i+1];
            r3 = sample_buffer16[i+2];
            r4 = sample_buffer16[i+3];
            r5 = sample_buffer16[i+4];
            r6 = sample_buffer16[i+5];
            sample_buffer16[i] = r2;
            sample_buffer16[i+1] = r3;
            sample_buffer16[i+2] = r1;
            sample_buffer16[i+3] = r6;
            sample_buffer16[i+4] = r4;
            sample_buffer16[i+5] = r5;
        }
    }

    for (i = 0; i < samples; i++)
    {
        data[i*2] = (char)(sample_buffer16[i] & 0xFF);
        data[i*2+1] = (char)((sample_buffer16[i] >> 8) & 0xFF);
    }


    return (void*)data;
}



void *request_frame( int *_samples, int *_chanels, int *_chanel_mask)
{
    sample_buffer = NeAACDecDecode(hDecoder, &frameInfo,
            b.buffer, b.bytes_into_buffer);

    /* update buffer indices */
    advance_buffer(&b, frameInfo.bytesconsumed);

    if (frameInfo.error > 0)
    {
        if(frameInfo.error != 5)
            report_bug(NeAACDecGetErrorMessage(frameInfo.error));
    }


    if ((frameInfo.error == 0) && (frameInfo.samples > 0))
    {
        if(first_time) {
            channel_mask = aacChannelConfig2wavexChannelMask(&frameInfo);
            first_time = 0;
        }

        //write_audio_file(aufile, sample_buffer, frameInfo.samples, 0);
        *_samples = frameInfo.samples;
        *_chanels = channels;
        *_chanel_mask = channel_mask;
    }else {
        *_samples = 0;
        *_chanels = 0;
        *_chanel_mask = 0;
    }

    /* fill buffer */
    fill_buffer(&b);

    if (b.bytes_into_buffer == 0)
        sample_buffer = NULL; /* to make sure it stops now */

    return sample_buffer;
}



void decoder_destroy()
{
    if(hDecoder)
        NeAACDecClose(hDecoder);

    if(b.infile)
        close_stream(b.infile);

    if (b.buffer)
        free(b.buffer);
}






