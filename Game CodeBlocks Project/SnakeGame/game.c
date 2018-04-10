//drawing stuff
#include<GL/gl.h>
#include<time.h>
#include<GL/glut.h>
#include"game.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

extern int score;
extern bool gameOver;

int gridX,gridY;        //dimension of the grid
int foodX,foodY;
bool food = true;
short sDirection= RIGHT;// gves initial direction to snake by default
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
int snake_length = 5;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
    // Stroing start time
    clock_t start_time = clock();
    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

void unit(int x, int y);
void initGrid(int x,int y)    //initialize grid
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
    glBegin(GL_LINE_LOOP);    //loop of lines, first vertex and last vertex specified will be connected
        glVertex2f(x,y);    //2 floating
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
    food=false;
    glColor3f(1,1,0);
    glRectf(foodX,foodY,foodX+1,foodY+1);

}
void drawSnake()
{
    int i;
    for(i = snake_length-1;i>0;i--)
    {
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }
    if(sDirection==UP)
    {
        posY[0]++;
        if(posY[0] == 40)
            {
                posY[0] = 0;
            }
    }
    else if(sDirection==DOWN)
        {
        posY[0]--;
        if(posY[0] == (-1))
            {
                posY[0] = 40;
            }
        }
    else if(sDirection==RIGHT)
        {
        posX[0]++;
        if(posX[0] == 40)
            {
                posX[0] = 0;
            }
        }
    else if(sDirection==LEFT)
        {
        posX[0]--;
        if(posX[0] == (-1))
            {
                posX[0] = 40;
            }
        }
    for(i = 0; i < snake_length ; i++)
    {
        if( i == 0)
            {
                glColor4f(0.0,0.0,0.0,1.0);
            }
        else
            {
                glColor3f(1.0,0.0,0.0);
            }
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);

    }
    //make the game over condition  when snake's head collide to its body die!
  for(i = 0 ; i < snake_length + 5 ; i++)
    {
        if(posX[0] == posX[i+4] && posY[0] == posY[i+4] )
           {
                gameOver = true;
                exit(0);
           }
    }


    if(posX[0]==foodX && posY[0]==foodY)
        {
            score++;
            food=true;
            snake_length++;
            if(snake_length > MAX)
                snake_length = MAX;
        }

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
