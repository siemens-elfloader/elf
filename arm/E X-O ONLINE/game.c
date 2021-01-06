#include "../inc/swilib.h"
#include "externs.h"


//Ход на пустую клетку
int RandXod(int anti_flag)
{
  int i=0, j=0;
  for(i=1;i<=6;i++)
  {  for(j=1;j<=5;j++)
     {  if (TableXod[i][j]==0)
        {   TableXod[i][j]=anti_flag;
            DoFring();
            return 0;
	}
     }
  }
  return 0;
}

int ReturnDes(int a)
{
     int i=0, j=0;
     while(a>10) 
     { 
           i-=10; //получаем количество единиц
           j++;   //получаем количество десятков
     }
     return j;
}

int ReturnEd(int a)
{
     int i=0, j=0;
     while(a>10) 
     { 
           i-=10; //получаем количество единиц
           j++;   //получаем количество десятков
     }
     return i;
}

int Step_1_2_3_4( int tx_o_1, int tx_o_2, int tx_t_1, int tx_t_2, int tx_fr_1, int tx_fr_2, int tx_fo_1, int tx_fo_2,int flag, int anti_flag)
{
  if( TableXod[tx_o_1][tx_o_2]==flag && TableXod[tx_t_1][tx_t_2]==flag && TableXod[tx_fr_1][tx_fr_2]==flag ) 
  {
       if (TableXod[tx_fo_1][tx_fo_2]==0)
       {
			TableXod[tx_fo_1][tx_fo_2]=anti_flag;
                        DoFring();
                        return 1;
       }

  }
  return 0;
}
void DoFring()
{
  FringFig(1);
  FringFig(2);
}

int Step_3_4_5_2( int tx_o_1, int tx_o_2, int tx_t_1, int tx_t_2, int tx_fr_1, int tx_fr_2, int tx_fo_1, int tx_fo_2,int flag, int anti_flag)
{
  if( TableXod[tx_o_1][tx_o_2]==flag && TableXod[tx_t_1][tx_t_2]==flag && TableXod[tx_fr_1][tx_fr_2]==flag ) 
  {
       if (TableXod[tx_fo_1][tx_fo_2]==0)
       {
			TableXod[tx_fo_1][tx_fo_2]=anti_flag;
                        DoFring();
                        return 1;
       }

  }
  return 0;
}

int Step_1_2_3( int tx_o_1, int tx_o_2, int tx_t_1, int tx_t_2, int tx_fr_1, int tx_fr_2,int flag, int anti_flag)
{
  if( TableXod[tx_o_1][tx_o_2]==flag && TableXod[tx_t_1][tx_t_2]==flag ) 
  {
       if (TableXod[tx_fr_2][tx_fr_2]==0)
       {
			TableXod[tx_fr_2][tx_fr_2]=anti_flag;
                        DoFring();
                        return 1;
       }

  }
  return 0;
}


