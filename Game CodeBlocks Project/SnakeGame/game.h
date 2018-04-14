#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
//maximum length of snake
#define MAX 60

void initGrid(int , int);
void drawGrid();
void drawSnake();
void unit();

void hurlde();

void drawFood();
void random1(int *,int *);
void delay(int);

#endif // GAME_H_INCLUDED
