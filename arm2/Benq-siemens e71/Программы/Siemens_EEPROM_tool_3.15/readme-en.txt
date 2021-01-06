+-----------------------------------------------------------------------------------------------------+
|                                    Siemens EEPROM tool v2.21                                        |
+-----------------------------------------------------------------------------------------------------+

	Main purpose of this program is the work with EEPROM of Siemens mobile phones via Service Mode.
This program allows you to export/save EEPROM blocks (all blocks at once or selected blocks only).
You can save them in binary or hex format, compare etc. As far as I know there are no similar programs
(free or commercial)....
------------------------------------------------------------------------------------------------------

+----------------------------------------------------------------------------------------------------+
|ATTENTION TO EVERYBODY:                                                                             |
+----------------------------------------------------------------------------------------------------+
THIS SOFTWARE AND ALL THE ACCOMPANYING FILES ARE PROVIDED "AS IS" AND                              
WITHOUT ANY WARRANTIES EXPRESSED OR IMPLIED INCLUDING BUT NOT LIMITED                              
TO IMPLIED WARRANTIES OF MERCHANT ABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

IN NO  EVENT SHALL I BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING
WITHOUT  LIMITATION,  DAMAGES  FOR  LOSS  OF  BUSINESS  PROFITS,   BUSINESS
INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
ARISING OUT OF THE USE OR INABILITY TO USE THIS PRODUCT.
------------------------------------------------------------------------------------------------------

+----------------------------------------------------------------------------------------------------+
|Special and very useful info for newbies and lamers:                                                |
+----------------------------------------------------------------------------------------------------+
	Don't use this program!!! Especially, if you don't know what EEPROM is and what
is his purpose...This program can quickly and painless kill your phone. Repair of this dead phone -
ONLY your own problem!Probability of my answers to email like "I killed my phone!
Please, help me repair it!" - is MINIMAL. 

+----------------------------------------------------------------------------------------------------+
|Attention for cool programmers:                                                                     |
+----------------------------------------------------------------------------------------------------+

Don't bother me with your remarks about this program. I did it as good as I could.
If I can, I will improve it. If you can do this better - write your own program.
It's better.
------------------------------------------------------------------------------------------------------

+----------------------------------------------------------------------------------------------------+
|                            How To work with Siemens EEPROM tool                                    |
+----------------------------------------------------------------------------------------------------+

Program interface is easy as calculator. :-)

	There are 2 lists with information about EEPROM blocks, you can drag-&-drop blocks between them.
Right list assosiated with phone EEPROM blocks, left - with user's EEPROM data.
Of course, movements have no effect to phone until appropriate button with 'save'-action is pressed.
	Main program's window have 2 information areas and 1 area which displays initialisation 
information.
Funtctionality of last one is easy for understanding: select appropriate COM port, press "Init"	and afer
that - quickly press power button on the phone (with red phone sign). Left information area contains 
information about mobile phone which was obtained from phone using Service Mode commands. Not all phones
support this commands. On C/S35 program displays only hardware and firmware versions. On SL45/A3x/A40 
program displays all information, except IMEI. On S/ME45 and higher - program display all valuable info.
	Right information area fills after mobile phone initialisation and refreshes after finalisation 
writing to EEPROM. As shown in interface, this area display information about free space...In general, 
program realize this feature, but....I am not sure about it, how's correct this info. :-)

Well, let's look on buttons in left area of main program's window. As I think, it's easy to understand 
their functions.
I just want to explain some things. When you save EEPROM blocks in bin and txt formats, in addition to
file which
contains EEPROM block data, program creates another small file (*.bid or *.tid, correspondingly).
This file contains information about block number and his version. I think it's comfortably: main file
contains only EEPROM block data, so you can edit it without thinking about other matters Informational
files can be created manually (just look into file and you will understand file structure) if you intend
to load to phone self-modified data.
Of course, you can load blocks to phone without having informational files. If program can't find
informational files, you will be asked about destination block number and his version. If you mark
several blocks, then, when you save them in *.bin and *.txt formats, program will add prefix (block number)
to file name.

About *.eep format...There are few tricks:

1. Theoretically, this format compatible with file format of Eeprom_tool by DarkBear.
 I don't know  exactly. how Eeprom_tool' will recognize my file format, but (!) if
you have old backup's from this tool, my program will import all necessary data without problem.

2. If you mark only one block, then program will save all EEPROM, else - only selected blocks.
If you want to save one block in *.eep format  for example- just leave him and delete other blocks.

	That's all about saving. Loading blocks looks similar, so, I want to
explain some tricks:

