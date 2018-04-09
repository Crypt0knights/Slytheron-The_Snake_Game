#include<string.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
using namespace std; 
void display(void);
void polygon(int a, int b, int c , int d);
void DrawCube();
void printtext(int x, int y, string String);
void processNormalKeys(unsigned char key,int x,int y);
int WindowHeight = 1000;
int WindowWidth = 1000;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(0, 0);
 
	glutCreateWindow("OpenGL Text Example");
 
	glutDisplayFunc(display);
        glutKeyboardFunc(processNormalKeys);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 1, 100);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
	gluLookAt(2, 2, 10, 2, 0, 0, 0, 1, 0);
 
	glutMainLoop();
	return 0;
}
 
 
void printtext(int x, int y, string String)
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
 
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glEnable(GL_DEPTH_TEST);
 
    char string[100000];
    sprintf(string, "SLYTHERON");
    
    printtext(450,700,string);
     sprintf(string,"press any key");
    printtext(450,450,string);
 
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key,int x,int y)
{
if(key ==27)
  exit(0);
}
