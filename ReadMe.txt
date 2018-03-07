#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
int length;
int Score();
void Left();
void Right();
void Up();
void Down();
void Border();
void GameOver();
struct coordinates
{
int x;
int y;
int direction;
}coordinate;                  

int main()
{
int ch;
int gd=DETECT,gm;
clrscr();
setcolor(RED);
settextstyle(3,0,5);
printf("Welcome To The Game\n");
x:
setcolor(BLUE);
settextstyle(0,0,3);
printf("Don't dare to touch the border\n");
printf("Press 's' to start\n");
printf("Press 'p' to pause\n");
printf("Have Fun Dude");
scanf("%c",&ch);
if(ch=='s')
   {
    initgraph(&gd,&gm,"Address of BGI");
   }
else
   {
     goto x;
   }
}

return 0;
}
