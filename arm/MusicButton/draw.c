/*
void InitTags()
{
  if(player0&&IsPlayerOn()){strcpy(Name,"Не работает!!!!!");}
  if(player1&&IsIvoOn)strcpy(Name,IvoTag);
  if(player2&&IsMaplayerOn)strcpy(Name,Info->trackName);
  if(player3&&IsSPlayerOn){}
  if(!IsPlayerOn()&&!IsIvoOn&&!IsMaplayerOn&&!IsSPlayerOn)wsprintf(ws,"");
  else wsprintf(ws,Name);
}
void Draw(){InitTags();DrawString(ws,TAGSPOS.x,TAGSPOS.y,TAGSPOS.x2,TAGSPOS.y2,FONT,TEXT_ALIGNMIDDLE,COLOR,NULL);}
void DrawTags()
{
  switch(TAGSType)
  {
  case 2:break;
  case 0:
    if(ShowInfo&&ShowTimer<15)
    {
      Draw();ShowTimer++;
    }
    else {ShowInfo=0;ShowTimer=0;}
    break;
  case 1:Draw();break;
  }
  GBS_StartTimerProc(&RedrawTimer,20,DrawTags);
}
*/
