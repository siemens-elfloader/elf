
#include <swilib.h>
#include "audio_control.h"
#include <spl/processbridge.h>
#include <fcntl.h>
#include <unistd.h>


/*
const unsigned char WavHdr[44] =
{
    0x52, 0x49, 0x46, 0x46,
    0x26, 0xbd, 0x17, 0x01,
    0x57, 0x41, 0x56, 0x45,
    0x66, 0x6d, 0x74, 0x20,
    0x12, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x02, 0x00,
    0x44, 0xac, 0x00, 0x00,
    0x88, 0x58, 0x01, 0x00,
    0x02, 0x00, 0x10, 0x00,
    0x00, 0x00, 0x64, 0x61,
    0x74, 0x61, 0x00, 0xbd
};
*/

unsigned char WavHdr[44] =
{
    0x52, 0x49, 0x46, 0x46, 0x6A, 0x88, 0x04, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x40, 0x1F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00,
    0x02, 0x00, 0x08, 0x00, 0x64, 0x61, 0x74, 0x61, 0x06, 0x88, 0x04, 0x00
};

char audio_control_fake_audio[8192] = {0};


#define PCM_HOOK_FUNC *((unsigned int *)RamAudioHookProc())


HObj ToObs(int handle)
{
    if(handle == -1) return 0;
    HObj Tobj;
    Tobj = (HObj)GetPlayObjById(handle);
    if(!Tobj) return 0;
    int ret = (( int*)Tobj)[0x3d0/4];
    return ret;
}


#ifdef NEWSGOLD
HObj
#else
int
#endif
audio_control_play(int volume, int samplerate, short channels, int bits_per_sample, void (*frame_request)(int unk, unsigned short *pcmframe))
{
    PCM_HOOK_FUNC = (unsigned int)(frame_request);

    memcpy((char *)audio_control_fake_audio, ( void * ) ( WavHdr ), 44 );

    wave_header *header = (wave_header*)audio_control_fake_audio;
    header->samplerate = samplerate;
    header->channels = channels;
    header->bits_per_sample = bits_per_sample;
    header->bytes_per_sec = bits_per_sample * channels * samplerate / 8;
    header->data_size = 30*1024*1024;
    header->file_size = header->data_size+44;


    /* Запускаем буффер на проигрывание */
/*#ifdef NEWSGOLD

    int err;
    WSHDR *ws = AllocWS(128);
    int fd = open("2:\\test.wav", O_CREAT | O_TRUNC | O_WRONLY);
    write(fd, audio_control_fake_audio, sizeof(audio_control_fake_audio));
    close(fd);

    wsprintf(ws, "wav");
    int uid=GetExtUid_ws(ws);

    wsprintf(ws, "2:\\test.wav");
    HObj pObj = Obs_CreateObject(uid, 0x34, 1, 0xB034, 1, 0, &err);
    err = Obs_SetInput_File(pObj, 0, ws);
    FreeWS(ws);
#ifdef NEWSGOLD
#ifndef ELKA
    Obs_Sound_SetPurpose(pObj,0x16);
#else
    Obs_Mam_SetPurpose(pObj,0x16);
#endif
#else
    Obs_Mam_SetPurpose(pObj,0x16);
#endif
    Obs_Sound_SetVolumeEx(pObj, volume, 1);
    Obs_Prepare(pObj);
    Obs_Start(pObj);
    return pObj;
#else*/
    int r = PlayMelodyInMem( 0x11, audio_control_fake_audio, sizeof(audio_control_fake_audio), MMI_CEPID, 0, 0 );

#ifdef NEWSGOLD
    PlayMelody_ChangeVolume(r, 0);
    // Мега хак, звук 15-ти ступенчатый через Обс :D
    char vol = -1;
    while(vol !=0 ) {
        Obs_Sound_GetVolume(ToObs(r), &vol);
        NU_Sleep(10);
    }

    Obs_Sound_SetVolumeEx(ToObs(r), volume, 0);
#else
    PlayMelody_ChangeVolume(r, 0);
#endif

    return r;
//#endif
}


void audio_control_destroy(
#ifdef NEWSGOLD
                           HObj player_id
#else
                           int player_id
#endif
                          )
{

/*#ifdef NEWSGOLD
    Obs_Stop(player_id);
    Obs_DestroyObject(player_id);
    _unlink("2:\\test.wav", 0);
#else*/
    PlayMelody_StopPlayback(player_id);
//#endif

    PCM_HOOK_FUNC = 0;
}


