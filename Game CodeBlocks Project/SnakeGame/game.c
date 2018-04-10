//drawing stuff
#include<GL/gl.h>
#include<time.h>
#include<GL/glut.h>
#include"game.h"
#include<stdio.h>
#include<stdlib.h>

int gridX,gridY;		//dimension of the grid
int food=1;int foodX,foodY;
short sDirection= RIGHT;// gves initial direction to snake
int posX=20,posY=20;
void unit(int x, int y);
void initGrid(int x,int y)	//initialize grid
{
	//this fucntion only initialize stuff
	gridX=x;
	gridY=y;
}

void drawGrid()
{
    int x,y;
	for(x =0; x<gridX; x++ )
        {
            for(y =0; y<gridY; y++)
            {
                unit(x, y);
            }
        }
}

void unit(int x,int y)
{
	glLineWidth(0.5);
	glColor4f(1.0,1.0,1.0,0.1);
	glBegin(GL_LINE_LOOP);	//loop of lines, first vertex and last vertex specified will be connected
	glVertex2f(x,y);	//2 floating
	glVertex2f(x+1,y);
	glVertex2f(x+1,y+1);
	glVertex2f(x,y+1);
	glEnd();
}
void drawFood()
{
    if(food)
    {
        random1(&foodX,&foodY);
    }
    food=0;
    glColor3f(1,1,0);
    glRectf(foodX,foodY,foodX+1,foodY+1);

}
void drawSnake()
{
    if(sDirection==UP)
        posY++;
    else if(sDirection==DOWN)
        posY--;
    else if(sDirection==RIGHT)
        posX++;
    else if(sDirection==LEFT)
        posX--;
    glColor3f(1.0,1.0,1.0);//coloring the snake
	glRectd(posX,posY,posX+1,posY+1);
	if(posX==foodX && posY==foodY)
        food=1;
    if(posX==0)
        posX=38;
     if(posY==0)
        posY=38;
    if(posX==39)
        posX=0;
    if(posY==39)
        posY=0;


}

void random1(int *x,int *y)
{
    int _maxX= gridX-2;
    int _maxY=gridY-2;
    int _min=1;
    srand(time(NULL));
    *x=_min+rand()%(_maxX+_min);
    *y=_min+rand()%(_maxY+_min);
}
