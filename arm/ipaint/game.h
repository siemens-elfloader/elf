void win()
{
   if(ball.y+ball.height>316&&ball.x>80&&ball.x+ball.width<160){cpu.g++;init();}//���
   if(ball.y<3&&ball.x>80&&ball.x+ball.width<160){user.g++;init();}//���
}
void enter()//���� ������ ��� ����� �� �����)))
{
  if(ball.x==user.x&&ball.y==user.y||ball.x==cpu.x&&ball.y==cpu.y)
  {
     if(lico==2)//�����
     {
  ball.dy=-sila;
  ball.dx=0;
     }
     if(lico==8)//����
     {
  ball.dy=sila;
  ball.dx=0;
     }
     if(lico==4)//�����
     {
  ball.dx=-sila;
   ball.dy=0;
     }
     if(lico==6)//������
     {
  ball.dx=sila;
   ball.dy=0;
     }
  if(lico==1)//����-�����
  {
    ball.dy=-sila/2;
    ball.dx=-sila/2;
  }
  if(lico==7)//����-���
  {
    ball.dy=sila/2;
    ball.dx-=sila/2;
  }
  if(lico==3)//�����-����
  {
    ball.dy=-sila/2;
    ball.dx=sila/2;
  }
  if(lico==9)//�����-���
  {
    ball.dy=sila/2;
    ball.dx=sila/2;
 }
  ball.x+=ball.dx;
  ball.y+=ball.dy;
  win();//������?
  }
}



void move_ball()
{
  xy2xy(&cpu.x,&cpu.y,&cpu.dx,&cpu.dy,&ball.x,&ball.y,1);
  if(cpu.x<3||cpu.x+cpu.width>237||cpu.y<3||cpu.y+cpu.height>310)//����� ��� � ��� �������
  {
    cpu.dx=cpu.dy=0;
  }
  if((ball.x!=uservr.x&&ball.y!=uservr.y)&&(ball.x!=cpuvr.x&&ball.y!=cpuvr.y))//���� �� � ��������
  {
  xrx(&cpu,&ball);
  xrx(&user,&ball);
  if(cpu.x==ball.x&&cpu.y==ball.y)
  {
   xy2xy(&cpu.x,&cpu.y,&cpu.dx,&cpu.dy,&udar.x,&udar.y,2);
  
  if(cpu.x==udar.x&&cpu.y==udar.y)//��������� - �������
  {
   ball.dx=0;
   ball.dy=40;
   ball.x+=ball.dx;
   ball.y+=ball.dy;
  }
  }
  } 
}

