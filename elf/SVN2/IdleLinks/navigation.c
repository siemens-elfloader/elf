#include "..\inc\swilib.h"
#include "IdleLinks.h"

extern TLabelData *TLabels;
extern TLabelData *Current;

TLabelData *GetFirstEnabled()
{
  TLabelData *result = TLabels;
  if(result->Enabled)
  {
    return result;
  }
  else
  {
    while (result->next)
    {
      result = result->next;
      if(result->Enabled)
      {
        return result;
      }
    }
  }
  return NULL;
}

TLabelData *GetLeftLink()
{
  //
  //  Возвращает ярлык с минимальной координатой по оси x
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // Пробегаемся по всему списку ярлычков
    {
      if(i->x <= result->x)    // Если новый ярлычок левее уже запомненного
      {
        if (i->x == result->x)
        {
          // Сравниваем по высоте
          if (i->y < result->y)
          {
            if (i->Enabled)
            {
              result = i;
            }
          }
        }
        else
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      i = i->next;
    }
    if(i->x <= result->x)    // Если новый ярлычок левее уже запомненного
    {
      if (i->x == result->x)
      {
        if (i->y < result->y)
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      else
      {
        if (i->Enabled)
        {
          result = i;
        }
      }
    }
    return result;
  }
  return NULL;
}

TLabelData *GetRightLink()
{
  //
  // Возвращает ярлык с максимальной координатой x
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // Пробегаемся по всему списку ярлычков
    {
      if(i->x >= result->x)    // Если новый ярлычок правее уже запомненного
      {
        if (i->x == result->x)
        {
          if (i->y > result->y)
          {
            if (i->Enabled)
            {
              result = i;
            }
          }
        }
        else
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      i = i->next;
    }
    if(i->x >= result->x)    // Если новый ярлычок правее уже запомненного
    {
      if(i->x == result->x)
      {
        if (i->y > result->y)
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      else
      {
        if (i->Enabled)
        {
          result = i;
        }
      }
    }
    return result;
  }
  return NULL;
}

TLabelData *GetUpLink()
{
  //
  //  Возвращает ярлык с минимальной координатой по оси y
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // Пробегаемся по всему списку ярлычков
    {
      if(i->y <= result->y)    // Если новый ярлычок ниже уже запомненного
      {
        if (i->y == result->y)
        {
          if (i->x < result->x)
          {
            if (i->Enabled)
            {
              result = i;
            }
          }
        }
        else
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      i = i->next;
    }
    if(i->y <= result->y)    // Если новый ярлычок ниже уже запомненного
    {
      if (i->y == result->y)
      {
        if(i->x < result->x)
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      else
      {
        if (i->Enabled)
        {
          result = i;
        }
      }
    }
    return result;
  }
  return NULL;
}

TLabelData *GetDownLink()
{
  //
  //  Возвращает ярлык с максимальной координатой по оси y
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // Пробегаемся по всему списку ярлычков
    {
      if(i->y >= result->y)    // Если новый ярлычок выше уже запомненного
      {
        if (i->y == result->y)
        {
          if (i->x > result->x)
          {
            if (i->Enabled)
            {
              result = i;
            }
          }
        }
        else
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      i = i->next;
    }
    if(i->y >= result->y)    // Если новый ярлычок выше уже запомненного
    {
      if (i->y == result->y)
      {
        if (i->x > result->x)
        {
          if (i->Enabled)
          {
            result = i;
          }
        }
      }
      else
      {
        if (i->Enabled)
        {
          result = i;
        }
      }
    }
    return result;
  }
  return NULL;
}

TLabelData *GetFirstLink()
{
  return GetLeftLink();
}


TLabelData *PrepareCompareSourseForFindNextLink(int key)
{
  switch(key)
  {
  case RIGHT_BUTTON:
    {
      return GetRightLink();
    }
  case LEFT_BUTTON:
    {
      return GetLeftLink();
    }
  case DOWN_BUTTON:
    {
      return GetDownLink();
    }
  case UP_BUTTON:
    {
      return GetUpLink();
    }
  }
  return GetFirstLink();
}

TLabelData *PrepareCompareSourseForCycledNavigation(int key)
{
  extern const unsigned int BCFG_CYCLED;
  if (BCFG_CYCLED == 1)
  {
    return Current;
  }
  else
  {
    switch(key)
    {
    case RIGHT_BUTTON:
      {
        return GetDownLink();
      }
    case LEFT_BUTTON:
      {
        return GetUpLink();
      }
    case DOWN_BUTTON:
      {
        return GetRightLink();
      }
    case UP_BUTTON:
      {
        return GetLeftLink();
      }
    }
    return GetFirstLink();
  }
}

TLabelData *GetLastLinkForCycledNavigation(int key)
{
  extern const unsigned int BCFG_CYCLED;
  if (BCFG_CYCLED == 1)
  {
    return Current;
  }
  else
  {
    switch(key)
    {
    case RIGHT_BUTTON:
      {
        return GetLeftLink();
      }
    case LEFT_BUTTON:
      {
        return GetDownLink();
      }
    case DOWN_BUTTON:
      {
        return GetLeftLink();
      }
    case UP_BUTTON:
      {
        return GetRightLink();
      }
    }
    return GetFirstLink();
  }
}
    
int CompareCoordinates(int Coordinate1, int Coordinate2)
  {
  if(Coordinate1 > Coordinate2)
  {
    return (Coordinate1 - Coordinate2);
  }
  else
  {
    return (Coordinate2 - Coordinate1);
  }
}

int CheckNextLink(int key, TLabelData *SelectedLabel, TLabelData *PrepareLabel, TLabelData *LastNextLabel)
{
  if (PrepareLabel->Enabled)
  {
    switch(key)
    {
    case RIGHT_BUTTON:
      {
        if(((GetRightLink()->x - PrepareLabel->x) < (GetRightLink()->x - SelectedLabel->x)) && ((GetRightLink()->x - PrepareLabel->x) > (GetRightLink()->x - LastNextLabel->x)))
        {
          return 1;
        }
        if(PrepareLabel->x == LastNextLabel->x)
        {
          if(CompareCoordinates(PrepareLabel->y, SelectedLabel->y) < CompareCoordinates(LastNextLabel->y, SelectedLabel->y))
          {
            return 1;
          }
        }
      }
      break;
    case LEFT_BUTTON:
      {
        if(((PrepareLabel->x - GetLeftLink()->x) < (SelectedLabel->x - GetLeftLink()->x)) && ((PrepareLabel->x - GetLeftLink()->x)>(LastNextLabel->x - GetLeftLink()->x)))
        {
          return 1;
        }
        if(PrepareLabel->x == LastNextLabel->x)
        {
          if(CompareCoordinates(PrepareLabel->y, SelectedLabel->y) < CompareCoordinates(LastNextLabel->y, SelectedLabel->y))
          {
            return 1;
          }
        }
      }
      break;
    case DOWN_BUTTON:
      {
        if(((GetDownLink()->y - PrepareLabel->y) < (GetDownLink()->y - SelectedLabel->y)) && ((GetDownLink()->y - PrepareLabel->y) > (GetDownLink()->y - LastNextLabel->y)))      
        {
          return 1;
        }
        if(PrepareLabel->y == LastNextLabel->y)
        {
          if(CompareCoordinates(PrepareLabel->x, SelectedLabel->x) < CompareCoordinates(LastNextLabel->x, SelectedLabel->x))
          {
            return 1;
          }
        }
      }
      break;
    case UP_BUTTON:
      {
        if(((PrepareLabel->y - GetUpLink()->y) < (SelectedLabel->y - GetUpLink()->y)) && ((PrepareLabel->y - GetUpLink()->y)>(LastNextLabel->y - GetUpLink()->y)))      
        {
          return 1;
        }
        if(PrepareLabel->y == LastNextLabel->y)
        {
          if(CompareCoordinates(PrepareLabel->x, SelectedLabel->x) < CompareCoordinates(LastNextLabel->x, SelectedLabel->x))
          {
            return 1;
          }
        }
      }
      break;
    }
  }
  return 0;
}
  
int CheckCycledNavigation(int key, TLabelData *SelectedLabel, TLabelData *PrepareLabel, TLabelData *LastNextLabel)
{
  if (PrepareLabel->Enabled)
  {
    extern const unsigned int BCFG_CYCLED;
    switch (BCFG_CYCLED)
    {
    case 0:
      {
        // Циклическая навигация выключена - тупо ничего не делаем ^_^
      }
      break;
    case 1:
      {
        // Переходим к первому ярлычку на текущей линии/столбце
        if (key == RIGHT_BUTTON)
        {
          // Если гуляем вперед по х ищем самый левый с точно такой же высотой,
          // как у текущего
          if (PrepareLabel->y == SelectedLabel->y)
          {
            if ((PrepareLabel->x < SelectedLabel->x) & (PrepareLabel->x < LastNextLabel->x))
            {
              return 1;
            }
          }
        }
        if (key == LEFT_BUTTON)
        {
          // Если гуляем назад по х ищем самый правый с точно такой же высотой,
          // как у текущего
          if (PrepareLabel->y == SelectedLabel->y)
          {
            if ((PrepareLabel->x > SelectedLabel->x) & (PrepareLabel->x > LastNextLabel->x))
            {
              return 1;
            }
          }
        }
        if (key == DOWN_BUTTON)
        {
          // Если гуляем вниз по у ищем самый верхний, с точно такой же 
          // координатой по х, как у текущего
          if (PrepareLabel->x == SelectedLabel->x)
          {
            if ((PrepareLabel->y < SelectedLabel->y) & (PrepareLabel->y < LastNextLabel->y))
            {
              return 1;
            }
          }
        }
        if (key == UP_BUTTON)
        {
          // Если гуляем вниз по у ищем самый нижний, с точно такой же 
          // координатой по х, как у текущего
          if (PrepareLabel->x == SelectedLabel->x)
          {
            if ((PrepareLabel->y > SelectedLabel->y) & (PrepareLabel->y > LastNextLabel->y))
            {
              return 1;
            }
          }
        }
      }
      break;
    case 2:
      {
        // Переходим к первому ярлычку на следующей линии столюце
        if (key == RIGHT_BUTTON)
        {
          // Если гуляем вперед по х ищем самый левый с наименьшей разницей
          //  в высоте, нежели у текущего
          if ((PrepareLabel->y > SelectedLabel->y) & ((GetDownLink()->y - PrepareLabel->y) >= (GetDownLink()->y - LastNextLabel->y)) & ((SelectedLabel->y - PrepareLabel->y) != 0))
          {
            if (PrepareLabel->y == LastNextLabel->y)
            {
              if (PrepareLabel->x < LastNextLabel->x)
              {
                return 1;
              }
            }
            else
            {
              return 1;
            }
          }
        }
        if (key == LEFT_BUTTON)
        {
          // Если гуляем назад по х ищем самый правый с точно такой же высотой,
          // как у текущего
          if ((PrepareLabel->y < SelectedLabel->y) & ((PrepareLabel->y - GetUpLink()->y) >= (LastNextLabel->y - GetUpLink()->y)) & ((SelectedLabel->y - PrepareLabel->y) != 0))
          {
            if (PrepareLabel->y == LastNextLabel->y)
            {
              if (PrepareLabel->x > LastNextLabel->x)
              {
                return 1;
              }
            }
            else
            {
              return 1;
            }
          }
        }
        if (key == DOWN_BUTTON)
        {
          // Если гуляем вниз по у ищем самый верхний, с точно такой же 
          // координатой по х, как у текущего
          if ((PrepareLabel->x > SelectedLabel->x) & ((GetRightLink()->x - PrepareLabel->x) >= (GetRightLink()->x - LastNextLabel->x)) & ((SelectedLabel->x - PrepareLabel->x) != 0))
          {
            if (PrepareLabel->x == LastNextLabel->x)
            {
              if (PrepareLabel->y < LastNextLabel->y)
              {
                return 1;
              }
            }
            else
            {
              return 1;
            }
          }
        }
        if (key == UP_BUTTON)
        {
          // Если гуляем вниз по у ищем самый нижний, с точно такой же 
          // координатой по х, как у текущего
          if ((PrepareLabel->x < SelectedLabel->x) & ((PrepareLabel->x - GetLeftLink()->x) >= (LastNextLabel->x - GetLeftLink()->x)) & ((SelectedLabel->x - PrepareLabel->x) !=0))
          {
            if(PrepareLabel->x == LastNextLabel->x)
            {
              if (PrepareLabel->y > LastNextLabel->y)
              {
                return 1;
              }
            }
            else
            {
              return 1;
            }
          }
        }
      }
      break;
    }
  }
  return 0;
}

void FindNextLink(int key)
{
  if (TLabels)
  {
    TLabelData *i = GetFirstEnabled();
    TLabelData *res = PrepareCompareSourseForFindNextLink(key);
    while(i->next)  // Пробегаемся по всему списку ярлычков
    {
      if (CheckNextLink(key, Current, i, res))
      {
        res = i;
      }
      i = i->next;
    }
    if (CheckNextLink(key, Current, i, res))
    {
      res = i;
    }
    if(Current!=res)
    {
      Current = res;
    }
    else
    {
      extern const unsigned int BCFG_CYCLED;
      if (BCFG_CYCLED)
      {
        // Здееся будет обработка зацикленной навигации
        TLabelData *i = GetFirstEnabled();
        TLabelData *res = PrepareCompareSourseForCycledNavigation(key);
        int b_changed = 0;
        while(i->next)  // Пробегаемся по всему списку ярлычков
        {
          if (CheckCycledNavigation(key, Current, i, res))
          {
            res = i;
            b_changed = 1;
          }
          i = i->next;
        }
        if (CheckCycledNavigation(key, Current, i, res))
        {
          res = i;
          b_changed = 1;
        }
        if (b_changed)
        {
          Current = res;
        }
        else
        {
          if (BCFG_CYCLED == 2)
          {
            Current = GetLastLinkForCycledNavigation(key);
          }
          else
          {
            Current = res;
          }
        }
      }
    }
  }
}
