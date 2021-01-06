/*
    state.c --
    Save state management.
*/

#include "shared.h"

void system_save_state(int fd)
{
    char *id = STATE_HEADER;
    uint16 version = STATE_VERSION;

    /* Write header */
    fwrite(fd, id, sizeof(id), &err);
    fwrite(fd, &version, sizeof(version), &err);

    /* Save VDP context */
    fwrite(fd, &vdp, sizeof(vdp_t), &err);

    /* Save SMS context */
    fwrite(fd, &sms, sizeof(sms_t), &err);

    fwrite(fd, cart.fcr, 4, &err);
//    fputc(cart.fcr[0], fd);
//    fputc(cart.fcr[1], fd);
//    fputc(cart.fcr[2], fd);
//    fputc(cart.fcr[3], fd);
    fwrite(fd, cart.sram, 0x8000, &err);

    /* Save Z80 context */
    fwrite(fd, Z80_Context, sizeof(Z80_Regs), &err);
    fwrite(fd, &after_EI, sizeof(int), &err);

    /* Save YM2413 context */
//    fwrite(FM_GetContextPtr(), FM_GetContextSize(), 1, fd);

    /* Save SN76489 context */
//    fwrite(SN76489_GetContextPtr(0), SN76489_GetContextSize(), 1, fd);
}


void system_load_state(int fd)
{
    int i;
//    uint8 *buf;
    char id[4];
    uint16 version;

    /* Initialize everything */
    z80_reset(0);
    z80_set_irq_callback(sms_irq_callback);
    system_reset();
//    if(snd.enabled)
//        sound_reset();

    /* Read header */
    fread(fd, id, 4, &err);
    fread(fd, &version, 2, &err);

    /* Load VDP context */
    fread(fd, &vdp, sizeof(vdp_t), &err);

    /* Load SMS context */
    fread(fd, &sms, sizeof(sms_t), &err);

    fread(fd, cart.fcr, 4, &err);
//    cart.fcr[0] = fgetc(fd);
//    cart.fcr[1] = fgetc(fd);
//    cart.fcr[2] = fgetc(fd);
//    cart.fcr[3] = fgetc(fd);
    fread(fd, cart.sram, 0x8000, &err);

    /* Load Z80 context */
    fread(fd, Z80_Context, sizeof(Z80_Regs), &err);
    fread(fd, &after_EI, sizeof(int), &err);

    /* Load YM2413 context */
//    buf = malloc(FM_GetContextSize());
//    fread(buf, FM_GetContextSize(), 1, fd);
//    FM_SetContext(buf);
//    free(buf);

    /* Load SN76489 context */
//    buf = malloc(SN76489_GetContextSize());
//    fread(buf, SN76489_GetContextSize(), 1, fd);
//    SN76489_SetContext(0, buf);
//    free(buf);

    /* Restore callbacks */
    z80_set_irq_callback(sms_irq_callback);

    for(i = 0x00; i <= 0x2F; i++)
    {
        cpu_readmap[i]  = &cart.rom[(i & 0x1F) << 10];
        cpu_writemap[i] = dummy_write;
    }

    for(i = 0x30; i <= 0x3F; i++)
    {
        cpu_readmap[i] = &sms.wram[(i & 0x07) << 10];
        cpu_writemap[i] = &sms.wram[(i & 0x07) << 10];
    }

    sms_mapper_w(3, cart.fcr[3]);
    sms_mapper_w(2, cart.fcr[2]);
    sms_mapper_w(1, cart.fcr[1]);
    sms_mapper_w(0, cart.fcr[0]);

    /* Force full pattern cache update */
    bg_list_index = 0x200;
    for(i = 0; i < 0x200; i++)
    {
        bg_name_list[i] = i;
        bg_name_dirty[i] = -1;
    }

    /* Restore palette */
    for(i = 0; i < PALETTE_SIZE; i++)
        palette_sync(i);
}

