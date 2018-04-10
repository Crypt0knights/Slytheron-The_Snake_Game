
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<string.h>

void display(void);
void printtext(int x, int y,char String[]);
void processNormalKeys(unsigned char key,int x,int y);
int WindowHeight = 1000;
int WindowWidth = 1000;

int main(int argc, char *argv[])//argc-stores the count to aruguments
{
	glutInit(&argc, argv);//argv-stores the arguments variables
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//Bit mask to select buffer window
	glutInitWindowSize(WindowWidth, WindowHeight);//WindowSize
	glutInitWindowPosition(500, 0);//WindowPosition
	glutCreateWindow("Opening window");//Initialising window
	glutDisplayFunc(display);//display_rendering
  glutKeyboardFunc(processNormalKeys);//keyboard control
	glMatrixMode(GL_PROJECTION);//Applies subsequent matrix operations to the projection matrix stack
	glLoadIdentity();//replaces the current matrix with the identity matrix
	gluPerspective(70, 1, 1, 100);//specifying viewing
	glMatrixMode(GL_MODELVIEW);//Applies subsequent matrix operations to the modelview matrix stack.
	glLoadIdentity();
	gluLookAt(2, 2, 10, 2, 0, 0, 0, 1, 0);/*creates a viewing matrix derived from an eye point, a reference
            point indicating the center of the scene, and an UP vector*/
	glutMainLoop();//event processing infinite loop
	return 0;
}


void printtext(int x, int y, char String[])
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();//push and pop the current matrix stack
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);//multiply the current matrix with an orthographic matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);//push and pop the server attribute stack
    glDisable(GL_DEPTH_TEST);//disable server-side GL capabilities
    glRasterPos2i(x,y);
    for (int i=0; i<strlen(String); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);//used to write text//font
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
    printtext(360,500,stri);
    sprintf(stri,"Press ESC to Exit");
    printtext(415,440,stri);
    glutSwapBuffers();
}
void processNormalKeys(unsigned char key,int x,int y)
{
if(key ==27)
  exit(0);
if(key==32)
  exit(0);
}
