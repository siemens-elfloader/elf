#ifndef crashpro
#define  crashpro

class CrashProtect
{
private:
   static int crashed;
   static char flagfile[128];
   static void CheckForCrash();
public:
  static char * ElfName;
  static char ZBinDrive;
  static int CanStart(){CheckForCrash();return !crashed;};
  static int CrashedLastTime(){ CheckForCrash(); return crashed;};
  static void CorrectlyTerminate();
  //static void IncorrectlyTerminated(){};
  static void Start();
};

#endif
