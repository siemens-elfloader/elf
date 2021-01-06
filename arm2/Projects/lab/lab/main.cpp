#include <stdio.h>//либы



#define SIZE 6//размер стека

struct point{
	int x,y;
};

struct box{
	struct point data[SIZE];
    int first,last,volume;
};

struct point getPoint()//задаем единичную структуру
{
struct point out;
printf("\tInput x\n\r");
scanf("%d",&out.x);
printf("\n\r");
printf("\tInput y\n\r");
scanf("%d",&out.y);
printf("\n\r");
return out;
}

void push(struct point getPoint,struct box *boxptr)//добавляем в стек структуру
{
	if(boxptr->last!=SIZE-1){
		++boxptr->last;
		boxptr->data[boxptr->last]=getPoint;
        ++boxptr->volume;
	}else{
   printf("\tstack is full\n\r");
	}
}
void pop(struct box *boxptr)//извлекаем последнюю структуру
{
	if(boxptr->last!=-1){
		--boxptr->last;
        --boxptr->volume;
	}else{
printf("\tstack is empty\n\r");
	}
}
void initbox(struct box *boxptr)//зануляем стек
{
		boxptr->last=-1;
		boxptr->first=-1;
        boxptr->volume=0;
}
void printbox(const struct box *boxptr)//выводим на экран
{
	int z=SIZE-boxptr->volume,
		i=boxptr->last;
	printf("\tfree space: %d volume: %d\n\r",z,boxptr->volume);
	for(;i>-1;i--)
	{
		printf("\tx: %d y: %d\n\r",boxptr->data[i].x,boxptr->data[i].y);
	}
}


int main()//основная функция
{
struct box stack;
initbox(&stack);
int cmd;
a:
printbox(&stack);
printf("Commands\n\r1 - push\n\r2 - pop\n\r3 - initbox\n\r0 - exit\n\r");
scanf("%d",&cmd);
printf("\n\r");
switch(cmd)
{
case 0:return 0;
case 1:push(getPoint(),&stack);break;
case 2:pop(&stack);break;
case 3:initbox(&stack);break;
default:printf("\tUnknown cmd\n\r");

}
printf("\n\t");
goto a;
return 0;
}
