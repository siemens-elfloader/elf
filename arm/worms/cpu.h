void vratary()//��� �������
{
  if(ball.y>270&&ball.x+ball.width>=40&&ball.x<=200)//���� ��� � ��������
  {
    if(ball.x==user.x&&ball.y==user.y)//���� ��� � ����
 {
  xy2xy(&uservr.x,&uservr.y,&uservr.dx,&uservr.dy,&uservr.x0,&uservr.y0,2);//���� � �������
 }
  else//���� �� � ����
    {
   xy2xy(&uservr.x,&uservr.y,&uservr.dx,&uservr.dy,&ball.x,&ball.y,2);//��������
 xrx(&uservr,&ball);
 if(ball.x==uservr.x&&ball.y==uservr.y)
 {
 if(cpu.y>150)//���� �����
   {
     cpu.dy=-2;
   //  cpu.dx=0;
   }
 else
 {
   cpu.dy=0;//����� ����
   ball.y+=-120;
 }
 }
  
  }
  }
  else
  {
  xy2xy(&uservr.x,&uservr.y,&uservr.dx,&uservr.dy,&uservr.x0,&uservr.y0,1);//���� � �������
  }


    if(ball.y<50&&ball.x+ball.width>=40&&ball.x<=200)
  {
    if(ball.x==cpu.x&&ball.y==cpu.y)
 {
   xy2xy(&cpuvr.x,&cpuvr.y,&cpuvr.dx,&cpuvr.dy,&cpuvr.x0,&cpuvr.y0,2);
 }
    else
    {
 xy2xy(&cpuvr.x,&cpuvr.y,&cpuvr.dx,&cpuvr.dy,&ball.x,&ball.y,2);
 xrx(&cpuvr,&ball);
if(ball.x==cpuvr.x&&ball.y==cpuvr.y)
 {
  if(cpu.y<150)
   {
     cpu.dy=2;
     
   }
 else
 {
   cpu.dy=cpu.dx=0;
   ball.y+=120;
 }
 }
  
 
    }
  }
  else
  {
   xy2xy(&cpuvr.x,&cpuvr.y,&cpuvr.dx,&cpuvr.dy,&cpuvr.x0,&cpuvr.y0,1);
  }
    cpu.y+=cpu.dy;
    
}
