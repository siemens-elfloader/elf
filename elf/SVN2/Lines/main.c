#include "..\inc\swilib.h"

#define TMR_SECOND 216

extern void kill_data(void *p, void (*func_p)(void *));
extern void srand(unsigned int);
extern int rand(void);
#define iNumOfColors 5 //Количество цветов 
#define iNumOfRows 9//Количество рядов (9 как в классическом)


int m_iNumOfRows;     // количество рядов игрового поля
int m_iNumOfColors;   //максимальное количество цветов
int m_iNumOfPoints;   //количество очков
int m_iNumOfBalls;    //количество шариков на поле
int cur_x=0;
int cur_y=0;

int m_iBallSize; //Текущий размер шарика (0 или 1)
int x0, y0; //кординаты текущего выбранного шарика

GBSTMR tmr;

int m_field[iNumOfRows][iNumOfRows];  //массив, задающий игровое поле
//Массив m_field задает игровое поле. Ноль будет означать, что поле свободно, а цифры от 1 до 7 - что поле занято (каждое число будет означать шарик определенного цвета).

    
    
#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

#pragma inline
void patch_rect(RECT* rc)
{
  rc->x=0;
  rc->y=YDISP;
  rc->x2=ScreenW()-1;
  rc->y2=ScreenH()-1;
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
}MAIN_GUI;



void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void SetField(int x, int y, int iColor);


void OnTimer(void) 
{
  // TODO: Add your message handler code here and/or call default
  m_iBallSize=!m_iBallSize;
  REDRAW();
  GBS_StartTimerProc(&tmr,TMR_SECOND/2,OnTimer);
}

void Delete5InLine(int x1, int y1, int x2, int y2)
{
  //удаляет 5 шариков, расположенных в ряд
  //от поля (x1, y1) до поля (x2, y2).
  int i;
  //удаление по горизонтали
  if(y1==y2){
    for(i=x1;i<=x2;i++){
      SetField(i,y1,0);
    }
  }
  
  //удаление по вертикали
  if(x1==x2){
    for(i=y1;i<=y2;i++){
      SetField(x1,i,0);
    }
  }
  
  //удаление по диагонали сверху-слева - снизу-справа
  if((x1<x2) && (y1<y2)){
    for(i=x1;i<=x2;i++){
      SetField(i,y1-x1+i,0);
    }
  }
  
  //удаление по диагонали снизу-слева - сверху-справа
  if((x1>x2) && (y1<y2)){
    for(i=y1;i<=y2;i++){
      SetField(x1+y1-i,i,0);
    }
  }
}
        
int CalcPoints(int iNumDeletedBalls)
{
  int iRes;
  if(iNumDeletedBalls<5){
    return 0;
  }
  else{
    iRes = 2* iNumDeletedBalls*iNumDeletedBalls-20*iNumDeletedBalls+60;
  }
  return iRes;
}

