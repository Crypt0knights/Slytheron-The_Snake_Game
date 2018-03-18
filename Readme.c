#include<GL/glut.h>
#include<stdio.h>
  






int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(1000,1000);
glutInitWindowPosition(100,100);
glutCreateWindow("Window for the Snake Game");
glutMainLoop();
}


