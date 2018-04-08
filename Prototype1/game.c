#include<GL/gl.h>
#include<GL/glut.h>
#include "game.h"
int gridX,gridY;
void initGrid(int x,int y)
{
	gridX=x;
	gridY=y;
}

void drawGrid()
{
	unit(20,20);
}

void unit(int x,int y)
{
	glLineWidth(1.0);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x,y);
	glVertex2f(x+1,y);
	glVertex2f(x+1,y+1);
	glVertex2f(x,y+1);
	glEnd();
}
