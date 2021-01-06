void left()
{
  if(user.x>3)
  {
  user.x-=xy;
  }
  if(user.x<3)
  {
    user.x=3;
  }
 }
void right()
{
 if(user.x<217)
  {
  user.x+=xy;
  }
 if(user.x>237-user.width)
 {
   user.x=237-user.width;
 }
  
 }
void up()
{
 if(user.y>0)
 {
 user.y-=xy;
 }
if(user.y<0)
{
  user.y=0;
}

}

void down()
{
if(user.y<300)
{
user.y+=xy;
}
if(user.y>300)
{  
  user.y=300;
}
   
}

