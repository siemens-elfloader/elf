// Mr. Anderstand:
// �� ������ � �������...

#include "setlang.h"
#ifndef _LANG_H_
#define _LANG_H_

#define LG_Version              "1.0.1.4"

///////////////////////////////////////////////////////////////////////////////////////////
//
//    Russian
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_RU

///////////MainMenu///////////
/*#define LG_Menu                  "����"
#define LG_SetNextPlayed         "B �������"
#define LG_ShowID3               "��������"
#define LG_FM                    "�������� ��������"
#define LG_Settings              "���������"
#define LG_AboutDlg              "�� �����..."
#define LG_Exit_SPlayer          "�����"

#define LG_SELECT                "�����"
#define LG_BACK                  "�����"

///////////Menu 1///////////
#define LG_Sets_Menu             "�����������"
#define LG_SetEditPL             "�������������� ���������"
#define LG_Coordinates           "����������������"
#define LG_Colours               "�����"
#define LG_Refresh               "��������"

///////////Attributes///////////
#define LG_ID3_Tag_Info          "ID3 ����"
#define LG_Full_name             "������ ���"
#define LG_Size                  "������ �����"
#define LG_Title                 "��������"
#define LG_Artist                "�����������"
#define LG_Album                 "������"
#define LG_Year                  "���"
#define LG_Comment               "�����������"
#define LG_Number                "�����"
#define LG_Genre                 "����"
*/
///////////Config///////////
#define LG_Default_playlist      "�����. ��������"
#define LG_Default_playlist_2    "�����. �������� 2"
#define LG_Default_playlist_3    "�����. �������� 3"
#define LG_Music_folder          "����� ������"
#define LG_Idle_coordinates      "���������� ������ �� Idle"
#define LG_Auto_Exit_Min         "����� �� ������������"
#define LG_Set_Speed             "��������� ��������"
#define LG_Speed_Moving          "�������� �������� ��������"
#define LG_Step_Moving           "��� �������� ��������"
#define LG_Speed_Rewind          "�������� ���������"
#define LG_Step_Rewind           "��� ���������"
#define LG_Speed_Moving_PL       "�������� �������������� ��"
#define LG_Speed_Open_Moving     "�������� �������� ��"
#define LG_Show_Anim             "���������� ��������"
#define LG_Sets                  "���������"
#define LG_Show_full_names       "�����. ������ �����"
//#define LG_Key_Settings          "��������� ������� ������"
#define LG_LoadKeys              "��������� ������ ������?"
//#define LG_KeySet_Path           "���� �������� ������"

#define LG_No                    "���"
#define LG_Yes                   "��"

#define LG_Show_effects          "���������� �������"
#define LG_Show_info             "���������� ����������"
#define LG_Show_Popup            "���������� ������"
#define LG_Save_Sets             "��������� ���������"
#define LG_Show_All_Track        "���������� ��� �����(�� ����)"
#define LG_Playmode              "����� �����."
#define LG_Play_all              "�����. ���"
#define LG_Repeat_all            "��������� ���"
#define LG_Random                "��������"
#define LG_Repeat_one            "��������� ����"
#define LG_Extension_of_playlist "���������� ���������"
#define LG_spl                   "spl"
#define LG_m3u                   "m3u"
#define LG_Default_volume        "�����. ���������"
#define LG_Amount_of_lines       "���������� ������"
#define LG_Size_Of_Font          "������ ������"
#define LG_Send_fname            "���������� ��� �����"
#define LG_Paths                 "���� � ������/������"
#define LG_Picture_folder        "����� ��� �������"
#define LG_Playlist_folder       "����� ��� ����������"
#define LG_Path_To_SCE           "SPlayer cfg editor"
#define LG_Path_To_Lang          "���� ��������"
#define LG_Sets_Path             "����� ���. ������"
//#define LG_Sets_File             "���� ��������"

///////////ShowMSG/MsgBoxError///////////
/*#define LG_Can_not_find_file     "���� �� ������!"
#define LG_Load_a_playlist       "����������, ��������� ��������!"
#define LG_Keypad_Unlock         "���������� ��������������"
#define LG_Keypad_Lock           "���������� �������������"
#define LG_Config_Updated        "������ SPlayer'� �������!"
#define LG_PL_Saved              "�������� ��������!"
#define LG_Exit                  "������� SPlayer?"
#define LG_Is_not_selected       "�� �������!"
#define LG_No_Tags               "��� ID3 �����!"
#define LG_Already_Started       "��� �������!"
#define LG_Error_1               "������ 1"
#define LG_Error_2               "������ 2: ������� ��������� �������!"
#define LP_Spkeys_er             "������ spkeys!"
#define LGP_PNG_er               " png-������ �����������. ��� ����� ��������� ������!"
#define LGP_eoPL                 "�������� ����������!"
#define LGP_Error_cfg_file       "������ cfg-�����!"
#define LGP_No_cfg_file          "����������� cfg-����!"
*/
#endif //RU

