/*
* Ping-Pong 2009 - 2010
* keys
* (c) Danil_e71
*/

#include "keys.h"


void left_but()
{

  switch(status)
  {
  case game:    
    if (user.x!=1)user.dx=LEFT_SIDE;
    else user.dx=STOP_SIDE;break;
    case menu:
    if(cur_y==nimg*52){if(game_new_cont==3)game_new_cont=2;else if(game_new_cont==4)game_new_cont=3;}else
    if(cur_y==nimg*92){if(saveload==1)saveload=2;}else
    if(cur_y==nimg*132){if(mode==1)mode=0;lives=0;game_new_cont=1;}
    RedrawScreen();
    break;
    case settings_igra:
      if(cur_y==nimg*(52+40))
      {
    switch(difficult)
      {
    case 1:difficult=0;break;
    case 2:difficult=1;break;
      }
      }
      else
    if(cur_y==nimg*(52+(40*3)))
    {
    switch(speed_game)
      {
      case 1:speed_game=0;break;
      case 2:speed_game=1;break;
      case 3:speed_game=2;break;
      }
    }
    else
     if(cur_y==nimg*(52+(40*5))){if(mode==1)lives--;if (lives<1)lives=99;
    }
       game_new_cont=1;
       if(mode==0)savedata(1);
    RedrawScreen();
   break;
   case music:
       if(cur_y==nimg*(52+40)){if(on_off_sound==1){on_off_sound=0;}else{if(on_off_sound==2){on_off_sound=1;}}}
       if(cur_y==nimg*(52+(40*3))){def_vol--;if (def_vol<0)def_vol=6;}
       if(cur_y==nimg*(52+(40*5))){if(vibra==1){vibra=0;}}
    RedrawScreen();
    break;
   }
}

void right_but()
{
  if(status==game)
  {
     if (user.x!=max_width-user.width-1){user.dx=RIGHT_SIDE;}
       else {user.dx=STOP_SIDE;}
  }
  else
  {
  switch(status)
  {
        case menu:
       if (cur_y==nimg*52){if(game_new_cont==2)game_new_cont=3;else if(game_new_cont==3)game_new_cont=4;}
       if (cur_y==nimg*92){ if(saveload==2){saveload=1; }}
       if (cur_y==nimg*132){if(mode==0){savedata(1);mode=1;lives=7;game_new_cont=1;}}
       RedrawScreen();
     break;
  case settings_igra:
       if(cur_y==nimg*(52+40)){ if(difficult==1){difficult=2; } if(difficult==0){difficult=1;}}
       if(cur_y==nimg*(52+(40*3))){ if(speed_game==2){speed_game=3;} if(speed_game==1){speed_game=2;} if(speed_game==0){speed_game=1;}   }
       if (cur_y==nimg*(52+(40*5))&mode==1) { lives++; if (lives>99)lives=1;}
       game_new_cont=1;
       if(mode==0)savedata(1);
       RedrawScreen();
     break;
  case music:
      if(cur_y==nimg*(52+40)){if(on_off_sound==1){on_off_sound=2;} if(on_off_sound==0){on_off_sound=1;}}
      
      if(cur_y==nimg*(52+(40*3))){ def_vol++; if (def_vol>6)def_vol=0;}
      if(cur_y==nimg*(52+(40*5))){if(vibra==0){vibra=1;}}
      RedrawScreen();
     break;
  }
  }
}

