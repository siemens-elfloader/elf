<?
/*
* (C)Danil_e71 2011
* (r) google.ru, yandex.ru
* Для каждого сайта генерируем свой ключ!Иначе не выведете картинку!
* http://code.google.com/intl/ru-RU/apis/maps/signup.html
* Параметры:
* lat/lon - широта/долгота 
* cell,op,cc,lac -бс 
* Нужно использовать или lat/lon, или cell/op/cc/lac 
* zoom принимает значения 0 - 19 (по дефолту 10) 
* t принимает значения roadmap,mobile,satellite,terrain,hybrid (по дефолту mobile) 
* frmt принимает значения png,gif,jpg (по дефолту png) 
* szx принимает значения 0 - 512 (по дефолту 150) 
* szy принимает значения 0 - 512 (по дефолту 150) 
* color принимает значения red,green,blue (не обязателен) 
* name принимает значения a-z (не обязателен) 
* hl принимает значения ru,en и т.д.(по дефолту ru) нужен для языка обозначений на карте 
* clat/clon координаты центрирования (по дефолту центрирует по вашим координатам) 
* q принимает значения text, image (по дефолту text)
* Пример
* ?lat=45.0117154&lon=41.9284964&zoom=10&t=mobile&frmt=png&szx=512&szy=512&color=blue&name=i&q=image
* или
* ?cell=62577&op=99&cc=250&lac=16855&zoom=10&t=mobile&frmt=png&szx=512&szy=512&color=blue&name=i&q=image
*/

//get params
$ky              ='ABQIAAAAqV2OGt7lLeOqPjzPlWRjDBR-51eTUNBQxkC3j-AWWroD5UXSfxStAEfFiy_TlLBRu-Hacb33IlknUA';
$cellid          =$_GET["cell"];
$operatorid      =$_GET["op"];
$countrycode     =$_GET["cc"];
$lac             =$_GET["lac"];
$maptype         =$_GET["t"];
$format          =$_GET["frmt"];
$latt            =$_GET["lat"];
$lonn            =$_GET["lon"];
$zoom            =$_GET["zoom"];
$sizex           =$_GET["szx"];
$sizey           =$_GET["szy"];
$color           =$_GET["color"];
$name            =$_GET["name"];
$type            =$_GET["q"];
$hl              =$_GET["hl"];
$clt             =$_GET["clat"];
$cln             =$_GET["clon"];

//yandex
function startElement($parser, $name, $attrs) 
{
  GLOBAL $lat,$lon;
  if($name=="COORDINATES")
 {
   $lat=$attrs["LATITUDE"];
   $lon=$attrs["LONGITUDE"];
 }
}

if($latt==NULL||$lonn==NULL)
{

$xmldata = file_get_contents("http://mobile.maps.yandex.net/cellid_location/?cellid=$cellid&operatorid=$operatorid&countrycode=$countrycode&lac=$lac");

$xml_parser = xml_parser_create();

xml_set_element_handler($xml_parser, "startElement", NULL);

xml_parse($xml_parser, $xmldata);

xml_parser_free($xml_parser);

$lt=$lat;

$ln=$lon;

}
else
{
$lt=$latt;
$ln=$lonn;
}

$querry="http://maps.google.com/staticmap?";

if($clt!=NULL)$querry=$querry.'center='.$clt;
else $querry=$querry.'center='.$lt;

if($cln!=NULL)$querry=$querry.','.$cln;
else $querry=$querry.','.$ln;

if($maptype!=NULL)$querry=$querry.'&maptype='.$maptype;
else $querry=$querry.'&maptype=mobile';

if($format!=NULL)$querry=$querry.'&format='.$format;
else $querry=$querry.'&format=png';

if($zoom!=NULL&&$zoom>=0&&$zoom<=19)$querry=$querry.'&zoom='.$zoom;
else $querry=$querry.'&zoom=10';

if($sizex!=NULL&&$sizex<=512)$querry=$querry.'&size='.$sizex;
else $querry=$querry.'&size=150';

if($sizey!=NULL&&$sizey<=512)$querry=$querry.'x'.$sizey;
else $querry=$querry.'x150';

$querry=$querry.'&key='.$ky;

if($color!=NULL||$name!=NULL)$querry=$querry.'&markers='.$lt.','.$ln.','.$color.$name;

if($hl!=NULL)$querry=$querry.'&hl='.$hl;
else $querry=$querry.'&hl=ru';

if($type!="text"&&$type!=="image")$type="text";

switch($type)
{
case "text":
echo"lat: $lt\r\nlon: $ln";
break;

case "image":
echo"<img src=$querry>";
break;
}

?>