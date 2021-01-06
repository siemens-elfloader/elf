<?
$host="localhost";
$user="djdflehfr";
$pass="ctrnfeu";
$base="maps";
$com =NULL;
$result=NULL;
function connect_db()
{
$com = mysql_connect( $host, $user, $pass );
$db = mysql_select_db( $base, $com );
}

function query_db($DBquery)
{
$result = mysql_query( $DBquery, $com );
}
function
$numFields = mysql_num_fields( $result );
?>