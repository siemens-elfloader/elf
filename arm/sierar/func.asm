	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN


	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1


defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM


  
//                    defadr  GBS_WaitForMsg,0xA00925C4
//                    defadr  RegisterCepidForSocketWork,0xA09915E5
//                    defadr  RequestLMANConnect,0xA09926F5
//                    defadr  RefreshGUI,0xA097851D
//                    defadr  EDIT_SetFocus,0xA0A118D9
//------------------------------ OBS_EXT ---------------------------------------
            defadr Obs_MM_SetInput_ProxyURI,0xA0D18744
            defadr Obs_SoundNotify_SendEventAUMA,0xA0CC5C8C
            defadr Obs_Sound_SetVolumeEx,0xA0CC371C
            defadr Obs_Sound_Set3dAudio,0xA0CC4638
            defadr Obs_Sound_SetEqualizer,0xA0CC45C8
            defadr Obs_Sound_SetLogSourceEx,0xA0CC3964
            defadr Obs_Snd_SetPurpose,0xA0CC407C
            defadr Obs_Sound_SetHandsFree,0xA0CC3FB8
            defadr Obs_Sound_SetPWM,0xA0CC3BE8
            defadr Obs_SetOutput_Uid,0xA0CCFD44
            defadr Obs_Sound_SetPlayModePartial,0xA0CC4740
            defadr Obs_Sound_SetMute,0xA0CC3EB0

//------------------------------ Caienu (OBS) ----------------------------------
            defadr Obs_Sound_SetBitrate,0xA0CC4EA4
            defadr Obs_Sound_SetAMRFrmPrBuf,0xA0CC4BEC
            defadr Obs_Sound_SetAMRFormat,0xA0CC4A70
            defadr Obs_Sound_SetAMRDTX,0xA0CC4994
            defadr Obs_Sound_SetNofChannels,0xA0CC48AC
            defadr Obs_Sound_SetAMRMode,0xA0CC47D4
            defadr Obs_Sound_SetFIsRecording,0xA0CC450C
            defadr Obs_Sound_SetMaxFileSize,0xA0CC4378
            defadr Obs_Sound_SetRecordingMode,0xA0CC3B18
            defadr Obs_SetOutput_File,0xA0CCD008
            defadr Obs_Sound_SetSampleRate,0xA0CC4FD4
            defadr Obs_SetOutput_Push,0xA0CCD0A8//not
            defadr Obs_Purpose,0xA0CC407C
            defadr Obs_SetTime,0xA0CC441C
            defadr Obs_Vibr,0xA0CC4F50
            defadr Obs_Sound_SetVisualisationsParams,0xA0CC4E10
            defadr Obs_Get,0xA0CC5C54
            defadr Aa,0xA0675604
            defadr AAC,0xA0CC4CC8
            defadr Stop,0xA0CB7C90//0xA0CB7D1C
            defadr Cam,0xA06757C0
	END
	