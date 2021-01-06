

#ifndef __DECODER_H__
#define __DECODER_H__


int init_decoder(const char *file);
void *request_frame(int *_samples, int *_chanels, int *_chanel_mask);
void decoder_destroy();
void *get_aac_buffer_data(int *size);

void* get_audio_16bit(void *sample_buffer, char *data, unsigned int samples, int bits_per_sample, int channels, int channelMask);
void *get_audio_32bit(void *sample_buffer, char *data, unsigned int samples, int bits_per_sample, int channels, int channelMask);
void *get_audio_float(void *sample_buffer, char *data, unsigned int samples, int bits_per_sample, int channels, int channelMask);

#endif