int Is5InLine(int x, int y, int bAddPoints){
  //проверяет, есть ли 5 или более шариков подряд
  //int x1=x, y1=y;//координаты поля справа, слева и т.п.
  int i;//смещение относительно точки (x, y)
  int bSeeFuther;//смотрим ли далее
  
  //число совпадений вправо, влево, вверх и вниз
  int iO=0, iW=0, iN=0, iS=0;
  //число совпадений вправо-вверх, влево-вверх, вправо-вниз и влево
  int iNO=0, iNW=0, iSO=0, iSW=0;
  int bRes =0;//возвращемое значение
  
  //смотрим вправо
  bSeeFuther=1;
  i=1;
  while((x+i<iNumOfRows) && bSeeFuther){//если поле справа существует
    bSeeFuther=0;
    if(m_field[x+i][y]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iO++;//увеличиваем счётчик совпадений вправо
      bSeeFuther=1;
    }
    i++;
  };
  
  //смотрим влево
  bSeeFuther=1;
  i=1;
  while((x-i>=0) && bSeeFuther){//если поле слева существует
    bSeeFuther=0;
    if(m_field[x-i][y]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iW++;//увеличиваем счётчик совпадений влево
      bSeeFuther=1;
    }
    i++;
  };
  
  //смотрим вниз
  bSeeFuther=1;
  i=1;
  while((y+i<iNumOfRows) && bSeeFuther){//если поле снизу существует
    bSeeFuther=1;
    if(m_field[x][y+i]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iS++;//увеличиваем счётчик совпадений вниз
      bSeeFuther=1;
    }
    i++;
  }
  
  //вмотри вверх
  bSeeFuther=1;
  i=1;
  while((y-i>=0) && bSeeFuther){//если поле сверху существует
    bSeeFuther=0;
    if(m_field[x][y-i]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iN++;//увеличиваем счётчик совпадений вверх
      bSeeFuther=1;
    }
    i++;
  }

    /////////////проверки диагоналей/////////////
  
  //смотрим вправо-вниз
  bSeeFuther=1;
  i=1;
  //если поле справа внизу существует
  while((x+i<iNumOfRows) && (y+i<iNumOfRows) && bSeeFuther){
    bSeeFuther=0;
    if(m_field[x+i][y+i]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iSO++;//увеличиваем счётчик совпадений вправо вниз
      bSeeFuther=1;
    }
    i++;
  };
    
  //смотрим вверх-влево
  bSeeFuther=1;
  i=1;
  while((x-i>=0) && (y-i>=0) && bSeeFuther){//если поле слева вверху существует
    bSeeFuther=0;
    if(m_field[x-i][y-i]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iNW++;//увеличиваем счётчик совпадений вверх влево
      bSeeFuther=1;
    }
    i++;
  };
  
  //смотрим вправо-вверх
  bSeeFuther=1;
  i=1;
  while((x+i<iNumOfRows) && (y-i>=0) && bSeeFuther){//если поле справа вверху существует
    bSeeFuther=0;
    if(m_field[x+i][y-i]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iNO++;//увеличиваем счётчик совпадений вправо
      bSeeFuther=1;
    }
    i++;
  };
  
  //смотрим вниз-влево
  bSeeFuther=1;
  i=1;
  while((x-i>=0) && (y+i<iNumOfRows) && bSeeFuther){//если поле слева внизу существует
    bSeeFuther=0;
    if(m_field[x-i][y+i]==m_field[x][y]){//и его цвет совпадает с цветом (x,y)
      iSW++;//увеличиваем счётчик совпадений вправо
      bSeeFuther=1;
    }
    i++;
  };
  
  //запоминаем, сколько шариков было до удаления
  int iWasNumOfBalls = m_iNumOfBalls;
  if(iS+iN+1>=5){//есть 5 в ряд
    ShowMSG(1,(int)"5 в ряд по вертикали");
    Delete5InLine(x,y-iN,x,y+iS); 
    bRes=1;
    //return true;
  }
  
  if(iO+iW+1>=5){//есть 5 в ряд
    ShowMSG(1,(int)"5 в ряд по горизонтали");
    Delete5InLine(x-iW,y,x+iO,y);
    bRes=1;
    //return true;
  }

    
  //есть 5 в ряд по диагонали слева-сверху справа-снизу
  if(iNW+iSO+1>=5){
    ShowMSG(1,(int)"5 в ряд по диагонали слева-сверху справа-снизу");
    Delete5InLine(x-iNW,y-iNW,x+iSO,y+iSO);
    bRes=1;
    //return true;
  }
  
  //есть 5 в ряд по диагонали справа-сверху слева-снизу
  if(iSW+iNO+1>=5){
    ShowMSG(1,(int)"5 в ряд по диагонали справа-сверху слева-снизу");
    Delete5InLine(x+iNO,y-iSW,x-iNO,y+iSW);
    bRes=1;
    //return true;
  }
  
  if(bAddPoints){
    //(пока закомментируем)
    m_iNumOfPoints+=CalcPoints(iWasNumOfBalls-m_iNumOfBalls);
  }
  return bRes;//нет 5 в ряд
}



int IsPath(int xFrom, int yFrom, int xTo, int yTo)
{
  int iField[iNumOfRows][iNumOfRows];
  for(int j=0;j<iNumOfRows;j++){
    for(int i=0;i<iNumOfRows;i++){
      iField[i][j]=m_field[i][j];
    }
  }
  
  int iMaxPathLength=iNumOfRows*iNumOfRows+1;
  iField[xFrom][yFrom]=-1;//начальная точка
  iField[xTo][yTo]=iMaxPathLength;//конечная точка
  
  int iNextSearch=-1;
  int bContSearch = 1;
  while(bContSearch){
    bContSearch=0;
    for(int j=0;j<iNumOfRows;j++){
      for(int i=0;i<iNumOfRows;i++){
        //найдно очередное поле для перемещения.
        if(iField[i][j]==iNextSearch){
          //начинаем обследовать его соседей
          //поле располжено слева
          int bIsLeft=(i==0)?1:0;
          //поле располжено справа
          int bIsRight=(i==(iNumOfRows-1))?1:0;
          //поле располжено сверху
          int bIsTop=(j==0)?1:0;
          //поле располжено снизу
          int bIsButtom=(j==(iNumOfRows-1))?1:0;
          
          if(!bIsLeft){
            //если это искомое поле.
            if(iField[i-1][j]==iMaxPathLength){
              return 1;
            }
            if(iField[i-1][j]==0){//если поле слева свободно
              iField[i-1][j]=iNextSearch-1;
              bContSearch = 1;
            }
          }
          
          if(!bIsRight){
            //если это искомое поле
            if(iField[i+1][j]==iMaxPathLength){
              return 1;
            }
            //если поле справа свободно
            if(iField[i+1][j]==0){
              iField[i+1][j]=iNextSearch-1;
              bContSearch = 1;
            }
          }
          
          if(!bIsTop){
            //если это искомое поле.
            if(iField[i][j-1]==iMaxPathLength){
              return 1;
            }
            //если поле сверху свободно
            if(iField[i][j-1]==0){
              iField[i][j-1]=iNextSearch-1;
              bContSearch = 1;
            }
          }
          
          if(!bIsButtom){
            //если это искомое поле
            if(iField[i][j+1]==iMaxPathLength){
              return 1;
            }
            //если поле снизу свободно
            if(iField[i][j+1]==0){
              iField[i][j+1]=iNextSearch-1;
              bContSearch = 1;
            }
          }
        }
      }
    }
    iNextSearch--;
  };
  return 0;
}


