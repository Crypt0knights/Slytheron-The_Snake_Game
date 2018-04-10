#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include "game.h"

#define COLUMNS 40
#define ROWS 40
#define FPS 10 //10 boxes in one second

extern short sDirection;
//bool gameOver=false;
void timer_callback();
void display_callback();
void reshape_callback(int,int);
void keyboard_callback(int);
void init()
{

	glEnable(GL_BLEND);         //added this for maintaing alpha value
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0,0.5,0.0,1.0);	//clear color of the window to red
	initGrid(COLUMNS,ROWS);

}
int main(int argc, char **argv)
{
	glutInit(&argc,argv);	//initialize
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE /*Doule Buffer Display Window*/ | GLUT_DEPTH);
	glutInitWindowPosition(500,0);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Slytheron-the Snake Game");
	glutDisplayFunc(display_callback);//register display_callback
	glutReshapeFunc(reshape_callback);//register reshape callback
	glutTimerFunc(0,timer_callback,0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
	return 0;
}
int index=0;//keep track of position
void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);//Clearing Color Buffer to get red window
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();//Buffer is first loaded, another displays
	/*if(gameOver)
	{
        MessageBox(0,"Your Score:","GAME OVER",0);
        exit(0);
	}*/

}
void reshape_callback(int w, int h)	//after it is resized w/h
{	//viewport - rectangular area.
	//sets the viewport
	//typecasting with GLsizei
	glViewport(0,0,(GLsizei)w,(GLsizei)h);//makes working size after resizing
	glMatrixMode(GL_PROJECTION/*GL Projection Matrix*/); //setting the co ordinate system
	glLoadIdentity();//make sure no changes made to matrix
	//glOrtho(leftx, rightx, bottom y, top y, zNear, zFar(going inside the screen))	we are working in 0 in zMode
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);//sets orthographic projection
	//Screen with 0,0 in left bottom
	glMatrixMode(GL_MODELVIEW);
}

void timer_callback()
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}
void keyboard_callback(int key)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if(sDirection!=DOWN)
                sDirection=UP;
            break;
        case GLUT_KEY_DOWN:
            if(sDirection!=UP)
                sDirection=DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection!=LEFT)
                sDirection=RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection!=RIGHT)
                sDirection=LEFT;
            break;
    }
}
