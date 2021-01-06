// Mr. Anderstand:
// По образу и подобию...

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
/*#define LG_Menu                  "Меню"
#define LG_SetNextPlayed         "B очередь"
#define LG_ShowID3               "Атрибуты"
#define LG_FM                    "Файловый менеджер"
#define LG_Settings              "Настройки"
#define LG_AboutDlg              "Об эльфе..."
#define LG_Exit_SPlayer          "Выход"

#define LG_SELECT                "Выбор"
#define LG_BACK                  "Назад"

///////////Menu 1///////////
#define LG_Sets_Menu             "Инструменты"
#define LG_SetEditPL             "Редактирование плейлиста"
#define LG_Coordinates           "Позиционирование"
#define LG_Colours               "Цвета"
#define LG_Refresh               "Обновить"

///////////Attributes///////////
#define LG_ID3_Tag_Info          "ID3 тэги"
#define LG_Full_name             "Полное имя"
#define LG_Size                  "Размер файла"
#define LG_Title                 "Название"
#define LG_Artist                "Исполнитель"
#define LG_Album                 "Альбом"
#define LG_Year                  "Год"
#define LG_Comment               "Комментарий"
#define LG_Number                "Номер"
#define LG_Genre                 "Жанр"
*/
///////////Config///////////
#define LG_Default_playlist      "Станд. плейлист"
#define LG_Default_playlist_2    "Станд. плейлист 2"
#define LG_Default_playlist_3    "Станд. плейлист 3"
#define LG_Music_folder          "Папка музыки"
#define LG_Idle_coordinates      "Координаты иконки на Idle"
#define LG_Auto_Exit_Min         "Время до автозакрытия"
#define LG_Set_Speed             "Настройки скорости"
#define LG_Speed_Moving          "Скорость быстрого листания"
#define LG_Step_Moving           "Шаг быстрого листания"
#define LG_Speed_Rewind          "Скорость перемотки"
#define LG_Step_Rewind           "Шаг перемотки"
#define LG_Speed_Moving_PL       "Скорость перелистывания пл"
#define LG_Speed_Open_Moving     "Скорость открытия пл"
#define LG_Show_Anim             "Показывать анимацию"
#define LG_Sets                  "Настройки"
#define LG_Show_full_names       "Показ. полные имена"
//#define LG_Key_Settings          "Настройки конфига клавиш"
#define LG_LoadKeys              "Загружать конфиг клавиш?"
//#define LG_KeySet_Path           "Файл настроек клавиш"

#define LG_No                    "Нет"
#define LG_Yes                   "Да"

#define LG_Show_effects          "Показывать эффекты"
#define LG_Show_info             "Показывать информацию"
#define LG_Show_Popup            "Показывать попапы"
#define LG_Save_Sets             "Сохранять настройки"
#define LG_Show_All_Track        "Показывать все треки(не один)"
#define LG_Playmode              "Режим воспр."
#define LG_Play_all              "Воспр. все"
#define LG_Repeat_all            "Повторить все"
#define LG_Random                "Случайно"
#define LG_Repeat_one            "Повторять один"
#define LG_Extension_of_playlist "Расширение плейлиста"
#define LG_spl                   "spl"
#define LG_m3u                   "m3u"
#define LG_Default_volume        "Станд. громкость"
#define LG_Amount_of_lines       "Количество треков"
#define LG_Size_Of_Font          "Размер шрифта"
#define LG_Send_fname            "Отправлять имя файла"
#define LG_Paths                 "Пути к файлам/папкам"
#define LG_Picture_folder        "Папка для графики"
#define LG_Playlist_folder       "Папка для плейлистов"
#define LG_Path_To_SCE           "SPlayer cfg editor"
#define LG_Path_To_Lang          "Файл ленгпака"
#define LG_Sets_Path             "Папка доп. файлов"
//#define LG_Sets_File             "Файл настроек"

