/*
* Ping-Pong 2009 - 2010
* save
* (c) Danil_e71
*/

struct
{
 char name[NUM_RECORD+1][15];
 int points[NUM_RECORD+1];
}record;

void parserecord(int mode);
void savedata(int mod);
void loadNastr();
void saveSettings();
void loadSettings();