void up_but()
{
  switch(status)
  {
  case load:
    if(isload)
    {
        cur_y=cur_y-nimg*40; if (cur_y<nimg*112){cur_y=nimg*152;}
        if(cur_y==nimg*112){langenru=0;}
        if(cur_y==nimg*152){langenru=1;}
        load_lang();
    }
    break;
  case menu:
        cur_y=cur_y-nimg*40; if (cur_y<nimg*52){cur_y=nimg*(5*40+52);}
        RedrawScreen();
    break;
  case settings:
        cur_y=cur_y-nimg*40; if (cur_y<nimg*52){cur_y=nimg*(1*40+52);}
        RedrawScreen();
    break;
  case settings_igra:
        cur_y=cur_y-nimg*40; if (cur_y<nimg*52+40){cur_y=nimg*(5*40+52);}
        for(int i=0;i<5;i+=2)if(cur_y==nimg*(i*40+52))cur_y=nimg*((i-1)*40+52);
        RedrawScreen();
    break;
  case music:
        cur_y=cur_y-nimg*40; if (cur_y<nimg*52+40){cur_y=nimg*(5*40+52);}
        for(int i=0;i<5;i+=2)if(cur_y==nimg*(i*40+52))cur_y=nimg*((i-1)*40+52);
        RedrawScreen();
       break;
  }
}

void down_but()
{
    switch(status)
  {
    case load:
        if(isload==1)
    {
        cur_y=cur_y+nimg*40; if (cur_y>nimg*152){cur_y=nimg*112;}
        if(cur_y==nimg*112)langenru=0;
        if(cur_y==nimg*152)langenru=1;
        load_lang();
     }
     break;
    case menu:
        cur_y=cur_y+nimg*40; if (cur_y>nimg*nimg*(5*40+52)){cur_y=nimg*52;}
        RedrawScreen();
        break;
      case settings:
        cur_y=cur_y+nimg*40; if(cur_y>nimg*nimg*(1*40+52)){cur_y=nimg*52;}
        RedrawScreen();
        break;
  case settings_igra:
        cur_y=cur_y+nimg*40; if(cur_y>nimg*(5*40+52)){cur_y=nimg*52;}
        for(int i=0;i<5;i+=2)if(cur_y==nimg*(i*40+52))cur_y=nimg*((i+1)*40+52);
        RedrawScreen();
    break;
    case music:
        cur_y=cur_y+nimg*40; if(cur_y>nimg*(5*40+52)){cur_y=nimg*52;}
        for(int i=0;i<5;i+=2)if(cur_y==nimg*(i*40+52))cur_y=nimg*((i+1)*40+52);
         RedrawScreen();
    break;
  }
}

void enter_but()
{
  switch(status)
  {
  case load:
          if(isload==1)
   {
         lgpInitLangPack();
         savedata(2);
         isload=0;
         T_Load_IMG();
   }
     break;
  case menu:
        if(cur_y==nimg*52)startcont();
        if (cur_y==nimg*252)exit();
        if (cur_y==nimg*92){if (saveload==1){saveSettings();}else if (saveload==2)loadSettings();}
        if (cur_y==nimg*172){status=rec;cur_y=nimg*52;}
        if(cur_y==nimg*212){status=settings;cur_y=nimg*52;}
        RedrawScreen();
    break;
  case settings:
    if(cur_y==nimg*52){status=settings_igra;cur_y=nimg*52+nimg*40;}else
      if(cur_y==nimg*(52+40)){status=music;cur_y=nimg*52+nimg*40;}

      RedrawScreen();
    break;
  }
}

void left_soft()
{
        if (status==game)
       {
        running=0;
        PlayMelody_PausePlayback(PLAY_ID);
        if(IsTimerProc(&tmr))GBS_StopTimer(&tmr);
        status=menu;
        game_new_cont=3;
        RedrawScreen();
       }
}

void right_soft()
{

  switch(status)
  {
  case settings:
       status=menu; 
       cur_y=nimg*52;
       RedrawScreen();
    break;
  case settings_igra:
       status=settings;
       cur_y=nimg*52;
       RedrawScreen();
    break;
  case music:
      status=settings;
      cur_y=nimg*52;
      RedrawScreen();
     break;
  case rec:
          status=menu;
          cur_y=nimg*52;
          RedrawScreen();
         break;
  }
}

void green_but()
{
  if(status==rec)
  {
          savedata(0);
          RedrawScreen();
  }
}

void resh_but()
{
  if(status==menu)
  {
   openconf();
   running=0;
  }
}