///////////ShowMSG/MsgBoxError///////////
/*#define LG_Can_not_find_file     "Файл не найден!"
#define LG_Load_a_playlist       "Пожалуйста, загрузите плейлист!"
#define LG_Keypad_Unlock         "Клавиатура разблокирована"
#define LG_Keypad_Lock           "Клавиатура заблокирована"
#define LG_Config_Updated        "Конфиг SPlayer'а изменен!"
#define LG_PL_Saved              "Плейлист сохранен!"
#define LG_Exit                  "Закрыть SPlayer?"
#define LG_Is_not_selected       "Не выбрано!"
#define LG_No_Tags               "Нет ID3 тэгов!"
#define LG_Already_Started       "Уже запущен!"
#define LG_Error_1               "Ошибка 1"
#define LG_Error_2               "Ошибка 2: Неверно назначена клавиша!"
#define LP_Spkeys_er             "Ошибка spkeys!"
#define LGP_PNG_er               " png-файлов отсутствует. Это может замедлить работу!"
#define LGP_eoPL                 "Плейлист переполнен!"
#define LGP_Error_cfg_file       "Ошибка cfg-файла!"
#define LGP_No_cfg_file          "Отсутствует cfg-файл!"
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
#define LG_Menu                  "Меню"
#define LG_SetNextPlayed         "У чергу"
#define LG_FM                   ////////////////////////// "Файловый менеджер"
#define LG_ShowID3               "Атрибути"
#define LG_Settings              "Установки"
#define LG_AboutDlg              "Про ельф..."
#define LG_Exit_SPlayer          "Выхiд"

#define LG_SELECT                "Вибiр"
#define LG_BACK                  "Назад"

///////////Menu 1///////////
#define LG_Sets_Menu             "Струмент"
#define LG_SetEditPL             "Редактування плейлиста"
#define LG_Coordinates           "Позициювання"
#define LG_Colours               "Кольоpи"
#define LG_Refresh               "Оновлення"

///////////Attributes///////////
#define LG_ID3_Tag_Info          "ID3 теги"
#define LG_Full_name             "Повне iм'я"
#define LG_Size                  "Розмiр файлу"
#define LG_Title                 "Назва"
#define LG_Artist                "Виконавець"
#define LG_Album                 "Альбом"
#define LG_Year                  "Рiк"
#define LG_Comment               "Коментарi"
#define LG_Number             ////////////////////////   "Номер"
#define LG_Genre                 "Жанр"
*/
///////////Config///////////
#define LG_Default_playlist      "Стнад. плейлист"
#define LG_Default_playlist_2    "Стнад. плейлист 2"
#define LG_Default_playlist_3    "Стнад. плейлист 3"
#define LG_Music_folder          "Папка пiсень"
#define LG_Idle_coordinates      "Координати ярличка на Idle"
#define LG_Auto_Exit_Min       ///////////////////////  "Время до автозакрытия"
#define LG_Set_Speed           ///////////////////////  "Настройки скорости"
#define LG_Speed_Moving        //////////////////////  "Скорость листания"
#define LG_Step_Moving         /////////////////////  "Шаг быстрого листания"
#define LG_Speed_Rewind        /////////////////////  "Скорость перемотки"
#define LG_Step_Rewind         ////////////////////  "Шаг перемотки"
#define LG_Speed_Moving_PL     /////////////////////  "Скорость перелистывания пл"
#define LG_Speed_Open_Moving   /////////////////////  "Скорость открытия пл"
#define LG_Show_Anim           //////////////////////  "Показывать анимацию"
#define LG_Sets                  "Установки"
#define LG_Show_full_names       "Показ повного iменi"
#define LG_Key_Settings        ///////////////////////  "Настроки конфига клавиш"
#define LG_LoadKeys            //////////////////////  "Загружать из файла?"
#define LG_KeySet_Path         ///////////////////  "Файл настроек клавиш"

#define LG_No			"Нi"
#define LG_Yes			"Так"

#define LG_Show_effects          "Показ ефектiв"
#define LG_Show_info           //////////////////////  "Show info"
#define LG_Show_Popup           //////////////////////  "Показывать попапы"
#define LG_Save_Sets            ///////////////////// "Сохранять настройки"
#define LG_Show_One_Track       ////////////////////// "Показывать 1 трек"
#define LG_Playmode              "Режим відтворення"
#define LG_Play_all              "Відтворити все"
#define LG_Repeat_all            "Повторювати усе"
#define LG_Random                "Випадково"
#define LG_Repeat_one            "Повторювати один"
#define LG_Extension_of_playlist "Розширення плейлиста"
#define LG_spl                   "spl"
#define LG_m3u                   "m3u"
#define LG_Default_volume        "Гучнiсть"
#define LG_Amount_of_lines       "Кількість треків"
#define LG_Size_Of_Font        /////////////////////  "Размер шрифта"
#define LG_Send_fname          ////////////////////  "Отправлять имя файла"
#define LG_Paths                 "Шлях до файлiв/папок"
#define LG_Picture_folder        "Папка для графiки"
#define LG_Playlist_folder       "Папка для плейлистів"
#define LG_Path_To_SCE           "SPlayer cfg editor"
#define LG_Path_To_Lang        ///////////////////  "Language file"
#define LG_Path_To_Files         ////////////////////////// "Папка с доп. файлами"
/*
///////////ShowMSG/MsgBoxError///////////
#define LG_Can_not_find_file    "файл не знайдено!"
#define LG_Load_a_playlist      "Будь ласка, завантажте плейлiст!"
#define LG_Keypad_Unlock	"Клавiатура заблоковано"
#define LG_Keypad_Lock  	"Клавiатура разблоковано"
#define LG_Config_Updated	"Конфiг SPlayer'a змiнено!"
#define LG_PL_Saved		"Плейлiст збережено!"
#define LG_Exit         	"Закрити SPlayer?"
#define LG_Is_not_selected	"Не обрано!"
#define LG_No_Tags		"Вiдсутнi ID3 тегi!"
#define LG_Already_Started    ////////////////////////////////////////////   "Уже запущен!"
#define LG_Error_1		"Помилка 1"
#define LG_Error_2		"Помилка 2"
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
#define LG_Step_Moving          /////////////////// "Шаг быстрого листания"
#define LG_Speed_Rewind          "Speed of rewind"
#define LG_Step_Rewind          /////////////////// "Шаг перемотки"
#define LG_Speed_Moving_PL       "Speed of move pl"
#define LG_Speed_Open_Moving     //////////////////"Скорость открытия пл"
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
#define LG_Path_To_Files         ////////////////////////// "Папка с доп. файлами"
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
