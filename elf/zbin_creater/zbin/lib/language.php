<?
/*
* (c) http://siedevelop.dyndns.org/ 2011
*/

$LANGUAGE=strtolower(substr($_SERVER['HTTP_ACCEPT_LANGUAGE'],0,2));
switch($LANGUAGE)
{
case "ru":
$ZBIN_CREATER="Конструктор папки ZBin";
$SELECT_PLATFORM="Выберите платформу:";
$NEXT="Далее";
$UNDEF_PLATFORM="Неверная платформа!";
$HOME="На главную";
$SELECT_ELFS="Выберите нужные эльфы";
$CREATE="Собрать";
$DOWNLOAD="Скачать";
$BYTES="байт";
$KBYTES="килобайт";
$MBYTES="мегабайт";
$GBYTES="гигабайт";
$CREATED="<b>Собрано!<br>Файл будет храниться на сервере %d минут</b>";
break;
case "be":
$ZBIN_CREATER = "Канструктар папкі ZBin";
$SELECT_PLATFORM = "Выберыце платформу:";
$NEXT = "Далей";
$UNDEF_PLATFORM = "Няправільная платформа!";
$HOME = "На галоўную";
$SELECT_ELFS = "Выберыце патрэбныя эльфы";
$CREATE = "Сабраць";
$DOWNLOAD = "Спампаваць";
$BYTES = "байтаў";
$KBYTES = "кілабайт";
$MBYTES = "мегабайт";
$GBYTES = "гігабайт";
$CREATED="<b>Сабрана!<br>Файл будзе захоўвацца на серверы %d хвілін</b>";
break;
case "ua":
$ZBIN_CREATER = "Конструктор папки ZBin";
$SELECT_PLATFORM = "Виберіть платформу:";
$NEXT = "Далі";
$UNDEF_PLATFORM = "Платформа не вiдповiдає дiйсностi!";
$HOME = "На головну";
$SELECT_ELFS = "Виберіть потрібні ельфи" ;
$CREATE = "Зібрати";
$DOWNLOAD = "Завантажити";
$BYTES = "байт";
$KBYTES = "кілобайт";
$MBYTES = "мегабайт";
$GBYTES = "гігабайт";
$CREATED="<b>Зібрано!<br>Файл буде зберігатися на сервері %d хвилин</b>";
break;
case "in":
$ZBIN_CREATER = "Designer Folder ZBin";
$SELECT_PLATFORM = "platform Pilih:";
$NEXT = "Berikutnya";
$UNDEF_PLATFORM = "platform tidak valid!";
$HOME = "Home";
$SELECT_ELFS = "Pilih elf yang diinginkan";
$CREATE = "Build"; 
$DOWNLOAD = "Download";
$BYTES = "byte"; 
$KByte = "KB";
$MBytes = "MB";
$Gbytes = "GB";
$CREATED="<b>Dikumpulkan!<br>File akan disimpan pada server %d menit</b>";
break;
default: 
$ZBIN_CREATER = "Designer Folder ZBin";
$SELECT_PLATFORM = "Select platform:";
$NEXT = "Next";
$UNDEF_PLATFORM = "Incorrect Platform";
$HOME = "Home";
$SELECT_ELFS = "Select the elfs";
$CREATE = "Build";
$DOWNLOAD = "Download";
$BYTES = "bytes";
$KBYTES = "KB";
$MBYTES = "MB";
$GBYTES = "GB";
$CREATED="<b>Created!<br>File will be stored on the server %d minutes</b>";
}
?>