///////////////////////////////////////////////////////////////////////////////////////////
//
//    Ukrainian
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_UA
/*
///////////MainMenu///////////
#define LG_Menu                  "����"
#define LG_SetNextPlayed         "� �����"
#define LG_FM                   ////////////////////////// "�������� ��������"
#define LG_ShowID3               "��������"
#define LG_Settings              "���������"
#define LG_AboutDlg              "��� ����..."
#define LG_Exit_SPlayer          "���i�"

#define LG_SELECT                "���i�"
#define LG_BACK                  "�����"

///////////Menu 1///////////
#define LG_Sets_Menu             "��������"
#define LG_SetEditPL             "������������ ���������"
#define LG_Coordinates           "������������"
#define LG_Colours               "�����p�"
#define LG_Refresh               "���������"

///////////Attributes///////////
#define LG_ID3_Tag_Info          "ID3 ����"
#define LG_Full_name             "����� i�'�"
#define LG_Size                  "����i� �����"
#define LG_Title                 "�����"
#define LG_Artist                "����������"
#define LG_Album                 "������"
#define LG_Year                  "�i�"
#define LG_Comment               "��������i"
#define LG_Number             ////////////////////////   "�����"
#define LG_Genre                 "����"
*/
///////////Config///////////
#define LG_Default_playlist      "�����. ��������"
#define LG_Default_playlist_2    "�����. �������� 2"
#define LG_Default_playlist_3    "�����. �������� 3"
#define LG_Music_folder          "����� �i����"
#define LG_Idle_coordinates      "���������� ������� �� Idle"
#define LG_Auto_Exit_Min       ///////////////////////  "����� �� ������������"
#define LG_Set_Speed           ///////////////////////  "��������� ��������"
#define LG_Speed_Moving        //////////////////////  "�������� ��������"
#define LG_Step_Moving         /////////////////////  "��� �������� ��������"
#define LG_Speed_Rewind        /////////////////////  "�������� ���������"
#define LG_Step_Rewind         ////////////////////  "��� ���������"
#define LG_Speed_Moving_PL     /////////////////////  "�������� �������������� ��"
#define LG_Speed_Open_Moving   /////////////////////  "�������� �������� ��"
#define LG_Show_Anim           //////////////////////  "���������� ��������"
#define LG_Sets                  "���������"
#define LG_Show_full_names       "����� ������� i���i"
#define LG_Key_Settings        ///////////////////////  "�������� ������� ������"
#define LG_LoadKeys            //////////////////////  "��������� �� �����?"
#define LG_KeySet_Path         ///////////////////  "���� �������� ������"

#define LG_No			"�i"
#define LG_Yes			"���"

#define LG_Show_effects          "����� �����i�"
#define LG_Show_info           //////////////////////  "Show info"
#define LG_Show_Popup           //////////////////////  "���������� ������"
#define LG_Save_Sets            ///////////////////// "��������� ���������"
#define LG_Show_One_Track       ////////////////////// "���������� 1 ����"
#define LG_Playmode              "����� ����������"
#define LG_Play_all              "³�������� ���"
#define LG_Repeat_all            "����������� ���"
#define LG_Random                "���������"
#define LG_Repeat_one            "����������� ����"
#define LG_Extension_of_playlist "���������� ���������"
#define LG_spl                   "spl"
#define LG_m3u                   "m3u"
#define LG_Default_volume        "����i���"
#define LG_Amount_of_lines       "ʳ������ �����"
#define LG_Size_Of_Font        /////////////////////  "������ ������"
#define LG_Send_fname          ////////////////////  "���������� ��� �����"
#define LG_Paths                 "���� �� ����i�/�����"
#define LG_Picture_folder        "����� ��� ����i��"
#define LG_Playlist_folder       "����� ��� ���������"
#define LG_Path_To_SCE           "SPlayer cfg editor"
#define LG_Path_To_Lang        ///////////////////  "Language file"
#define LG_Path_To_Files         ////////////////////////// "����� � ���. �������"
/*
///////////ShowMSG/MsgBoxError///////////
#define LG_Can_not_find_file    "���� �� ��������!"
#define LG_Load_a_playlist      "���� �����, ���������� �����i��!"
#define LG_Keypad_Unlock	"����i����� �����������"
#define LG_Keypad_Lock  	"����i����� ������������"
#define LG_Config_Updated	"����i� SPlayer'a ��i����!"
#define LG_PL_Saved		"�����i�� ���������!"
#define LG_Exit         	"������� SPlayer?"
#define LG_Is_not_selected	"�� ������!"
#define LG_No_Tags		"�i�����i ID3 ���i!"
#define LG_Already_Started    ////////////////////////////////////////////   "��� �������!"
#define LG_Error_1		"������� 1"
#define LG_Error_2		"������� 2"
*/

