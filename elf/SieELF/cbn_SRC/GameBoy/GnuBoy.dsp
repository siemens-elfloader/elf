# Microsoft Developer Studio Project File - Name="GnuBoy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=GnuBoy - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GnuBoy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GnuBoy.mak" CFG="GnuBoy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GnuBoy - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "GnuBoy - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GnuBoy - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "GnuBoy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GnuBoy - Win32 Release"
# Name "GnuBoy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CPU.cpp
# End Source File
# Begin Source File

SOURCE=.\DEBUG.cpp
# End Source File
# Begin Source File

SOURCE=.\EMU.cpp
# End Source File
# Begin Source File

SOURCE=.\EVENTS.cpp
# End Source File
# Begin Source File

SOURCE=.\EXPORTS.cpp
# End Source File
# Begin Source File

SOURCE=.\FASTMEM.cpp
# End Source File
# Begin Source File

SOURCE=.\HW.cpp
# End Source File
# Begin Source File

SOURCE=.\INFLATE.cpp
# End Source File
# Begin Source File

SOURCE=.\KEYTABLE.cpp
# End Source File
# Begin Source File

SOURCE=.\LCD.cpp
# End Source File
# Begin Source File

SOURCE=.\LCDC.cpp
# End Source File
# Begin Source File

SOURCE=.\LOADER.cpp
# End Source File
# Begin Source File

SOURCE=.\MAIN.cpp
# End Source File
# Begin Source File

SOURCE=.\MEM.cpp
# End Source File
# Begin Source File

SOURCE=..\Mylib.cpp
# End Source File
# Begin Source File

SOURCE=.\NEWSOUND.cpp
# End Source File
# Begin Source File

SOURCE=.\PALETTE.cpp
# End Source File
# Begin Source File

SOURCE=.\PATH.cpp
# End Source File
# Begin Source File

SOURCE=.\RCCMDS.cpp
# End Source File
# Begin Source File

SOURCE=.\RCFILE.cpp
# End Source File
# Begin Source File

SOURCE=.\RCKEYS.cpp
# End Source File
# Begin Source File

SOURCE=.\RCVARS.cpp
# End Source File
# Begin Source File

SOURCE=.\REFRESH.cpp
# End Source File
# Begin Source File

SOURCE=.\RTC.cpp
# End Source File
# Begin Source File

SOURCE=.\SAVE.cpp
# End Source File
# Begin Source File

SOURCE=.\SOUND.cpp
# End Source File
# Begin Source File

SOURCE=.\SPLIT.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Cpu.h
# End Source File
# Begin Source File

SOURCE=.\Cpucore.h
# End Source File
# Begin Source File

SOURCE=.\Cpuregs.h
# End Source File
# Begin Source File

SOURCE=.\Defs.h
# End Source File
# Begin Source File

SOURCE=.\Fastmem.h
# End Source File
# Begin Source File

SOURCE=.\Fb.h
# End Source File
# Begin Source File

SOURCE=.\Hw.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\Lcd.h
# End Source File
# Begin Source File

SOURCE=.\Loader.h
# End Source File
# Begin Source File

SOURCE=.\Mem.h
# End Source File
# Begin Source File

SOURCE=..\Mylib.h
# End Source File
# Begin Source File

SOURCE=.\Noise.h
# End Source File
# Begin Source File

SOURCE=.\Pcm.h
# End Source File
# Begin Source File

SOURCE=.\Rc.h
# End Source File
# Begin Source File

SOURCE=.\Regs.h
# End Source File
# Begin Source File

SOURCE=.\Rtc.h
# End Source File
# Begin Source File

SOURCE=.\Sound.h
# End Source File
# Begin Source File

SOURCE=..\Swilib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
