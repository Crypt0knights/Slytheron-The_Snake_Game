#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>  






int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(4000,4000);
glutInitWindowPosition(200,200);
glutCreateWindow("Window for the Snake Game");
glutMainLoop();
}


