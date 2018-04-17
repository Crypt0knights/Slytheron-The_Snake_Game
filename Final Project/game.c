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
bool food = true;
short sDirection= RIGHT;                                                  //gives initial direction to snake by default
//--------------------------FUNCTION PROTOTYPES----------------------------------------
void unit(int x, int y);
void initGrid(int, int);                                                  //initialize grid
void drawGrid();
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
//------------------------RECTANGULAR HURDLES-------------------------------------------
void hurlde()
{
        int i;
        glColor4f(1.0,0.0,0.0,1.0);
        for(i = 10 ;i <30 ; i++)
        {
            glRectd(i,8,1+i,10);
        }
        for(i = 10 ;i <30 ; i++)
        {
            glRectd(i,30,1+i,32);
        }
        glColor4f(1.0,0.0,0.0,1);
        glLineWidth(2.5);
        //top right
        glBegin(GL_LINE_LOOP);
        glVertex2f(30.0,31.0);
        glVertex2f(31.0,31.0);
        glEnd();
        //top left
        glBegin(GL_LINE_LOOP);
        glVertex2f(9.0,31.0);
        glVertex2f(10.0,31.0);
        glEnd();
        //bottom right
        glBegin(GL_LINE_LOOP);
        glVertex2f(30.0,9.0);
        glVertex2f(31.0,9.0);
        glEnd();
        //bottom left
        glBegin(GL_LINE_LOOP);
        glVertex2f(9.0,9.0);
        glVertex2f(10.0,9.0);
        glEnd();
        //upper top first
        glBegin(GL_LINE_LOOP);
        glVertex2f(11.0,32.0);
        glVertex2f(11.0,33.0);
        glEnd();
        //upper top second
        glBegin(GL_LINE_LOOP);
        glVertex2f(29.0,32.0);
        glVertex2f(29.0,33.0);
        glEnd();
        //upper low first
        glBegin(GL_LINE_LOOP);
        glVertex2f(11.0,29.0);
        glVertex2f(11.0,30.0);
        glEnd();
        //upper low second
        glBegin(GL_LINE_LOOP);
        glVertex2f(29.0,29.0);
        glVertex2f(29.0,30.0);
        glEnd();

        //bottom top first
        glBegin(GL_LINE_LOOP);
        glVertex2f(11.0,10.0);
        glVertex2f(11.0,11.0);
        glEnd();
        //bottom top second
        glBegin(GL_LINE_LOOP);
        glVertex2f(29.0,10.0);
        glVertex2f(29.0,11.0);
        glEnd();
        //bottom low first
        glBegin(GL_LINE_LOOP);
        glVertex2f(11.0,7.0);
        glVertex2f(11.0,8.0);
        glEnd();

        //bottom low second
        glBegin(GL_LINE_LOOP);
        glVertex2f(29.0,7.0);
        glVertex2f(29.0,8.0);
        glEnd();
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
//call random1 again if dont want the food to be drawn in rectaangular blocks again 
    for(i = 10; i<30; i++)
    {
        if(foodX == i && (foodY == 8 || foodY == 9))
            {
                random1(&foodX, &foodY);
            }
    }

    for(i = 10; i<30; i++)
    {
        if(foodX == i && (foodY == 30 || foodY == 31))
            {
                random1(&foodX, &foodY);
            }
    }
    /* this code in the comment here disables food being drawn at dead ends, instead a random1() function will be called again to draw
    food at other random position of x and y
        for(i = 9; i<=30; i++)
    {
        if(foodX == i && (foodY == 8 || foodY == 9 || foodY == 7 || foodY == 10))
            {
                random1(&foodX, &foodY);
            }
    }

    for(i = 9; i<=30; i++)
    {
        if(foodX == i && (foodY == 30 || foodY == 31 || foodY == 32 || foodY == 29 ))
            {
                random1(&foodX, &foodY);
            }
    }
    
    
    
    
    
    */


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
           if(posX[0] == 0 && posY[0] == 0)
                gameOver = false;
           else
                gameOver = true;
        }
    }

  //lower
    //left
    if(posX[0] == 9 && (posY[0] == 8 || posY[0] == 9))
        {
        gameOver = true;
        }
    //right
    if(posX[0] == 30 && (posY[0] == 8 || posY[0] == 9))
        {
        gameOver = true;
        }
    //top
    for(i = 10; i<30 ;i++)
    {
        if( posX[0] == i && posY[0] ==10)
        {
        gameOver = true;
        }
    }
    //bottom
    for(i = 10; i<30 ;i++)
    {
        if( posX[0] == i && posY[0] ==7)
        {
        gameOver = true;
        }
    }
    //upper
        //left
     if(posX[0] == 9 && (posY[0] == 30 || posY[0] == 31))
        {
        gameOver = true;
        }
        //right
    if(posX[0] == 30 && (posY[0] == 30 || posY[0] == 31))
        {
        gameOver = true;
        }
        //top
    for(i = 10; i<30 ;i++)
    {
        if( posX[0] == i && posY[0] == 32)
        {
        gameOver = true;
        }
    }
        //bottom
    for(i = 10; i<30 ;i++)
    {
        if( posX[0] == i && posY[0] == 29)
        {
        gameOver = true;
        }
    }
    //Scoring when eats food
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
    srand(time(NULL));                          //seeding a random number, value of time(NULL) keeps chaning every second, srand(time(NULL)) changes the algorithm of rand() function
    *x=_min+rand()%(_maxX+_min);                //here the result is in between (_min + (0,_maxX+_min-1))   // this is how the rand algorithms works.
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

