SilentInstall and RemReg usage.


1. Preconditions.
   You can either use the default files (see 1.1) or provide your own 
   configuration ini file (see 1.2).
   All binary (exe, sys) files should be in the same directory as input files.

   1.1. Files needed for SilentInstall.

        - devtpl01.dat
        - siusbmod.inf
        - siusbmod.sys


   1.2. Configuration ini file.

        [conf]
        SvcName=service_name
        SysFile=driver_file.sys
        TplFile=reg_template.dat
        InfFile=driver_inf_file.inf


2. Siusbmod driver installation process.
   install_drv.cmd script file performs the full unattended installation.

   2.1. Install process using default input files.

        silentinstall.exe –i


   2.2. Install process using configuration ini file.
        
        silentinstall.exe –i config_file_name.ini
        
        where config_file_name.ini points to the configuration file (see 1.2)

   
3. Siusbmod driver uninstallation process.
   uninstall_drv.cmd script file performs the full unattended uninstallation.

   silentinstall.exe -u


4. Usage of RemReg tool.
   RemReg force removes siusbmod driver entries from system registry, if for any reasons you can't 
   remove siusbmod hardware key from the registry just run remreg.exe. 
   Caution: all data (subkeys and values) from siusbmod key will be deleted.