If you mark several files for loading (files may be in any format - eep, bin, txt or map),
they will be processed in order which equal to order in list in program window! Therefore,
if program will find repeated blocks, they will be replaced to blocks which found in list later.
You should pay attention to it, especially in "InitMap mappings" loading process
(this feature appears in Siemens EEPROM tool v2.x): when you load "general"
standart  mapping + delta-mapping with operator configurations. Also this
"mappings" has yet another one feature: really, InitMap use not all blocks,
which is  saved in map. Not all blocks must be loaded in phone...But, if you really
need to load them, Siemens EEPROM tool can do this: when program find such blocks
in loading list, you will be asked. If you press "Yes" - program load all blocks,
if "No" - only blocks, which loading by original InitMap.

	Finally, let me say some words about actual work with phone (right set
of buttons in program window). Button "Load all" loads all EEPROM blocks into
program buffer. Program CAN'T load (and write) EEPROM blocks containing IMEI information
(except 'OpenBfB' phones). Button "Save all" save to phone all blocks containing
in list in right section of main program window. During this process old blocks
in EEPROM will be erased!!! Exactly, will be erased EELITE, but it's not so
important, because there is no command to delete EEFULL (exactly, this command
exist, but don't work). Cosidering named fact, that is not all blocks can be loaded to phone,
you shoul be very carefull with "Save all" button...;-)
Button "Save selected" is more usefull. This button save only selected blocks without
deleting old blocks. Using button "Load custom" you can set manually exact numbers of
EEPROM blocks (you can define set of blocks using comma to separate them or whole band
using "-"). Also program has very useful button ("Delete directly") which allows to user
delete block not only from list,  but and from phone, escaping other blocks.

	Also I want to speek about block descriptions, which can be seen
in right column in each list. They are taken from comments to "InitMap mappings"
and related with phone model. So, program display first appropriate block description
which found in program dictionary. Sometimes it's not good, for example, blocks from SL45
EEPROM have another description, and, therefore, another value.
For such cases program has special checkbox - "Check hardware ver for description".
If this checkbox is set to "Checked", program display only that descriptions, which
is strictly related with current phone model (of course, if program "knows" what
phone model is...) But, if you are using whole set of descriptions (checkbox is set to "unchecked"),
you have a greate chance to understand meaning maximum count of blocks. I think, it's good...:-)
Except this, Siemens EEPROM tool package contains small tool ("GetMapDesc") for
самостоятельного creating sets of descriptions from "InitMap mappings". To use this tool simply
run it and select approtiate input files. After that, this tool will create file "eeprom.dsc"
contained description of EEPROM blocks and mobile phone type. But, you must remember,
that in future Siemens EEPROM tool will use nearest description of block, so  place
information about specific mobile phones at the end of list in "eeprom.dsc".

+----------------------------------------------------------------------------------------------------+
|Hardware & software requirements                                                                    |
+----------------------------------------------------------------------------------------------------+

1. Program works with mobile phones via usual data cable with external power supply.
COM, USB - it's not so important. Main condition - data cable chips should not get power
from phone.
2. Program works under Win'95 and higher (except WinNT 4.0).
3. Program requires following files:
		                      msvbvm5.dll
                		      MSCOMM32.OCX
		                      COMCTL32.OCX
		                      comdlg32.ocx
If you haven't that files (program doesn't work and/or shows errors related with that files),
you must get them from any source (Internet, Visual Studio disc etc.) and place in system folder.
4. Program works on 486 PC (or better).
5. If program runs and shows no errors, it's a kind of garantie thatloading data to phone
is correct. Siemes made "Service mode" smart and safe: each command and each block is 
verifuing using CRC. Now, program has "solid like rock" algoritm, which, theoretically, works
good, even data cable isn't attached to phone. ;-)))
6. If you want to inform me about found errors or bugs, please mail me with attached COM-port
logs. You must create them using LGComSpy (http://latex.hotbox.ru). Please, DO NOT send
logs created using other logger (like PortMon etc.).

+----------------------------------------------------------------------------------------------------+
| GREETINGS!!!!                                                                                      |
+----------------------------------------------------------------------------------------------------+

Well, that's all what I want to say. I hope, that this tool will be useful to someone.
I want to say my biggest respect to "SK", who was the first user of Siemens EEPROM tool,
and to "Viper_rus", who selflessly tested 2nd version of program. :-)
Also my respect goes out to "The Sig" (thesig.spils.lv), whose descriptions of BfB95eg.dll
I used sometimes.

I'd like to express my deep gratitude to all my friends and familiars. Thanks in advance to all people,
who will place my modest program on his/her Internet site. :-))))

Please feel free to send me bug reports and feature requests. Good luck! :-)))


        	                                   (c) Copyright Skylord, 2002, 2003.
	                                                            sky_lord@mail.ru
This manual translated to english
by RussianBear.
E-mail: russian-bear@mail.ru