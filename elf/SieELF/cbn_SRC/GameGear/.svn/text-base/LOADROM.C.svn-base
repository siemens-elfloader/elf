/*
    loadrom.c --
    File loading and management.
*/

#include "shared.h"

char game_name[PATH_MAX];

typedef struct {
    uint32 crc;
    int mapper;
    int display;
    int territory;
    char *name;
} rominfo_t;

rominfo_t game_list[] = {
    {0x29822980, MAPPER_CODIES, DISPLAY_PAL, TERRITORY_EXPORT, "Cosmic Spacehead"},
    {0xB9664AE1, MAPPER_CODIES, DISPLAY_PAL, TERRITORY_EXPORT, "Fantastic Dizzy"},
    {0xA577CE46, MAPPER_CODIES, DISPLAY_PAL, TERRITORY_EXPORT, "Micro Machines"},
    {0x8813514B, MAPPER_CODIES, DISPLAY_PAL, TERRITORY_EXPORT, "Excellent Dizzy (Proto)"},
    {0xAA140C9C, MAPPER_CODIES, DISPLAY_PAL, TERRITORY_EXPORT, "Excellent Dizzy (Proto - GG)"}, 
    {-1        , -1  , NULL},
};

int load_rom(char *filename)
{
    strcpy(game_name,filename);
    int i;
    int size;
    if(cart.rom){
        mfree(cart.rom);
        cart.rom = NULL;
    }
//    if(0 || check_zip(filename))
//    {
//        char name[PATH_MAX];
//        cart.rom = loadFromZipByName(filename, name, &size);
//        if(!cart.rom) return 0;
//        strcpy(game_name, name);
//    }
//    else
//    {
    if(!(cart.rom=(uint8*)loadfile(filename))) return 0;
    size=loadfilesize;
//        int fd = NULL;
//
//        fd = fopen(filename,A_ReadOnly+A_BIN,0,&err);
//        if(fd==-1) return 0;
//
//        /* Seek to end of file, and get size */
//        size=lseek(fd, 0, 2, &err,&err);
//        lseek(fd, 0, 0, &err,&err);
//
//        cart.rom = (unsigned char*)malloc(size);
//        if(!cart.rom) return 0;
//        fread32(fd, cart.rom, size, &err);
//
//        fclose(fd,&err);
//    }

    /* Don't load games smaller than 16K */
    if(size < 0x4000) return 0;

    /* Take care of image header, if present */
    if((size / 512) & 1)
    {
        size -= 512;
        memmove((signed char*)cart.rom, (signed char*)cart.rom + 512, size);
    }

    cart.pages = (size / 0x4000);
    cart.crc = 0;//crc32(0, cart.rom, size);////!!!!

    /* Assign default settings (US NTSC machine) */
    cart.mapper     = MAPPER_SEGA;
    sms.display     = DISPLAY_NTSC;
    sms.territory   = TERRITORY_EXPORT;

    /* Look up mapper in game list */
//    for(i = 0; game_list[i].name != NULL; i++)
//    {
//        if(cart.crc == game_list[i].crc)
//        {
//            cart.mapper     = game_list[i].mapper;
//            sms.display     = game_list[i].display;
//            sms.territory   = game_list[i].territory;
//        }
//    }

    /* Figure out game image type */
    //if(1)// || stricmp(strrchr(game_name, '.'), ".gg") == 0) //!!!!!!!!!!!!!
    i=*((unsigned char*)(filename+strlen(filename)-1))|0x20;
    //if((*(filename+strlen(filename)-1)|0x20)!='s')
    if(i!=0x73)
        sms.console = CONSOLE_GG;
    else
        sms.console = CONSOLE_SMS; 

    system_assign_device(PORT_A, DEVICE_PAD2B);
    system_assign_device(PORT_B, DEVICE_PAD2B);

    return 1;
}