int A_I2(int flag, int anti_flag)
{
  int no_danger=0;
     //Вертикально
  for(int i=1;i<=6;i++)
  {
    if(Step_1_2_3(i,1, i,2, i,3,  flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3(i,2, i,3, i,4,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(i,3, i,4, i,5,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(i,4, i,5, i,3,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(i,3, i,4, i,2,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(i,2, i,3, i,1,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,1, i,2, i,3, i,4, anti_flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,1, i,2, i,3, i,4, flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,3, i,4, i,5, i,2, anti_flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,3, i,4, i,5, i,2, flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,1, i,2, i,4, i,3, anti_flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,1, i,2, i,4, i,3, flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,2, i,4, i,5, i,3, anti_flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,2, i,4, i,5, i,3, flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,2, i,3, i,4, i,5, anti_flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3_4(i,2, i,3, i,4, i,5, flag, anti_flag))no_danger=1;
   }
  

  
    //Горизонтально  
    for(int j=1;j<=5;j++)
  {
    if(no_danger==0&&Step_1_2_3(1,j, 2,j, 3,j,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(2,j, 3,j, 4,j,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(3,j, 4,j, 5,j,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(4,j, 5,j, 6,j,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(5,j, 6,j, 4,j,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(5,j, 4,j, 3,j,  flag, anti_flag))no_danger=1; 
    if(no_danger==0&&Step_1_2_3(4,j, 3,j, 2,j,  flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3(3,j, 2,j, 1,j,  flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(1,j, 2,j, 3,j, 4,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(2,j, 3,j, 4,j, 5,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(3,j, 4,j, 5,j, 6,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(4,j, 5,j, 6,j, 3,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(3,j, 4,j, 5,j, 2,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(2,j, 3,j, 4,j, 1,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(1,j, 2,j, 4,j, 3,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(3,j, 5,j, 6,j, 4,j, anti_flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(2,j, 4,j, 5,j, 3,j, anti_flag, anti_flag))no_danger=1;
    
    if(no_danger==0&&Step_1_2_3_4(1,j, 2,j, 3,j, 4,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(2,j, 3,j, 4,j, 5,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(3,j, 4,j, 5,j, 6,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(4,j, 5,j, 6,j, 3,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(3,j, 4,j, 5,j, 2,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(2,j, 3,j, 4,j, 1,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(1,j, 2,j, 4,j, 3,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(3,j, 5,j, 6,j, 4,j, flag, anti_flag))no_danger=1;
    if(no_danger==0&&Step_1_2_3_4(2,j, 4,j, 5,j, 3,j, flag, anti_flag))no_danger=1;
  }



    
   //Диагональ
   if(no_danger==0&&Step_1_2_3(1,4, 2,3, 3,2,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(2,3, 3,2, 4,1,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(4,1, 3,2, 2,3,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(2,3, 3,2, 1,4,  flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3(1,5, 2,4, 3,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(2,4, 3,3, 4,2,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(3,6, 4,2, 5,1,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(4,2, 5,1, 3,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(4,2, 3,3, 2,4,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(2,4, 3,3, 1,5,  flag, anti_flag))no_danger=1; 
     
   if(no_danger==0&&Step_1_2_3(2,5, 3,4, 4,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(2,4, 4,3, 5,2,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(3,6, 5,2, 6,1,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(5,2, 6,1, 4,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(5,2, 4,3, 2,4,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(2,4, 4,3, 2,5,  flag, anti_flag))no_danger=1; 
     
   if(no_danger==0&&Step_1_2_3(3,5, 4,4, 5,3,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(4,4, 5,3, 6,2,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(6,2, 5,3, 4,4,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(4,4, 5,3, 3,5,  flag, anti_flag))no_danger=1; 
     
   // 2-ая диагональ 
   if(no_danger==0&&Step_1_2_3(6,4, 5,3, 4,2,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(5,3, 3,2, 3,1,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(3,1, 3,2, 5,3,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(5,3, 3,2, 6,4,  flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3(4,5, 3,4, 2,3,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(3,4, 3,2, 1,2,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(1,2, 3,2, 3,4,  flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3(3,4, 3,2, 4,5,  flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3(6,5, 5,4, 4,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(5,4, 4,3, 3,2,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(3,6, 3,2, 2,1,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(3,2, 2,1, 4,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(3,2, 4,3, 5,4,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(5,4, 4,3, 6,5,  flag, anti_flag))no_danger=1;  
     
   if(no_danger==0&&Step_1_2_3(5,5, 4,4, 3,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(4,4, 3,3, 2,2,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(3,6, 2,2, 1,1,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(2,2, 1,1, 3,3,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(2,2, 3,3, 4,4,  flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3(4,4, 3,3, 5,5,  flag, anti_flag))no_danger=1;  
   
     
     
     
     

    
  

   //Диагональ
   if(no_danger==0&&Step_1_2_3_4(1,2, 2,3, 3,4, 4,5, anti_flag, anti_flag))no_danger=1;


   if(no_danger==0&&Step_1_2_3_4(2,3, 3,4, 4,5, 1,2, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(1,2, 3,4, 4,5, 2,3, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(1,2, 3,4, 4,5, 2,3, anti_flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(1,1, 2,2, 3,3, 4,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 4,4, 5,5, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,3, 4,4, 5,5, 2,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 4,4, 1,1, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(1,1, 2,2, 4,4, 3,3, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 5,5, 4,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(1,1, 3,3, 4,4, 2,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 5,5, 4,4, anti_flag, anti_flag))no_danger=1; 
     
   if(no_danger==0&&Step_1_2_3_4(2,1, 3,2, 4,3, 5,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 5,4, 6,5, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,3, 5,4, 6,5, 3,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 5,4, 2,1, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,1, 3,2, 5,4, 4,3, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 6,5, 5,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,1, 4,3, 5,4, 3,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 6,5, 5,4, anti_flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(3,1, 4,2, 5,3, 6,4, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(4,2, 5,3, 6,4, 3,1, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(3,1, 5,3, 6,4, 4,2, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(3,1, 5,3, 6,4, 4,2, anti_flag, anti_flag))no_danger=1;  
   // 2-ая диагональ 
   if(no_danger==0&&Step_1_2_3_4(6,2, 5,3, 4,4, 3,5, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(5,3, 4,4, 3,5, 6,2, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(6,2, 4,4, 3,5, 5,3, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(6,2, 4,4, 3,5, 5,3, anti_flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(4,1, 3,2, 2,3, 1,4, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(3,2, 2,3, 1,4, 4,1, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(4,1, 2,3, 1,4, 3,2, anti_flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(4,1, 2,3, 1,4, 3,2, anti_flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(6,1, 5,2, 4,3, 3,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 3,4, 2,5, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,3, 3,4, 2,5, 5,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 3,4, 6,1, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(6,1, 5,2, 3,4, 4,3, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 2,5, 3,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(6,1, 4,3, 3,4, 5,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 2,5, 3,4, anti_flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(5,1, 4,2, 3,3, 2,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 2,4, 1,5, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,3, 2,4, 1,5, 4,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 2,4, 5,1, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,1, 4,2, 2,4, 3,3, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 1,5, 2,4, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,1, 3,3, 2,4, 4,2, anti_flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 1,5, 2,4, anti_flag, anti_flag))no_danger=1;
     
      
  
    
  

   //Диагональ
   if(no_danger==0&&Step_1_2_3_4(1,2, 2,3, 3,4, 4,5, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(2,3, 3,4, 4,5, 1,2, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(1,2, 3,4, 4,5, 2,3, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(1,2, 3,4, 4,5, 2,3, flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(1,1, 2,2, 3,3, 4,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 4,4, 5,5, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,3, 4,4, 5,5, 2,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 4,4, 1,1, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(1,1, 2,2, 4,4, 3,3, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 5,5, 4,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(1,1, 3,3, 4,4, 2,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,2, 3,3, 5,5, 4,4, flag, anti_flag))no_danger=1; 
     
   if(no_danger==0&&Step_1_2_3_4(2,1, 3,2, 4,3, 5,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 5,4, 6,5, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,3, 5,4, 6,5, 3,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 5,4, 2,1, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,1, 3,2, 5,4, 4,3, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 6,5, 5,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(2,1, 4,3, 5,4, 3,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,2, 4,3, 6,5, 5,4, flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(3,1, 4,2, 5,3, 6,4, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(4,2, 5,3, 6,4, 3,1, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(3,1, 5,3, 6,4, 4,2, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(3,1, 5,3, 6,4, 4,2, flag, anti_flag))no_danger=1;  
   // 2-ая диагональ 
   if(no_danger==0&&Step_1_2_3_4(6,2, 5,3, 4,4, 3,5, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(5,3, 4,4, 3,5, 6,2, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(6,2, 4,4, 3,5, 5,3, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(6,2, 4,4, 3,5, 5,3, flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(4,1, 3,2, 2,3, 1,4, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(3,2, 2,3, 1,4, 4,1, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(4,1, 2,3, 1,4, 3,2, flag, anti_flag))no_danger=1;
   if(no_danger==0&&Step_1_2_3_4(4,1, 2,3, 1,4, 3,2, flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(6,1, 5,2, 4,3, 3,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 3,4, 2,5, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,3, 3,4, 2,5, 5,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 3,4, 6,1, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(6,1, 5,2, 3,4, 4,3, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 2,5, 3,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(6,1, 4,3, 3,4, 5,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,2, 4,3, 2,5, 3,4, flag, anti_flag))no_danger=1;
     
   if(no_danger==0&&Step_1_2_3_4(5,1, 4,2, 3,3, 2,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 2,4, 1,5, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(3,3, 2,4, 1,5, 4,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 2,4, 5,1, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,1, 4,2, 2,4, 3,3, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 1,5, 2,4, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(5,1, 3,3, 2,4, 4,2, flag, anti_flag))no_danger=1; 
   if(no_danger==0&&Step_1_2_3_4(4,2, 3,3, 1,5, 2,4, flag, anti_flag))no_danger=1;
     
   if(!no_danger) RandXod(anti_flag);


 DoFring();
 
 return 0;
}

void KompXod()
{
   if(end_game==0 || nich==0)
   {
   switch(MODE_FIGURE)
   {
                  case 1: A_I2(1, 2); break;
                  case 2: A_I2(2, 1); break;
   }
   count++;
   }
}

// Рисуем Крестик или Нолик
void DrawXorO(int flag,int x_p, int y_p)
{
  switch(flag)
  {
   case 1:// X
   DrwImg(images[1], x_p, y_p);
   break;
   case 2: // O
   DrwImg(images[0], x_p,y_p);
   break;
  }
}

void Count_1_gamer()
{
    if(summ_count1)
      {
      count_gamer_num_1++;
      summ_count1=0;
      }
}

void Count_2_gamer()
{
    if(summ_count2)
      {
      count_gamer_num_2++;
      summ_count2=0;
      }
}

void DrawIsGamerStatus(int flag)
{
  WSHDR *ws_res = AllocWS(128);
  ena_two_g=0, end_game=1;
  GBS_StopTimer(&timer);
  switch(flag)
  {
    case 1:
          if(MODE_GAME>2)
          {
                   if(MODE_FIGURE==1)
                   {
                           Count_1_gamer();
                           wsprintf(ws_res,perc_t,"Первый игрок выиграл!");
                   }
                   else 
                   if(MODE_FIGURE==2)
                   {
                           Count_2_gamer();
                           wsprintf(ws_res,perc_t,"Второй игрок выиграл!");
                   }
           }
           else
           {
                   switch(MODE_FIGURE)
                   {
                   case 1: Count_1_gamer();
                           wsprintf(ws_res,perc_t,"Вы выиграли!");
                           break;
                   case 2: Count_2_gamer();
                           wsprintf(ws_res,perc_t,"Вы проиграли!");
                           break;
                   }
            }
   break;
   case 2:
         if(MODE_GAME>2)
         {
                   switch(MODE_FIGURE)
                   {
                   case 1:  Count_2_gamer();
                            wsprintf(ws_res,perc_t,"Второй игрок выиграл!");
                            break;
                   case 2:  Count_1_gamer();
                            wsprintf(ws_res,perc_t,"Первый игрок выиграл!");
                            break;
                   }
         }
         else
         {
                   switch(MODE_FIGURE)
                   {
                   case 1:  Count_2_gamer();
                            wsprintf(ws_res,perc_t,"Вы проиграли!");
                            break;
                   case 2:  Count_1_gamer();
                            wsprintf(ws_res,perc_t,"Вы выиграли!");
                            break;
                   }
         }
   }   
  DrawString(ws_res,0,35,ScreenW(),ScreenW(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws_res);
}

void DrRF_R_U(int flag,int x,int y)
{
  isDrawFring=1;
  DrawIsGamerStatus(flag);
  for(int i=0;i<=3;i++)
    DrawRoundedFrame(x+20*i, y+20*i, x+20*i+20, y+20*i + 20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);
}

void DrRF_R_D(int flag,int x,int y)
{
  isDrawFring=1;
  DrawIsGamerStatus(flag);
  for(int i=0;i<=3;i++)
   DrawRoundedFrame(x-20*i, y+20*i, x-20*i+20, y+20*i + 20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);
}

void DrRF_DOWN(int flag,int x, int y)
{
  isDrawFring=1;
  DrawIsGamerStatus(flag);
  for(int i=0;i<=3;i++)
   DrawRoundedFrame(x, y+20*i,x+20, y+20*i+20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);
}

void DrRF_LEFT(int flag,int x, int y)
{
  isDrawFring=1;
  DrawIsGamerStatus(flag);
  for(int i=0;i<=3;i++)
   DrawRoundedFrame(x+20*i, y ,x+20*i+20, y+20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);
}


void FringFig(int flag)
{
  for(int i=1;i<=6;i++)
  {
    for(int j=1;j<=6;j++)
    {
    if(j<3&&TableXod[i][j]==flag&&TableXod[i][j+1]==flag&&TableXod[i][j+2]==flag&&TableXod[i][j+3]==flag){DrRF_DOWN(flag,9+36*(i-1),126+36*(j-1));break;}//линия по Y
    if(j<6&&i<4&&TableXod[i][j]==flag&&TableXod[i+1][j]==flag&&TableXod[i+2][j]==flag&&TableXod[i+3][j]==flag){DrRF_LEFT(flag,9+36*(i-1),126+36*(j-1));break;}//линия по X
     }
  }
  
 //------------------------------------------------------------------------------     
 if(  TableXod[1][1]==flag && TableXod[2][2]==flag && TableXod[3][3]==flag && TableXod[4][4]==flag ) DrRF_R_U(flag,5,70); else
 if(  TableXod[1][2]==flag && TableXod[2][3]==flag && TableXod[3][4]==flag && TableXod[4][5]==flag ) DrRF_R_U(flag,5,90); else
 if(  TableXod[2][2]==flag && TableXod[3][3]==flag && TableXod[4][4]==flag && TableXod[5][5]==flag ) DrRF_R_U(flag,25,90); else
 if(  TableXod[2][1]==flag && TableXod[3][2]==flag && TableXod[4][3]==flag && TableXod[5][4]==flag ) DrRF_R_U(flag,25,70); else
 if(  TableXod[3][2]==flag && TableXod[4][3]==flag && TableXod[5][4]==flag && TableXod[6][5]==flag ) DrRF_R_U(flag,45,90); else
 if(  TableXod[3][1]==flag && TableXod[4][2]==flag && TableXod[5][3]==flag && TableXod[6][4]==flag ) DrRF_R_U(flag,45,70); else
   
 if(  TableXod[6][2]==flag && TableXod[5][3]==flag && TableXod[4][4]==flag && TableXod[3][5]==flag ) DrRF_R_D(flag,105,90); else   
 if(  TableXod[6][1]==flag && TableXod[5][2]==flag && TableXod[4][3]==flag && TableXod[3][4]==flag ) DrRF_R_D(flag,105,70); else    
 if(  TableXod[5][2]==flag && TableXod[4][3]==flag && TableXod[3][4]==flag && TableXod[2][5]==flag ) DrRF_R_D(flag,85,90); else    
 if(  TableXod[5][1]==flag && TableXod[4][2]==flag && TableXod[3][3]==flag && TableXod[2][4]==flag ) DrRF_R_D(flag,85,70); else    
 if(  TableXod[4][2]==flag && TableXod[3][3]==flag && TableXod[2][4]==flag && TableXod[1][5]==flag ) DrRF_R_D(flag,65,90); else       
 if(  TableXod[4][1]==flag && TableXod[3][2]==flag && TableXod[2][3]==flag && TableXod[1][4]==flag ) DrRF_R_D(flag,65,70);  
}



void OXod(int flag)
{
  for(int i=1;i<=6;i++)
    for(int j=1;j<=6;j++)
  {
#ifdef ELKA
    if(TableXod[i][j]==flag)DrawXorO(flag,9+36*(i-1),126+36*(j-1));
#else
    if(TableXod[i][j]==flag)DrawXorO(flag,5+20*(i-1),70+20*(j-1));
#endif
  }
}

void NullGame()
{
      for(int i=1;i<=6;i++)
       for(int j=1;j<=6;j++)
        TableXod[i][j]=0;
}
