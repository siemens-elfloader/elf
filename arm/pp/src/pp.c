/*
* Ping-Pong 2009 - 2010
* pp
* (c) Danil_e71
*/

#include "pp.h"
#include "other.h"
void move_block()
{
  if (user.dx==LEFT_SIDE)shift_block(-user.speed);//влево
  if (user.dx==RIGHT_SIDE)shift_block(user.speed);//вправо
}

void shift_block(int shift)
{ 
    if (user.x<-shift)user.x=0;
    else if (((user.x+shift+user.width)>max_width)&&(shift>0))user.x=max_width-user.width;
    else user.x+=shift;
}

void shift_cpu(int shift)
{
  if (cpu.x<-shift)cpu.x=0;
  else if (((cpu.x+shift+cpu.width)>max_width)&&(shift>0))cpu.x=max_width-cpu.width;
  else cpu.x+=shift;
}

void move_ball()
{
  if ((ball.x+ball.width>=user.x)&&(ball.x<=(user.x+user.width))&&(ball.y+ball.dy>user.y-user.height))
  { 
    ball.dy*=-1;
    if (((ball.x<=user.x-ball.width/2)&&(ball.dx>0)) || ((ball.x>=user.x+user.width-ball.width/2)&&(ball.dx<0)))
      {
       ball.dx*=-1; 
       ball.y=user.y-ball.height;
      } //разворот м€ча если попадает в угол битка          
    else
    { //отклонени€ м€ча при попадании в биток
      switch (user.dx)
      {
      case LEFT_SIDE: ball.dx-=2; break;
      case RIGHT_SIDE: ball.dx+=2; break;
      }
      }
    if(on_off_sound==1)Play(1);
    start_vibra(0,2);
  }
  else
  {
//отражение от битка "бота"     
  if ((ball.x>=cpu.x)&&(ball.x<=(cpu.x+cpu.width))&&((ball.y+ball.dy)<(cpu.y+cpu.height)))
  {
    ball.dy*=-1;
    if (((ball.x<=cpu.x-ball.width/2)&&(ball.dx>0)) || ((ball.x>=(cpu.x+cpu.width-ball.width/2))&&(ball.dx<0)))
      {
      ball.dx*=-1; 
      ball.y=cpu.y+cpu.height;
      } //разворот м€ча если попадает в угол битка          
    else{
      if (ball.x<(cpu.x+cpu.width/2)) {  //в левую часть       
        ball.dx-=1;
      }else{//в правую часть
        ball.dx+=1;    
      }
    }
    if(on_off_sound==1)Play(1);
    start_vibra(0,2);
  }
  }
//ограничение ускорени€ по x
  if (ball.dx>7){ball.dx=7;}
  if (ball.dx<-7){ball.dx=-7;}
//отражение от боковых стенок и движение м€ча по х
  if ((ball.x+ball.dx)<=1){ball.x=1; ball.dx*=-1;}//левой
  if ((ball.x+ball.dx)>=max_width-ball.width-1){ball.x=max_width-ball.width-1; ball.dx*=-1;}//правой
  ball.x+=ball.dx;
  ball.y+=ball.dy;
  AI();// вызов »»
  win();
}

void AI()
{
 if (ball.y<AI_line)
 {     
    if (ball.x>=cpu.x+cpu.width/2+ball.width/2)
    {
      if (ball.dx<cpu.speed&&ball.x<cpu.x+cpu.width*3/4&&ball.dx>=0)
      shift_cpu(ball.dx);
      else shift_cpu(cpu.speed);
    }
    else
    if (ball.x<=(cpu.x+cpu.width/2-ball.width/2))
    {
      if (ball.dx>-cpu.speed&&ball.x>cpu.x+cpu.width/4&&ball.dx<=0)
      shift_cpu(ball.dx);
      else shift_cpu(-cpu.speed);
     }
  }
 else
 { //отодвигаем биток телефона от кра€
    if (cpu.x<(cpu.width/2))shift_cpu(cpu.speed);
    if (((cpu.x+cpu.width))>(max_width-cpu.width/2))shift_cpu(-cpu.speed);
}
}

