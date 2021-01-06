<?
/*
* (c) http://siedevelop.dyndns.org/ 2011
*/

$all=array();

function recoursiveDir($dir)
{
$GLOBALS["all"][]=$dir.'/';
foreach(glob($dir.'/*') as $key=>$file)
  {
   if($file==".."||$file==".")continue;
   if(filetype($file)=="dir"){$GLOBALS["all"][]=$file.'/';recoursiveDir($file);}
   else $GLOBALS["all"][]=$file;
  }
}
function SetTitle($Title)
{
echo"<title>$Title</title>";
}
function SetHomeErr($Err)
{
echo"$Err<br><a href=./>$GLOBALS[HOME]</a>";
}

function WWritePlatform()
{
echo"<form action=./>
<b>$GLOBALS[SELECT_PLATFORM]</b>
<br>
<select name=p>
<option value=0>SGOLD</option>
<option value=1>SGOLD_X75</option>
<option value=2>NEWSGOLD</option>
<option value=3>ELKA</option>
</select>
<br>
<input type=submit  value=$GLOBALS[NEXT]>
</form>";
}

function CheckPlatform($p)
{
  switch($p)
   {
    case "0":return 0;
    case "1":return 1;
    case "2":return 2;
    case "3":return 3;
    default: return -1;
   }
}

function GetSize($size)
{
if($size<1024){$size=sprintf("%01.2f",$size);return $size.' '.$GLOBALS[BYTES];}
if($size>=1024){$size/=1024;$size=sprintf("%01.2f",$size); return $size.' '.$GLOBALS[KBYTES];}
if($size>=1024*1024){$size/=1024*1024;$size=sprintf("%01.2f",$size); return $size.' '.$GLOBALS[MBYTES];}
if($size>=1024*1024*1024){$size/=1024*1024*1024;$size=sprintf("%01.2f",$size); return $size.' '.$GLOBALS[GBYTES];}
}

function ZipZbin($array)
{
$zip_file="./".$GLOBALS[PATH]."/zbin".date("YmdHis").".zip";
$zip = new ZipArchive();

$zip->open($zip_file, ZipArchive::CREATE);
foreach ($array as $key=>$value) 
{
       if($_GET["elf".$key]=="true")
       {
            recoursiveDir($value);
             foreach ($GLOBALS["all"] as $val)
             {
               $s=filetype($val);
               $path=substr($val,strpos($val,$GLOBALS[PATH_PLATF])+2+strlen($GLOBALS[PATH_PLATF]));
		       if($s=="dir")$zip->AddEmptyDir("ZBin".$path);
               else $zip->addFile($val,"ZBin".$path);
             }
        }
}
$zip->close();
return $zip_file;
}

function DeleteOld()
{
$files=glob('./'.$GLOBALS[PATH].'/*');
foreach($files as $key=>$file)
  {
   if($file==".."||$file=="."||$file=="")continue;
   $fil=substr(substr($file,11),0,14);
   $year=substr($fil,0,4);
   
   $month=substr(substr($fil,4),0,2);
   

   $day=substr(substr($fil,6),0,2);
   
   $hour=substr(substr($fil,8),0,2);
   
   $min=substr(substr($fil,10),0,2);
   
   $sec=substr($fil,12);

   $old=mktime($hour,$min,$sec,$month,$day,$year);
   
   $new=time();
   
   $max=$GLOBALS[TIME]*60;

   if($old+$max<$new)unlink($file);
   
  }
}

function Read($mode)
{
   $array_of_elfs=Array();
   $path="./".$GLOBALS[PATH_PLATF].'/'.$mode."/";
   if($handle=opendir($path))
     {
       while($file=readdir($handle))
	   {
	     if($file=="."||$file=="..")continue;
		 array_push ($array_of_elfs, $path.$file);
	   }
    }
	return $array_of_elfs;
}

function WWrite($mode)
{
   $count=0;
   $path="./".$GLOBALS[PATH_PLATF].'/'.$mode."/";
   if($handle=opendir($path))
     {
       while($file=readdir($handle))
	   {
	     if($file=="."||$file=="..")continue;
		  echo"<input type=checkbox name=elf$count value=true>$file<br>";
          $count++;
		  }
	   }
    }
?>
