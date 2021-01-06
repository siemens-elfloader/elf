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
  //  ���������� ����� � ����������� ����������� �� ��� x
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // ����������� �� ����� ������ ��������
    {
      if(i->x <= result->x)    // ���� ����� ������� ����� ��� ������������
      {
        if (i->x == result->x)
        {
          // ���������� �� ������
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
    if(i->x <= result->x)    // ���� ����� ������� ����� ��� ������������
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
  // ���������� ����� � ������������ ����������� x
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // ����������� �� ����� ������ ��������
    {
      if(i->x >= result->x)    // ���� ����� ������� ������ ��� ������������
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
    if(i->x >= result->x)    // ���� ����� ������� ������ ��� ������������
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
  //  ���������� ����� � ����������� ����������� �� ��� y
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // ����������� �� ����� ������ ��������
    {
      if(i->y <= result->y)    // ���� ����� ������� ���� ��� ������������
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
    if(i->y <= result->y)    // ���� ����� ������� ���� ��� ������������
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
  //  ���������� ����� � ������������ ����������� �� ��� y
  //
  if (TLabels)
  {
    TLabelData *result = GetFirstEnabled();
    TLabelData *i = GetFirstEnabled();
    while (i->next)  // ����������� �� ����� ������ ��������
    {
      if(i->y >= result->y)    // ���� ����� ������� ���� ��� ������������
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
    if(i->y >= result->y)    // ���� ����� ������� ���� ��� ������������
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
        // ����������� ��������� ��������� - ���� ������ �� ������ ^_^
      }
      break;
    case 1:
      {
        // ��������� � ������� ������� �� ������� �����/�������
        if (key == RIGHT_BUTTON)
        {
          // ���� ������ ������ �� � ���� ����� ����� � ����� ����� �� �������,
          // ��� � ��������
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
          // ���� ������ ����� �� � ���� ����� ������ � ����� ����� �� �������,
          // ��� � ��������
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
          // ���� ������ ���� �� � ���� ����� �������, � ����� ����� �� 
          // ����������� �� �, ��� � ��������
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
          // ���� ������ ���� �� � ���� ����� ������, � ����� ����� �� 
          // ����������� �� �, ��� � ��������
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
        // ��������� � ������� ������� �� ��������� ����� �������
        if (key == RIGHT_BUTTON)
        {
          // ���� ������ ������ �� � ���� ����� ����� � ���������� ��������
          //  � ������, ������ � ��������
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
          // ���� ������ ����� �� � ���� ����� ������ � ����� ����� �� �������,
          // ��� � ��������
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
          // ���� ������ ���� �� � ���� ����� �������, � ����� ����� �� 
          // ����������� �� �, ��� � ��������
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
          // ���� ������ ���� �� � ���� ����� ������, � ����� ����� �� 
          // ����������� �� �, ��� � ��������
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
    while(i->next)  // ����������� �� ����� ������ ��������
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
        // ������ ����� ��������� ����������� ���������
        TLabelData *i = GetFirstEnabled();
        TLabelData *res = PrepareCompareSourseForCycledNavigation(key);
        int b_changed = 0;
        while(i->next)  // ����������� �� ����� ������ ��������
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