void MoveBall(int xFrom, int yFrom, int xTo, int yTo){
  //обмен шарика и пустого места
  int iTmp;
  iTmp = m_field[xTo][yTo];
  SetField(xTo, yTo, m_field[xFrom][yFrom]);
  SetField(xFrom, yFrom, iTmp);
}

void SetField(int x, int y, int iColor)
{
  //устанавливает шарик цвета iColor
  m_field[x][y]=iColor;
  if (iColor>0 && iColor<8) m_iNumOfBalls++;  //увеличиваем счётчик количества шариков на поле
  else m_iNumOfBalls--;  //уменьшаем счётчик расположенных на поле шариков
  //SetModifiedFlag();//устанавливаем флаг изменения документа
}
//Переменную m_iNumOfBalls мы уменьшаем или увеличиваем на 1, в зависимости от того, ставим ли мы шарик (iColor больше нуля) или убираем его (iColor равно нулю).


int Throw3Balls(int iNum)
{
  int x, y;//место, в которое кидаем шарик
  int iColor; //цвет шарика
  if(iNum!=0)
  {
    for(int i=0;i<iNum;i++)
    {
      //выбор свободного места
      do
      {
        x=rand()%m_iNumOfRows;
        y=rand()%m_iNumOfRows;
      }
      while(m_field[x][y]!=0);
      //выбор цвета
      iColor=rand()%m_iNumOfColors+1;
      SetField(x,y,iColor); //ставим шарик нужного цвета
      Is5InLine(x, y, 0);
    }
    return (1);
  }
  else
  {
    ShowMSG(1,(int)"Игра закончена!");
    return (0);
  }
}
// ==============================================================================================

#define MIN(a,b) a<b?a:b
void OnRedraw(MAIN_GUI *data)
{ 
  unsigned int scr_w=ScreenW();
  unsigned int scr_h=ScreenH();
  unsigned int color;
  int x_off;
  int y_off;
  int xy_size=(MIN(scr_w,scr_h))/m_iNumOfRows;
  x_off=((MIN(scr_w,scr_h))-xy_size*m_iNumOfRows)>>1;
  y_off=(scr_h-MIN(scr_w,scr_h))>20?20:scr_h-MIN(scr_w,scr_h);
  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(20));
  wsprintf(data->ws1,"%d balls, %d points", m_iNumOfBalls, m_iNumOfPoints);
  DrawString(data->ws1,3,3,scr_w-3,3+GetFontYSIZE(SMALL_FONT),SMALL_FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

  for (int x=0; x<=m_iNumOfRows; x++)
  {
    DrawLine(x_off+x*xy_size,y_off,x_off+x*xy_size,y_off+m_iNumOfRows*xy_size,1,GetPaletteAdrByColorIndex(0));
  }
  for (int y=0; y<=m_iNumOfRows; y++)
  {
    DrawLine(x_off,y_off+y*xy_size,x_off+m_iNumOfRows*xy_size,y_off+y*xy_size,1,GetPaletteAdrByColorIndex(0));
  }
  
  // Нарисуем рамку текущего элемента
  DrawRectangle(xy_size*cur_x+x_off,xy_size*cur_y+y_off,xy_size*cur_x+xy_size+x_off,xy_size*cur_y+xy_size+y_off,
                0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  for(int j=0; j<m_iNumOfRows; j++)
  {
    for(int i=0; i<m_iNumOfRows; i++)
    {
      switch(m_field[i][j])
      {
      case 1:
        color=1;
        break;
          
      case 2:
        color=3;
        break;
        
      case 3:
        color=14;
        break;
        
      case 4:
        color=4;
        break;
        
      case 5:
        color=2;
        break;
        
      case 6:
        color=8;
        break;
        
      case 7:
        color=7;
        break;
        
      default:
        color=23;
        break;
      }
      if (m_iBallSize==1 && i==x0 && j==y0)
      {
        drawArc(xy_size*i+x_off+3,xy_size*j+y_off+3,xy_size*i+xy_size+x_off-3,xy_size*j+xy_size+y_off-3,360,360,
                0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(color));        
      }
      else
      {
        drawArc(xy_size*i+x_off,xy_size*j+y_off,xy_size*i+xy_size+x_off,xy_size*j+xy_size+y_off,360,360,
                0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(color));
      }
    
    
      
    }
  }

}


void OnCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  TTime tt;
  int n;
  data->ws1=AllocWS(256);

  m_iNumOfColors=7;//количество цветов (7 максимум)
  m_iNumOfRows=9;
  GetDateTime(0, &tt);
  n=tt.param+tt.min*60+tt.hour*3600;
  srand(n%32000); //Инициализируем датчик случайных чисел
  
  Throw3Balls(5);//кидаем пять начальных шариков.
  data->gui.state=1;
}

void OnClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void OnFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void OnUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void OnJClickUp(MAIN_GUI *data) 
{
  // TODO: Add your message handler code here and/or call default
  int x=cur_x;  //координата по горизонтали
  int y=cur_y;  //координата по вертикали
  static int bMove;   //щёлкаем ли во второй раз

  if(m_field[x][y]!=0){//т.е. если щёлкаем на шарике
     bMove=1;
     x0=x;//запоминем выбраный шарик
     y0=y;
     OnTimer();
  }
  else{//т. е. щелкаем не на шарике
    if(bMove)
    {//если шарик выбран
      if(IsPath(x0, y0, x, y))
      {       //ставим временную заглушку,    
                                      //т. е. считаем, что путь всегда существует
        GBS_DelTimer(&tmr);
        MoveBall(x0, y0, x, y);
        bMove=0;
        //если нет пяти в ряд
        if(!Is5InLine(x,y,1))
        {   //ставим временную заглушку,
          //т. е. считаем, пяти (или более) шариков  в ряд не существует
          //true-очки прибавляем
          //смотрим, сколько свободных полей осталось
          //и кидаем шарики
          if(m_iNumOfRows*m_iNumOfRows-m_iNumOfBalls>=3){
            Throw3Balls(3);
          }
          else{
            Throw3Balls(m_iNumOfRows*m_iNumOfRows-m_iNumOfBalls);
          }
          //Проверяем, есть не все ли клетки заняты
          //Если да, то заканчиваем игру
          if(m_iNumOfRows*m_iNumOfRows==m_iNumOfBalls){
            
          }
        }
      }
    }
  }
    
    //показываем в заголовке окна кол-во шариков
    
}
int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{

  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
    case '2':
    case UP_BUTTON:
      cur_y=cur_y-1<0?m_iNumOfRows-1:cur_y-1;
      break;
      
    case '4':
    case LEFT_BUTTON:
      cur_x=cur_x-1<0?m_iNumOfRows-1:cur_x-1;
      break;
      
    case '6':
    case RIGHT_BUTTON:
      cur_x=(cur_x+1)>=m_iNumOfRows?0:cur_x+1;
      break;
      
    case '8':
    case DOWN_BUTTON:
      cur_y=(cur_y+1)>=m_iNumOfRows?0:cur_y+1;
      break;
    }
    REDRAW();
  }
    
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON:
      OnJClickUp(data);
      REDRAW();
      return (-1);
    }
  }
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case LEFT_SOFT:
      break;

    case RIGHT_SOFT:
      return(1); 
      
    case GREEN_BUTTON:

      // TODO: add reinitialization code here
      // (SDI documents will reuse this document)
      m_iNumOfBalls=0; //Шариков на поле пока нет
      m_iNumOfPoints=0;//Количество очков (пока ноль)
      
      
      for(int j=0;j<m_iNumOfRows;j++){
        for(int i=0;i<m_iNumOfRows;i++){
          m_field[i][j]=0; //заполняем поле нулями
        }
      }
      Throw3Balls(5);
      break;
    }
  }
  
  return(-1);
}


int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)OnCreate,	//Create
  (void *)OnClose,	//Close
  (void *)OnFocus,	//Focus
  (void *)OnUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data, //method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
  }
  return(1);
}


void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((void *)(&Canvas));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&tmr);
  SUBPROC((void *)ElfKiller);
}

unsigned short maincsm_name_body[140];
const int minus11=-11;
const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Lines");
}

int main(char *exename, char *fname)
{
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return (0);
}
