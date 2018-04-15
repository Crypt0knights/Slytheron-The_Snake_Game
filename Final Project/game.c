//drawing stuff
//--------------------HEADER FILES----------------------------------//
#include<GL/gl.h>
#include<time.h>
#include<GL/glut.h>
#include"game.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//------------------------GLOABAL VARIABLES-------------------------------------------
extern int score;
extern bool gameOver;
int gridX, gridY, foodX, foodY, snake_length = 5;
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
int hurdleX[10] = {5,5,5,5,5,5,5,5,5,5}, hurdleY[10] = {16,17,18,19,20,21,22,23,24,25};
bool food = true;
short sDirection= RIGHT;                                                    // gves initial direction to snake by default
//--------------------------FUNCTION PROTOTYPES----------------------------------------
void unit(int x, int y);
void initGrid(int, int);                                                  //initialize grid
void drawGrid();
void unit(int x,int y);
void drawFood();
void drawSnake();
//------------------------FUNCTION DEFINITIONS-------------------------------------------
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

void hurlde()
{
        int i;
        glColor4f(1.0,0.0,0.0,0.5);

        for(i = 10 ;i <30 ; i++)
        {
            glRectd(i,8,1+i,10);
        }

        for(i = 10 ;i <30 ; i++)
        {
            glRectd(i,30,1+i,32);
        }
}

void drawFood()
{
    int i;
    if(food)
        {
        random1(&foodX,&foodY);
        }
    food=false;
    glColor3f(1,1,0);

    for(i = 10; i<30; i++)
    {
        if((foodX == i && foodY == 8) || (foodX == (i+1) && foodY == 9))
            {
                random1(&foodX, &foodY);
            }
    }

    for(i = 10; i<30; i++)
    {
        if((foodX == i && foodY == 30) || (foodX == (i+1) && foodY == 31))
            {
                random1(&foodX, &foodY);
            }
    }
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
    for(i = 0; i < snake_length; i++)
    {
        if( i == 0)
           glColor4f(0.0,0.0,0.0,1.0);
        else
           glColor3f(1.0,0.0,0.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }
    for(i = 0 ; i < snake_length + 5 ; i++)                             //collision condition
    {
        if(posX[0] == posX[i+4] && posY[0] == posY[i+4] )
        {
           gameOver = true;
        }
    }
    for(i = 10; i<30; i++)
    {
        if(posX[0] == i && posY[0] == 8 || posX[0] == (i+1) && posY[0] == 9)
        {
        gameOver = true;
        }

        if(posX[0] == i && posY[0] == 30 || posX[0] == (i+1) && posY[0] == 31)
        {
        gameOver = true;
        }
        if(posX[0] == 30 && (posY[0] == 31 || posY[0] == 9) )
        {
        gameOver = false;
        }
    }

    if(posX[0] == 10 && posY[0] == 8 || posX[0] == 10 && posY[0] == 9 || posX[0] == 29 && posY[0] == 8 || posX[0] == 29 && posY[0] == 9 || posX[0] == 10 && posY[0] == 30 || posX[0] == 10 && posY[0] == 31  || posX[0] == 29 && posY[0] == 30 || posX[0] == 29 && posY[0] == 31)
        {
        gameOver = true;
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
    srand(time(NULL));  //seeding a random number, value of time(NULL) keeps chaning every second, srand(time(NULL)) changes the algorithm of rand() function
    *x=_min+rand()%(_maxX+_min);    //here the result is in between (_min + (0,_maxX+_min-1))   // this is how the rand algorithms works.
    *y=_min+rand()%(_maxY+_min);
}

void initGrid(int x,int y)                                                  //initialize grid
{
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
//-------------------------END-------------------------------------------------------------------------