void start_vibra(int type,int sec)
{
  if(vibra)
  {
  void stop_vibra(void);
  if(!IsCalling())
  {
    switch(type)
    {
  case 1:SetVibration(15);break;//√ол
  case 0:SetVibration(40);break;//ќб ракетки
    }
     GBS_StartTimerProc(&vibr,(TMR_SECOND/2)>>sec,stop_vibra);
  }
  }
}

void stop_vibra(void)
{
  SetVibration(0);
}

void win() // провер€ем выиграл ли кто-то... 
{
  WSHDR *ws = AllocWS(48);
  if (mode==1)
  {
    wsprintf(ws,"%t:%d %d cpu:%d %d ¬рем€: %s",name,user.lifetime,user.round,cpu.lifetime,cpu.round,Time.str);
    if (ball.y>(user.y+user.height/2)){--user.lifetime;start_vibra(1,1);gdy=0; setgame(0); stop(1);}
    else
    if (ball.y<(cpu.y-cpu.height/2)){--cpu.lifetime;start_vibra(1,1);gdy=1; setgame(0); stop(2); }    
    if (user.lifetime==0){gameover();cpu.round++;}
    if (cpu.lifetime==0){gameover();user.round++;}
   }
  if (mode==0)
  {
   if (ball.y>(user.y+user.height/2)){++cpu.lifetime;start_vibra(1,1);gdy=0; setgame(0); stop(1);}
  else
   if (ball.y<(cpu.y-cpu.height/2)){++user.lifetime;start_vibra(1,1); gdy=1;AI_line-=3; cpu.speed++; if(user.speed>5){user.speed--;}setgame(0); stop(2); }    
   wsprintf(ws,"%t:%d cpu:%d ¬рем€: %s",name,user.lifetime,cpu.lifetime,Time.str);
  } 
  DrawString(ws,2,1,2+Get_WS_width(ws,FONT),1+GetFontYSIZE(FONT),FONT,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(9),NULL);
  FreeWS(ws);
}

void gameover()//≈сли кто проиграл\выиграл
{

  if (user.lifetime==0)outtextxy(lang[47]);
  else if (cpu.lifetime==0)outtextxy(lang[48]);
  user.lifetime=cpu.lifetime=lives;
}

void setgame(int newgame) //1-newgame; 0-continue
{
 switch(mode)
 {
 case 1:
   if(newgame)user.lifetime=cpu.lifetime=lives;
   switch(difficult)
      {
      case 0:
        AI_line = nimg*140;
        user.speed=12;
        cpu.speed=10;
        break;
      case 1:
        AI_line = nimg*110;
        user.speed=11;
        cpu.speed=11;
        break;
      case 2: 
        AI_line = nimg*90;
        user.speed=10;
        cpu.speed=17;
        break;
      }
   break;
 case 0:
   AI_line=nimg*120;
   if(newgame)user.lifetime=cpu.lifetime=0;
   break;
 }   

 user.x=(max_width-user.width)/2;
 user.y=(max_height-user.height-1);
 ball.x=(max_width-ball.width)/2;
 cpu.x=(max_width-cpu.width)/2;
 cpu.y=nimg*24;
 user.dx=STOP_SIDE;
 if (rndindex==64){rndindex=0;}
 ball.dx=rndtable[(++rndindex-5)]; //по рандому
 switch(speed_game)
 {
 case 0:ball.dy=10;break;
 case 1:ball.dy=12;break;
 case 2:ball.dy=14;break;
 case 3:ball.dy=17;break;
 }
 switch(gdy)
 {
 case 1:ball.dy*=-1;ball.y=user.y-user.height;break;
 case 0:ball.dy*=1;ball.y=cpu.y+cpu.height;break;
 }
 status=game;
}

void setpause()
{
  if(running)
  {
  running=0;
  RedrawScreen();
  if(IsTimerProc(&tmr))GBS_StopTimer(&tmr);
  PlayMelody_PausePlayback(PLAY_ID);
  outtextxy(lang[50]);
  }
  else
  {
   status=game;
   running=1;
   if(on_off_sound)PlayMelody_ResumePlayBack(PLAY_ID);
   RedrawScreen();
  }
}

void stop(int type)
{ 
  if(running)
  {
    running=0;
    RedrawScreen();
    if(IsTimerProc(&tmr))GBS_DelTimer(&tmr);
  }
  switch(type)
  {
  case 1:outtextxy(lang[51]);break;
  case 2:outtextxy(lang[52]);break;
  }
 }
