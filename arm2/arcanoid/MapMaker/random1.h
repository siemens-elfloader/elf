
// Генератор случайных чисел
// Алгоритм взят из исходников mp3 плеера (c) ILYA_ZX

int randseed;

#define random randint
#define randomize Randomize
int randint( int max )
{
  randseed = randseed * 0x08088405;
  randseed++;
  return (((long long)randseed * max ) >> 32)%max;
}

unsigned int rand(){
  return randint(0x100000);//?
}

void Randomize(){ // Вызываем при старте для случайной последовательности
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  //rndindex = (unsigned char)time.param;
  randseed=(time.min | (time.sec<<5));
}
