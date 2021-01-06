<?
/*
* (c) http://siedevelop.dyndns.org/ 2011
*/

session_start();
include "./lib/language.php";
include "./lib/config.php";
include "./lib/files.php";

SetTitle($ZBIN_CREATER);
if($_GET['p']==NULL&&!$_GET['download'])
  WWritePlatform();
else if(CheckPlatform($_GET['p'])==-1&&!$_GET['download'])SetHomeErr($UNDEF_PLATFORM);
else if($_GET['zip']!="1"&&!$_GET['download'])
{
echo"
<b>$SELECT_ELFS</b>
<br>
<form action=./>";
WWrite(CheckPlatform($_GET['p']));
echo
"<input type=hidden name=p value=$_GET[p]>
 <input type=hidden name=zip value=1>
 <img src=./lib/capcha.php alt=защитный код>
 <br>
 Введите капчу:
 <br>
 <input type=text name=capcha>
 <br>
 <input type=submit value=$CREATE>
</form>";
}
else if($_GET['zip']=="1")
 {
 if($_SESSION['secpic']==strtolower($_GET['capcha']))
 {
  DeleteOld();
  $URL=ZipZbin(Read($_GET['p']));
  $text=GetSize(filesize($URL));
  printf($CREATED,$GLOBALS[TIME]);
  $hidden=basename($URL, ".zip");
  echo"<br><a href=./?download=$hidden>$DOWNLOAD</a> $text";
  }
  else SetHomeErr("Неверная капча!");
  
 }
 else if($_GET['download'])
 {
 $file='./'.$GLOBALS[PATH].'/'.$_GET['download'].'.zip';
 if(file_exists($file))header("location: ".$file);
 else SetHomeErr("Файл не существует!");
 }
?>

