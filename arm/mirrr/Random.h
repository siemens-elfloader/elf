
// ��������� ��������� �����
// �������� ���� �� ���������� mp3 ������ (c) ILYA_ZX

unsigned int randseed;

#define random randint
#define randomize Randomize
unsigned int randint( int max )
{
  randseed = randseed * 0x08088405;
  randseed++;
  return ((long long)randseed * max ) >> 32;
}

unsigned int rand(){
  return randint(0x100000);//?
}

void Randomize(){ // �������� ��� ������ ��� ��������� ������������������
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  //rndindex = (unsigned char)time.param;
  randseed=(time.min | (time.param<<5));
}
