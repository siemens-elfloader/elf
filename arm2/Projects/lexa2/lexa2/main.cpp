//#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#define size 8

int first=size/2-1;
int last=first+1;

char mass[size];
void addtop(char a);
void addend(char a);
void removetop(void);
void removeend(void);

int main(void)
{
int key=0;
char item=0;
while(1)
{

printf("Select action with array:\n");
printf("'1'- Add item to the top\n");
printf("'2'- Add item to the end\n");
printf("'3'- Remove item from the top\n");
printf("'4'- Remove item from the end\n");
printf("'5'- Print MASS\n");
printf("'6'- Clear screen\n");
printf("'7'- Exit from the program\n");
scanf("%d",&key);
system("cls");
switch(key)
{
case 1:
printf("Print the item\n");
scanf("%s",&item);
system("cls");
addtop(item);
break;

case 2:
printf("Print the item\n");
scanf("%s",&item);
system("cls");
addend(item);
break;

case 3:
removetop();
break;

case 4:
removeend();
break;

case 5:
for(int i=0;i<size;i++)
printf("%c",mass[i]);
printf("\r\n");
break;

case 6:
system("cls");
break;
case 7:return 0;
}


}
}

void addtop(char a)
{
if(first>=0) mass[first--]=a;
else
{
system("cls");
printf("\nFrom the left no place, please choose another operation\r\n");
}
}

void addend(char a)
{
if(last<size)mass[last++]=a;
else
{
system("cls");
printf("\nFrom the right no place, please choose another operation\nr\n");
}
}

void removetop(void)
{
if(first<=size)
{
mass[++first]='\0';
}
else
{
system("cls");
printf("\nMass is empty\r\n");
first=size/2-1;
last=first+1;
}
}

void removeend(void)
{
if(last>=0)mass[--last]='\0';
else
{
system("cls");
printf("\nMass is empty\r\n");
first=size/2-1;
last=first+1;
}
}