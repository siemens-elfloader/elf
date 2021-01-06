#include <swilib.h>

#include "../include.h"
#include "language.h"
#include "../string_works.h"


std::string lgpData[LGP_DATA_NUM];


void lgpInitLangPack(void)
{
    /*FILE *hFile;
    char  lang_file[256];
    sprintf(elf_path,fname);
    if(elf_path[strlen(elf_path)-1]!='\\')elf_path[strlen(elf_path)-1]='\\';
    sprintf(lang_file,"%s%s",elf_path,resource[LANG]);



    char * buf;
    FSTATS fstat;

    if (GetFileStats(lang_file, &fstat, 0) != -1)
    {
        hFile = fopen(lang_file, "r");
        {
            buf =new char(fstat.size + 1);

            buf[fread(buf, 1,fstat.size,hFile)] = 0;
            fclose(hFile);



            char line[128];
            int lineSize = 0;
            int lp_id = 0;
            int buf_pos = 0;
            while(buf[buf_pos] && buf_pos < fstat.size && lp_id < LGP_DATA_NUM)
            {
                if (buf[buf_pos]=='\n' || buf[buf_pos]=='\r')
                {
                    if (lineSize > 0)
                    {
                        lgpData[lp_id] = new char(lineSize+1);
                        //memcpy(lgpData[lp_id], line, lineSize);
                        //lgpData[lp_id][lineSize] = 0;
                        lgpData[lp_id].assign(line, lineSize);

                        lp_id ++;
                        lineSize = 0;
                    }
                }
                else
                    line[lineSize ++] = buf[buf_pos];
                buf_pos ++;
            }
            if (lineSize > 0 && lp_id < LGP_DATA_NUM) // eof
            {
                lgpData[lp_id] = (char *)malloc(lineSize+1);
                //memcpy(lgpData[lp_id], line, lineSize);
                //lgpData[lp_id][lineSize] = 0;
                lgpData[lp_id].assign(line, lineSize);
                lp_id ++;
                lineSize = 0;
            }
            delete(buf);


            // old langpack
            if (lgpData[LGP_LangCode].length() > 2) {
                lgpData[LGP_LangCode] = "ru";
            }


            for (int i=0; i<LGP_DATA_NUM; ++i)
            {
                if (lgpData[i].empty()) {
                    lgpData[i] = "Error! Update language.lng!";
                }
            }
            return;

            fclose(hFile);
        }
    }
*/
    lgpData[LGP_LoadingMap] = (char *)"Loading map";
    lgpData[LGP_PressAnyKey] = (char *)"press any key";
    lgpData[LGP_Traffic] = (char *)"traffic";
    lgpData[LGP_State] = (char *)"state";
    lgpData[LGP_LoadingCache] = (char *)"loading cache";

    lgpData[LGP_LangCode]=             (char *)"en";
}


