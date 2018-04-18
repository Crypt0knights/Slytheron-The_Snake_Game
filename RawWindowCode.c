#include<GL/glut.h>
#include<stdio.h>
  
int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(3000,3000);
glutInitWindowPosition(300,300);
glutCreateWindow("Window for the Snake Game");
glutMainLoop();
}


