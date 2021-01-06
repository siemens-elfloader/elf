#include <swilib.h>
//������ ����,�� ���-�� ����� ������� ���������� ������� :)
//������ ������� ��������,�� ��������� �������� �� ��������..������� ����-�� ����������


//������ ������ ��� ������ ����� ���� ��������� �������,����� ����� InitSprite ��� ������������� �������
//� DrawSprites ��� ����������
//��� ������ �� ����� ������ ����������� �������

typedef struct
{
  IMGHDR **img;
  char active;
  short x,y;
  char num; //���-�� �������� � ��������
  short time; //����� ����� �������,��� ������������.�������� �� ��������� � 2
  char sw; //������������ ������,����� ��������� ������,������ �����������
  int counter; //������� ��� ��� ���-�� ������������,����� ���� ������ �����������
  short N; //����� ������� � ������
  short ovr; // ���-�� ������������ �������� �������
  
  short ex,ey; //�������� ���������� �������� �������
  signed char x_incr,y_incr; //���������� �� ����� � �������
  char isMoving; //���� �� ���������� ��������?
  short uid; //id,�������� ������.�������� ����� ���������������� ������ �������� � ����� uid,� ����� �������� ��� ���� �������� ������ �� ����������.�� �� ����� u��� ���������� ������� ����� GetSprite � � ������ ����. ����������� :)
  short udv; //User Defined Variable
}TSPRITE; //������� �� ��� ��������� ������� ��������� ��� SpriteLoader'a,� ��� ����� ��������  ������� ��������


#define MAX_SPRITES 128
extern TSPRITE *sprites;



//�� �������� ��� MAX_SPRITES!
void DrawSprites(); //����������
void LoadSprite(char *name,char num,short time,TSPRITE *sprite); //�������� �� �����
void FreeSprite(TSPRITE *sprite); //������� ������������ �� ����� �������
short InitSprite(TSPRITE *sprite,short uid,short x,short y,short repeat_num); //������������� ����� �����������
short InitMSprite(TSPRITE *sprite,short uid,short x,short y,signed char x_incr,signed char y_incr,short ex,short ey); //���������� ������,�� �������� �������� ������ ����-���� :)

void SetSpriteCoordinaties(short N,short x,short y); //������ ���������� ������� � ��������� ������� � ������(����� ���������� InitSprite)
void GetSpriteCoordinaties(short N,short *x,short *y); //�������� ���������� ������� � ��������� �������
short GetSpriteWidth(short N);
short GetSpriteHeight(short N);
void StopSprite(short N); //������ ���������� ������
void DumpActiveSprites();

TSPRITE *GetSprite(short num);

void InitSpriteBuffer();
void DeinitSpriteBuffer();

//������ ������
/*
TSPRITE my_sprite1;
TSPRITE my_sprite2;

void StartProgram() //OnCreate
{
  InitSpriteBuffer();
  LoadSprite("images\\anim1.png",4,&my_sprite1);
  LoadSprite("images\\anim2.png",6,&my_sprite2);
}

void RedrawScreen() //��������� � ������������ �� �������
{
  DrawSprites();
}

void FreeMemory() //OnClose
{
  DeinitSpriteBuffer();
  FreeSprite(&my_sprite1);
  FreeSprite(&my_sprite2);
}

void Activate1()
{
  //� �������� ����� � � ����� ���������������� ������ ��������,����� ��� ��������� �����
  InitSprite(&my_sprite1,100,100);
  InitSprite(&my_sprite2,200,200);
}*/


