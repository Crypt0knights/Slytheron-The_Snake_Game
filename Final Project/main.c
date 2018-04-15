//compile using  gcc file.c -o file -lGL -lGLU -lglut
//Snake Game 1.0
//--------------------HEADER FILES------------------------------------------------------
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include "game.h"
#include<stdbool.h>
#include<string.h>
#define COLUMNS 40
#define ROWS 40
//-------------------------GLOBAL VARIABLES---------------------------------------------------------------------
extern short sDirection;
bool gameOver = false;
int score=0;
int FPS = 10;
int WindowHeight = 1000;
int WindowWidth = 1000;
//--------------------------------FUNCTTION PROTOTYPES----------------------------------------------------------------
void timer_callback();
void display_callback();
void reshape_callback(int,int);
void keyboard_callback(int,int,int);                                                /* (key pressed, mouse X, mouse Y) */
void display(void);
void printtext(int x, int y,char String[]);
void processNormalKeys(unsigned char key,int x,int y);
//-------------------------------------FUNCTION DEFINITIONS---------------------------------------------------------------------
void initMain()
{
	glEnable(GL_BLEND);                                                             //added this for maintaing alpha value
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0,0.5,0.0,1.0);	                                                //clear color of the window to black
	initGrid(COLUMNS,ROWS);
}

void initGameWindow()
{
	glEnable(GL_BLEND);                                                             //added this for maintaing alpha value
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0,0.5,0.0,1.0);	                                                //clear color of the window to orange
	initGrid(COLUMNS,ROWS);
}

int main(int argc, char *argv[])                                                    //argc-stores the count to aruguments in case of argument variable
{
    glutInit(&argc, argv);                                                          //argv-stores the arguments variables
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);                       //Bit mask to select buffer window
	glutInitWindowSize(WindowWidth, WindowHeight);                                  //WindowSize
	glutInitWindowPosition(500, 0);                                                 //WindowPosition
	glutCreateWindow("Welcome to SLYTHERON");                                       //Initialising window
	glutDisplayFunc(display);                                                       //display_rendering
  	glutKeyboardFunc(processNormalKeys);                                            //keyboard control
	glMatrixMode(GL_PROJECTION);                                                    //Applies subsequent matrix operations to the projection matrix stack
	glLoadIdentity();                                                               //replaces the current matrix with the identity matrix
	gluPerspective(70, 1, 1, 100);                                                  //specifying viewing
	glMatrixMode(GL_MODELVIEW);                                                     //Applies subsequent matrix operations to the modelview matrix stack.
	glLoadIdentity();
	gluLookAt(2, 2, 10, 2, 0, 0, 0, 1, 0);                                          //creates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector*/
	initMain();
	glutMainLoop();                                                                 //event processing infinite loop
	return 0;
}

int GameWindow()
{
	glutCreateWindow("Slytheron-the Snake Game");
	glutDisplayFunc(display_callback);                                              //register display_callback
	glutReshapeFunc(reshape_callback);                                              //register reshape callback
	glutTimerFunc(0, timer_callback, 0);                                            //registered here once then in timer_callback
	glutSpecialFunc(keyboard_callback);
	initGameWindow();
	glutMainLoop();
	return 0;
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);                                                   //Clearing Color Buffer to get window
	drawGrid();
	glColor3d(1,1,1);
	drawSnake();
	hurlde();
	glColor4d(1,0,0,1);
	drawFood();
	glutSwapBuffers();                                                              //Buffer is first loaded, another displays //some delay is added by glutSwapBuffers() too
                                                                                    //*****************************CHECK***************************************************
	if(gameOver == true)
    {
        boardprint();
        exit(0);
    }
}

void reshape_callback(int w, int h)	                                                //after it is resized w/h   //viewport - rectangular area. //sets the viewport //typecasting with GLsizei
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);                                          //makes working size after resizing
	glMatrixMode(GL_PROJECTION);                                                    //GL Projection Matrix*/); //setting the co ordinate system
	glLoadIdentity();                                                               //make sure no changes made to matrix
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);                                         //sets orthographic projection //glOrtho(leftx, rightx, bottom y, top y, zNear, zFar(going inside the screen))	we are working in 0 in zMode
	glMatrixMode(GL_MODELVIEW);                                                     //Screen with 0,0 in left bottom
}

void timer_callback()
{
    glutPostRedisplay();
    if(score == 5)
        FPS = 10;                                                    //display function is to be called next, new frame is displayed each time timer_callback is called
    if(score == 10)
        FPS = 15;
    if(score == 15)
        FPS = 20;
    if(score == 20)
        FPS = 25;
    if(score == 25)
        FPS = 60;

    glutTimerFunc(1000/FPS, timer_callback, 0);                                     //here it is a continous loop of frames being dispalyed we want 10frames in one sec
}

void keyboard_callback(int key,int x,int y)
{
    switch(key)
    {

        case GLUT_KEY_UP:
            if(sDirection != DOWN)
                {
                    sDirection = UP;
                }
            break;
        case GLUT_KEY_DOWN:
            if(sDirection != UP)
                {
                    sDirection = DOWN;
                }
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection != LEFT)
                {
                    sDirection = RIGHT;
                }
            break;
        case GLUT_KEY_LEFT:
            if(sDirection != RIGHT)
                {
                    sDirection = LEFT;
                }
            break;

    }
}

void printtext(int x, int y, char String[])
{
                                                                                    //(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();                                                                 //push and pop the current matrix stack
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);                          //multiply the current matrix with an orthographic matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);                                                    //push and pop the server attribute stack
    glDisable(GL_DEPTH_TEST);                                                       //disable server-side GL capabilities
    glRasterPos2i(x,y);
    int i;
    for (i=0; i<strlen(String); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);                //used to write text//font
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glClearColor(1.0,0.5,0.0,1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    char stri[100000];
    sprintf(stri, "S\t\tL\t\tY\t\tT\t\tH\t\tE\t\tR\t\tO\t\tN\t\t-\tT\th\te\t\tS\tn\ta\tk\te\t\tG\ta\tm\te");
    printtext(280,700,stri);
    sprintf(stri,"Press SPACE to get the Snake Rollin....");
    glColor3f(0,0,1);
    printtext(360,500,stri);
    sprintf(stri,"Use Arrow Keys To Control the SNAKE!!!! ");
    glColor3f(0,0,1);
    printtext(330,450,stri);
    glColor3f(0,0,1);
    sprintf(stri,"If Bored,press ESC to Exit");
    printtext(415,400,stri);
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key,int x,int y)
{
    if(key ==27)                                                            //escape key
        exit(0);
    if(key==32)                                                             //Space Bar
        GameWindow();
}
//--------------------------------END--------------------------------------------------------------
