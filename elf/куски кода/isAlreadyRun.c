int IsAlreadyRunning()
{
    int found = 0;
    CSM_RAM *icsm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next; 
    while((((unsigned int)(icsm->constr)>>27)==0x15)&& (!found) )
    {
      WSHDR *tws=(WSHDR *)(((char *)icsm->constr)+sizeof(CSM_DESC));
      if((tws->ws_malloc==NAMECSM_MAGIC1)&&(tws->ws_mfree==NAMECSM_MAGIC2))
      {
        if (!memcmp(tws->wsbody+1, MAINCSM.maincsm_name.wsbody+1, tws->wsbody[0]*2))
          found = 1;
      }
      icsm=icsm->next;
    } 
}