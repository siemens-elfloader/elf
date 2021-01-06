int miss1=0,miss2=0,miss3=7;
//TextBox("Кровавая баня","Вы должны отстоять Урюпинск"," 1. Убить 1  медведя",miss1," 2. Построить арбу",miss2,"",miss3); - пример Цели миссии
void mission1()
{
  
  sprintf(zag,"Кровавая баня");
  sprintf(all,"Вы должны отстоять Урюпинск");
  sprintf(cel1," 1. Убить 1  медведя");
  sprintf(cel2," 2. Построить арбу");
  sprintf(cel3,"");//пусто
  miss1=0;
  miss2=0;
  miss3=-1;//если не 1 и не 0 то пусто
  if(strcmp(GetTerrainNames[npic (cursorX,cursorY)], "Арба")==0)
  {
    miss2=1;
  }
}
