// Клавиатурные хуки ;)

void RunIdlePanel()
{
  if ( NumOfItems_idle > 0)
  {
    IdleMenuActive=1;
    DrawIdleMenu();
  }
  else EditConfig();
}

int IDLE_KeyHook(int submsg, int msg)// Это хук, действующий на IDLE.
{
  CSM_RAM *data=FindCSMbyID(CSM_root()->idle_id);
  if(IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует
    {
#ifdef ELKA
      {
#else
      void *idata=GetDataOfItemByID(igui,2);
      if (idata)
      {
#endif
        if((IsUnlocked())&&(!FastRunMenuActive))
        {
          if((!IDLE_CALL_BUTTON)&&(!IDLE_EXIT_BUTTON))
          {
            if ((msg==KEY_DOWN)||(msg==LONG_PRESS))// Если клавиша нажата или зажата
            {
              switch(submsg)
              {
                case LEFT_BUTTON:// Джой влево
                  Selected_idle--;// Курсор назад
                  if(Selected_idle<0)
                    Selected_idle=NumOfItems_idle-1; // Если пришли к началу, возвращаемся в конец
                  DrawIdleMenu(); // И перерисовываем саму панель
                  return (2); 
       
                case RIGHT_BUTTON:// Джой вправо
                  Selected_idle++;// Курсор вперед
                  if(Selected_idle >= NumOfItems_idle)
                    Selected_idle=0;// Если уткнулись в конец, возврат в начало
                  DrawIdleMenu(); // Снова перерисовываем
                  return (2);
       
                case ENTER_BUTTON:// Тыкаем на джой
                  IdleMenuActive=0;
                  RunAction(Selected_idle,1);// И запускаем выделенную закладку
                  return (2);
              }
            }
          }
          else
          {
            if(IdleMenuActive)
            {
              if ((msg==KEY_DOWN)||(msg==LONG_PRESS))// Если клавиша нажата или зажата
              {
                switch(submsg)
                {
                  case LEFT_BUTTON:// Джой влево
                  case '4':
                    Selected_idle--;// Курсор назад
                    if(Selected_idle<0)
                      Selected_idle=NumOfItems_idle-1; // Если пришли к началу, возвращаемся в конец
                    DrawIdleMenu(); // И перерисовываем саму панель
                    return (2); // Возвращаем 2, чтобы кнопка больще ничего не запускала...
       
                  case RIGHT_BUTTON:// Джой вправо
                  case '6':
                    Selected_idle++;// Курсор вперед
                    if(Selected_idle >= NumOfItems_idle)
                      Selected_idle=0;// Если уткнулись в конец, возврат в начало
                    DrawIdleMenu(); // Снова перерисовываем
                    return (2);
       
                  case ENTER_BUTTON:// Тыкаем на джой
                  case '5':
                    IdleMenuActive=0;
                    RunAction(Selected_idle,1);// И запускаем выделенную закладку
                    return (2);
        
                  case '#':
                    IdleMenuActive=0;
                    EditConfig();
                    return (2);
        
                  case '0':
                    ShowMSG(2,(int)LG_COPYRIGHT);
                    return (2);
                }
              }
              if (submsg==IDLE_EXIT_BUTTON)// Кнопка закрытия панели. Тут все уже ясно
              {
                switch (msg)
                {
                  case KEY_DOWN:
                    IdleMenuActive=0;
                    PendedRedrawGUI();
                    DrawIdleMenu();
                    return (2);
                    
                  case LONG_PRESS:
                    return (2);
                }
              }
              else return (2);
            }
            else
            {
              if (submsg==IDLE_CALL_BUTTON)
              {
                switch(msg)
                {
                  case KEY_DOWN:
                    if (!ENA_IDLE_LONGPRESS)
                      RunIdlePanel();
                    else
                    {
                      if (mode_enter==2)
                      {
                        GBS_SendMessage(MMI_CEPID,KEY_UP,IDLE_CALL_BUTTON);
                        return (0);
                      }
                      mode_enter=0;
                    }
                    return (2);
                    
                  case KEY_UP:
                    if (ENA_IDLE_LONGPRESS)
                    {
                      if (mode_enter==0)
                      {
                        mode_enter=2;
                        GBS_SendMessage(MMI_CEPID,KEY_DOWN,IDLE_CALL_BUTTON);
                        return (2);
                      }
                      if (mode_enter==2)
                      {
                        mode_enter=0;
                        return (0);
                      }
                      mode_enter=0;
                    }
                    return (2);
                  case LONG_PRESS:
                    if (ENA_IDLE_LONGPRESS)
                    {
                      mode_enter=1;
                      RunIdlePanel();
                    }
                    break;
                }
              }
            }
          }
        }
      }
    }
  }
  return (0);
}

int FastRun_KeyHook(int submsg, int msg)// Вызов панели FastRun
{
if((IsUnlocked())&&(!FastRunMenuActive))
{
    if (submsg==FR_CALL_BUTTON)
    {
      switch(msg)
      {
        case KEY_DOWN:
          if (!ENA_FR_LONGPRESS)
          {
            RunFastRunPanel();//RunFastRunPanel();
            return(2);
          }
          else
          {
            if (mode_enter==2)
            {
              GBS_SendMessage(MMI_CEPID,KEY_UP,FR_CALL_BUTTON);
              return (0);
            }
            mode_enter=0;
            return (2);
          }
          
        case KEY_UP:
          if (ENA_FR_LONGPRESS)
          {
            if (mode_enter==0)
            {
              mode_enter=2;
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,FR_CALL_BUTTON);
              return (2);
            }
            if (mode_enter==2)
            {
              mode_enter=0;
              return (0);
            }
            mode_enter=0;
            return (2);
          }
          
        case LONG_PRESS:
          if (ENA_FR_LONGPRESS)
          {
            mode_enter=1;
            RunFastRunPanel();//RunFastRunPanel();
          }
          break;
      }
    }
  }
return(0); 
}
