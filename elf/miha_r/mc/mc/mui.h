#define id_no		1
#define id_yes		2

#define id_byte		10
#define id_kbyte		11
#define id_mbyte		12

#define id_reconfig		50
#define id_lng		51
#define id_lngname		52

#define id_dirmking		100
#define id_copying		101
#define id_moveing		102
#define id_deling		103

#define id_mcmenu		1000
#define id_select		1001
#define id_back		1002

#define id_open		1010
#define id_file_m		1020
#define id_chk		1021
#define id_chkall		1022
#define id_invchk		1024
#define id_unchall		1023
#define id_oper_m		1030
#define id_past		1031
#define id_cancel		1037
#define id_copy		1032
#define id_move		1033
#define id_del		1034
#define id_rename		1035
#define id_newdir		1036
#define id_prop		1040
#define id_drvinf		1050
#define id_view_m		1090
#define id_sort_m		1080
#define id_sortn		1081
#define id_sorte		1082
#define id_sorts		1083
#define id_sortd		1084
#define id_sortr		1085
#define id_filter		1092
#define id_refresh		1091
#define id_bm_m		1060
#define id_bm		1061
#define id_add		1062
#define id_bml		1063
#define id_misc_m		1070
#define id_settings		1071
#define id_about_m		1072
#define id_exit		1100

#define id_name		1500
#define id_fullname		1501
#define id_size		1502
#define id_global		1511
#define id_folders		1512
#define id_files		1513
#define id_date		1503
#define id_attr		1504
#define id_readonly		1505
#define id_hidden		1506
#define id_system		1507
#define id_arh		1508
#define id_subdirs		1509

#define id_pmt_del		3000
#define id_pmt_copy		3001
#define id_pmt_move		3002
#define id_pmt_stop		3003
#define id_pmt_cancel		3008
#define id_pmt_exists		3004
#define id_pmt_exit		3005
#define id_pmt_impcs		3006
#define id_pmt_implg		3007

#define id_err_attrset		4001
#define id_err_makedir		4002
#define id_err_rename		4003
#define id_err_delete		4004
#define id_err_badname_t		4005
#define id_err_baddrv_t		4006
#define id_err_resnok		4007
#define id_err_nofiles		4008
#define id_err_badname		4009
#define id_err_badkey		4010
#define id_err_badformat		4011


	typedef struct
{
 int id;
 char* df_str;
}MUI_STR;

typedef struct
{
 unsigned short id;
 unsigned short ofs;
}MC_LG;

#define MCLG_hdr mccfg_hdr

#define mclg_sig (*(int*)"mclg")
#define mclg_ver 2
#define mclg_size MUI_COUNT
#define mclg_offset sizeof(MCLG_hdr)

extern const char mclg_deffile[];
extern const char mclg_ext[];

void SaveMUI(char* filename);
int LoadMUI(char* filename);
void InitMUI();
void FreeMUI();
char* muitxt(int ind);







#define ind_no		0
#define ind_yes		1

#define ind_byte		2
#define ind_kbyte		3
#define ind_mbyte		4

#define ind_reconfig		5
#define ind_lng		6
#define ind_lngname		7

#define ind_dirmking		8
#define ind_copying		9
#define ind_moveing		10
#define ind_deling		11

#define ind_mcmenu		12
#define ind_select		13
#define ind_back		14

#define ind_open		15
#define ind_file_m		16
#define ind_chk		17
#define ind_chkall		18
#define ind_invchk		19
#define ind_unchall		20
#define ind_oper_m		21
#define ind_past		22
#define ind_cancel		23
#define ind_copy		24
#define ind_move		25
#define ind_del		26
#define ind_rename		27
#define ind_newdir		28
#define ind_prop		29
#define ind_drvinf		30
#define ind_view_m		31
#define ind_sort_m		32
#define ind_sortn		33
#define ind_sorte		34
#define ind_sorts		35
#define ind_sortd		36
#define ind_sortr		37
#define ind_filter		38
#define ind_refresh		39
#define ind_bm_m		40
#define ind_bm		41
#define ind_add		42
#define ind_bml		43
#define ind_misc_m		44
#define ind_settings		45
#define ind_about_m		46
#define ind_exit		47

#define ind_name		48
#define ind_fullname		49
#define ind_size		50
#define ind_global		51
#define ind_folders		52
#define ind_files		53
#define ind_date		54
#define ind_attr		55
#define ind_readonly		56
#define ind_hidden		57
#define ind_system		58
#define ind_arh		59
#define ind_subdirs		60

#define ind_pmt_del		61
#define ind_pmt_copy		62
#define ind_pmt_move		63
#define ind_pmt_stop		64
#define ind_pmt_cancel		65
#define ind_pmt_exists		66
#define ind_pmt_exit		67
#define ind_pmt_impcs		68
#define ind_pmt_implg		69

#define ind_err_attrset		70
#define ind_err_makedir		71
#define ind_err_rename		72
#define ind_err_delete		73
#define ind_err_badname_t		74
#define ind_err_baddrv_t		75
#define ind_err_resnok		76
#define ind_err_nofiles		77
#define ind_err_badname		78
#define ind_err_badkey		79
#define ind_err_badformat		80