#endif //UA

///////////////////////////////////////////////////////////////////////////////////////////
//
//    English
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_EN

///////////MainMenu///////////
/*#define LG_Menu                  "Menu"
#define LG_SetNextPlayed         "Set next played"
#define LG_ShowID3               "Attributes"
#define LG_FM                    "File manager"
#define LG_Settings              "Settings"
#define LG_AboutDlg              "About..."
#define LG_Exit_SPlayer          "Exit"

#define LG_SELECT                "Select"
#define LG_BACK                  "Back"

///////////Menu 1///////////
#define LG_Sets_Menu             "Instruments"
#define LG_SetEditPL             "Edit playlist"
#define LG_Coordinates           "Coordinates"
#define LG_Colours               "Colours"
#define LG_Refresh               "Refresh"

///////////Attributes///////////
#define LG_ID3_Tag_Info          "ID3 Tag Info"
#define LG_Full_name             "Full name"
#define LG_Size                  "Size"
#define LG_Title                 "Title"
#define LG_Artist                "Artist"
#define LG_Album                 "Album"
#define LG_Year                  "Year"
#define LG_Comment               "Comment"
#define LG_Number                "Number"
#define LG_Genre                 "Genre"
*/
///////////Config///////////
#define LG_Default_playlist      "Default playlist"
#define LG_Default_playlist_2    "Default playlist 2"
#define LG_Default_playlist_3    "Default playlist 3"
#define LG_Music_folder          "Music folder"
#define LG_Idle_coordinates      "Idle coordinates"
#define LG_Auto_Exit_Min         "Time before close"
#define LG_Set_Speed             "Settings of speed"
#define LG_Speed_Moving          "Speed of move cursor"
#define LG_Step_Moving          /////////////////// "��� �������� ��������"
#define LG_Speed_Rewind          "Speed of rewind"
#define LG_Step_Rewind          /////////////////// "��� ���������"
#define LG_Speed_Moving_PL       "Speed of move pl"
#define LG_Speed_Open_Moving     //////////////////"�������� �������� ��"
#define LG_Show_Anim             "Show animation"
#define LG_Sets                  "Sets"
#define LG_Show_full_names       "Show full names"
//#define LG_Key_Settings          "Key-config settings"
#define LG_LoadKeys              "Load key-config from file"
//#define LG_KeySet_Path           "File key-config"

#define LG_No                    "No"
#define LG_Yes                   "Yes"

#define LG_Show_effects          "Show effects"
#define LG_Show_info             "Show info"
#define LG_Show_Popup            "Show popups"
#define LG_Save_Sets             "Save settings"
#define LG_Show_One_Track        "Show 1 track"
#define LG_Playmode              "Playmode"
#define LG_Play_all              "Play all"
#define LG_Repeat_all            "Repeat all"
#define LG_Random                "Random"
#define LG_Repeat_one            "Repeat one"
#define LG_Extension_of_playlist "Extension of playlist"
#define LG_spl                   "spl"
#define LG_m3u                   "m3u"
#define LG_Default_volume        "Default volume"
#define LG_Amount_of_lines       "Amount of lines"
#define LG_Size_Of_Font          "Size of font"
#define LG_Send_fname            "Send filename"
#define LG_Paths                 "Paths"
#define LG_Picture_folder        "Picture folder"
#define LG_Playlist_folder       "Playlist folder"
#define LG_Path_To_SCE           "SPlayer cfg editor"
//#define LG_Path_To_Lang          "Language file"
#define LG_Path_To_Files         ////////////////////////// "����� � ���. �������"
/*
///////////ShowMSG/MsgBoxError///////////
#define LG_Can_not_find_file     "Can't find file!"
#define LG_Load_a_playlist       "Load a playlist, please!"
#define LG_Keypad_Unlock         "Keypad unlocked"
#define LG_Keypad_Lock           "Keypad locked"
#define LG_Config_Updated        "SPlayer config updated!"
#define LG_PL_Saved              "Playlist saved!"
#define LG_Exit                  "Close SPlayer?"
#define LG_Is_not_selected       "Isn't selected!"
#define LG_No_Tags               "No ID3 tags!"
#define LG_Already_Started       "Already started!"
#define LG_Error_1               "Error 1"
#define LG_Error_2               "Error 2: Bad key!"
*/
#endif //EN


#endif
