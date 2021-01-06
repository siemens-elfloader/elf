void sleep(int i)
{
  TTime t,t2;
  GetDateTime(0,&t);
  while(i)
  {
   GetDateTime(0,&t2);
   if(t2.sec!=t.sec)
    {
	  i--;
	  t=t2;
    }	
  }  
}