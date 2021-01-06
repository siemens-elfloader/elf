
#ifndef __AUDIO_HOOK__
#define __AUDIO_HOOK__


typedef struct
{
    char riff[4];
    unsigned int file_size;
    char wave[4];
    char fmt[4];
    unsigned int wave_section_size;
    unsigned short format;
    unsigned short channels;
    unsigned int samplerate;
    unsigned int bytes_per_sec;
    unsigned short align;
    unsigned short bits_per_sample;
    char data[4];
    unsigned int data_size;
}wave_header;


HObj ToObs(int handle);

#ifdef NEWSGOLD
HObj
#else
int
#endif
audio_control_play(int volume, int samplerate, short channels, int bits_per_sample, void (*frame_request)(int unk, unsigned short *pcmframe));
void audio_control_destroy(
#ifdef NEWSGOLD
                           HObj player_id
#else
                           int player_id
#endif
                           );

/*#ifdef NEWSGOLD
#define stopPlayBack(player) Obs_Stop(player)
#define pausePlayBack(player) Obs_Pause(player)
#define resumePlayBack(player) Obs_Resume(player)
#define setPlayBackVolume(player, vol) Obs_Sound_SetVolumeEx(player, vol, 0)
#else*/
#define stopPlayBack(player) PlayMelody_StopPlayback(player)
#define pausePlayBack(player) PlayMelody_PausePlayback(player)
#define resumePlayBack(player) PlayMelody_ResumePlayBack(player)
#define setPlayBackVolume(player, vol) Obs_Sound_SetVolumeEx(ToObs(player), vol, 0)
//#endif




#endif

