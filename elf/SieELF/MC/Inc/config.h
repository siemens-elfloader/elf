#ifndef _CONFIG_H
#define _CONFIG_H

typedef struct
{
	int sort;
	int LastInd;
	char LastPath[MAX_PATH];
} MC_CFGti;

typedef struct
{
	int curtab;
	MC_CFGti tabs[MAX_TABS];
} MC_CFG;

#define MCCF_hdr mccfg_hdr

#define mccf_sig (*(int*)"mccf")
#define mccf_ver 1
#define mccf_size sizeof(MC_CFG)
#define mccf_offset sizeof(MCCF_hdr)
#define mccf_minsize (sizeof(MCCF_hdr)+mccf_size)

extern const char mccf_config[];
extern MC_CFG MCConfig;

void SaveCfg();
int LoadCfg();

#endif
