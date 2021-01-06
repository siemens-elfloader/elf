//stdio Danil_e71
//--------------------------------------------------
bool FileExists(char *fname)
{
FSTATS fs; 
 if(GetFileStats(fname,&fs,0)!=-1)
{
  return true;
}
else return false;
}
//---------------------------------------------------
unsigned int GetFileSize(char *fname)
{
 FSTATS fs;
  if(GetFileStats(fname,&fs,0)!=-1)
{
  return fs.size;
}
else return (0);
}

class TTimer
{
public:
int Interval;
void OnTimer(void func());
bool Enabled;
private:
void OnTmr();
GBSTMR *Tmr;
};

void TTimer::OnTimer(void func())
{
  GBS_StartTimerProc(&Tmr,Interval,func);
}

void ShowMessage(char message)
{
  ShowMSG(1,(int)message);
}

