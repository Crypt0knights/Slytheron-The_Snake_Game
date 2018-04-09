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
	glutInitWindowPosition(500, 0);

	glutCreateWindow("Opening window");

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
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
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

    char string[100000];
    sprintf(string, "S\t\tL\t\tY\t\tT\t\tH\t\tE\t\tR\t\tO\t\tN\t\t-\tT\th\te\t\tS\tn\ta\tk\te\t\tG\ta\tm\te");

    printtext(280,700,string);
     sprintf(string,"Press S to get the Snake Rollin....");
    printtext(360,500,string);
    sprintf(string,"Press ESC to Exit");
     printtext(415,440,string);

	glutSwapBuffers();
}
void processNormalKeys(unsigned char key,int x,int y)
{
if(key ==27)
  exit(0);
	if(key==115)
	  exit(0);
}
