
#include "..\..\inc\swilib.h"
#include "..\..\C++\_cpp2.cpp"
typedef struct
{
  TDate Date;
  TTime Time;
  int size;
  char *msg;
} Buff_Data;

// ����� ��� ������ � ������� �������
class Console_Buffer
{
private:
  Buff_Data *Buff_MSG;  // ������ ���������
  int total;  // ���-�� ��������� � �������
  int head;
  int tail;
public:
  Console_Buffer(int Size); // �����������
  ~Console_Buffer();  //  �������������
  int Put(Buff_Data *Data); // ���������� ��������� � �����
  int Get(Buff_Data **Data); //  ��������� ��������� �� ������
  Buff_Data * GetEx(int Num); // ��������� ��������� �� ������ ��� ������� Num
  int Clean();  //  �������������� ������� ������
};

Console_Buffer::Console_Buffer(int Size) : total (Size)
{
  tail = 0;
  head = 0;
  Buff_MSG = new Buff_Data[Size];
}

Console_Buffer::~Console_Buffer()
{
  delete Buff_MSG;
}

// ���������� ����� ������������ ���������, � �������� ��������� - ���� ���������
int Console_Buffer::Put(Buff_Data *Data)
{
  if (tail==total-1) tail=-1;
  Buff_MSG[tail++] = *Data;
  return tail;  
}

// ���������� ������ ��� ������� Num �� ������
Buff_Data * Console_Buffer::GetEx(int Num)
{
  return &Buff_MSG[Num];
}

// ���������� ����� ����������� ���������, � �������� - ���� ���������
int Console_Buffer::Get(Buff_Data **Data)
{
  if (head==total-1)  head=-1;
  *Data = &Buff_MSG[head++];
  return head;
}

int Console_Buffer::Clean()
{
  delete Buff_MSG;
  Buff_MSG = new Buff_Data[total];
  return 1;
}

////////////////////////////////////////////////////////////////////////////////

int cstate = -1;	// ��������� ������������� �������
Console_Buffer *Con_Buf;	// ������ �������

///////////////////////////////////////////////////////////////////////////////


//   Console Init   //
/*
0 - ������� ���� ���������������� �����
1 - ������� ����������������
*/

__arm int InitConsole_ep(int Size)
{
  if (cstate) return 0;
  Con_Buf = new Console_Buffer(Size);
  return 1;
}

//   Console Destroy   //
/*
0 - ������� �� ���� �������
1 - ������� �������
*/

__arm int KillConsole_ep()
{
  if (cstate)
  {
    delete Con_Buf;
    return 1;
  }
  else
    return 0;
}

//   Console ReInit   //
/*
0 - ������� ���� ���������������� �����
1 - ������� ����������������
*/

__arm int ReInitConsole_ep(int NewSize)
{
  if (cstate) KillConsole_ep();
  return InitConsole_ep(NewSize);
}

//   Console Put   //
/*
���������� ������ � ����� ������ �������
1 - ������ ���������
0 - ������� �� ��������
*/

__arm int ConsolePut_ep(Buff_Data *Data)
{
 if (cstate)
 {
   Con_Buf->Put(Data);
   return 1;
 }
 else
   return 0;
}

//   Console Get   //
/*
��������� "�������" ������ �� ������ �������
1 - ������ ���������
0 - ������� �� ��������
*/

__arm int ConsoleGet_ep(Buff_Data *Data)
{
 if (cstate)
 {
   Con_Buf->Get(&Data);
   return 1;
 }
 else
   return 0;
}

//   Console Get by Num   //
/*
��������� ������ �� ������ �������, ������������� ��� ������� Num, ��� ����, ������� �� ����������
0 - ������� �� ��������, ����� - ������
*/

__arm Buff_Data * ConsoleGetEx_ep(int Num)
{
 if (cstate)
 {
   return Con_Buf->GetEx(Num);
 }
 else
   return 0;
}

//   Console Clean   //
/*
������� ������ �������
1 - ����� ������
0 - ������� �� ��������
*/

__arm int ConsoleClean_ep()
{
 if (cstate)
 {
   return Con_Buf->Clean();
 }
 else
   return 0;
}


#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC311 @ "SWILIB_FUNC311_317" = (int)InitConsole_ep;
__root static const int SWILIB_FUNC312 @ "SWILIB_FUNC311_317" = (int)KillConsole_ep;
__root static const int SWILIB_FUNC313 @ "SWILIB_FUNC311_317" = (int)ReInitConsole_ep;
__root static const int SWILIB_FUNC314 @ "SWILIB_FUNC311_317" = (int)ConsolePut_ep;
__root static const int SWILIB_FUNC315 @ "SWILIB_FUNC311_317" = (int)ConsoleGet_ep;
__root static const int SWILIB_FUNC316 @ "SWILIB_FUNC311_317" = (int)ConsoleGetEx_ep;
__root static const int SWILIB_FUNC317 @ "SWILIB_FUNC311_317" = (int)ConsoleClean_ep;
#pragma diag_default=Pe177
