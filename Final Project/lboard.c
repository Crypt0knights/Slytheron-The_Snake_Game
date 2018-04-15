#include<GL/gl.h>
#include<time.h>
#include<GL/glut.h>
#include"game.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
/*----------------LINKED LIST STRUCTURE AND NODE POINTERS-------------------------*/
struct Node{
int score2;
char playername[10];
struct Node *next;
};
typedef struct Node node;
node *first;
//-----------------FUNCTION PROTOTYPES-------------------------------------//
void fileread();
void display();
void insertlist(int ,char []);
void sortlist();
void writetofile();
int listsize;
listsize=0;
//-----------------GLOBAL VARIABLES--------------------------------------//
extern int score;               //taking values of score
//-------------------FUNCTION DEFINITIONS START-----------------------//
void fileread()
{
    int value,size;value=0;char playerid[10];
    FILE *fp;
    fp=fopen("lb1.txt","r");
    if (NULL != fp)
    {
        fseek (fp, 0, SEEK_END);
        size = ftell(fp);
        if (0 == size)
        {
            printf("file is empty\n");
            fclose(fp);
            return;
        }
        else
        {
            rewind(fp);
            //printf("1");
            while((fscanf(fp,"%s %d ",playerid,&value))!=EOF)
            {
                //printf("%d ",value);
                insertlist(value,playerid);
                listsize++;
            }
        }
    fclose(fp);
}
}
void insertlist(int val,char playerid[10])
{
    node *new_node;
	new_node=(node*)malloc(sizeof(node));
	//printf(" %d",val);
	new_node->score2=val;
	strcpy(new_node->playername,playerid);
	if(first==NULL)
	{
		first=new_node;
		new_node->next=NULL;
	}
	else{
	node *temp1=first;
	while(temp1->next!=NULL)
	{
		temp1=temp1->next;
	}
	temp1->next=new_node;
	new_node->next=NULL;
    }
}
void sortlist()
{
node *temp1;
node *temp2;
int t,i,j,n;n=listsize+1;char t1[10];
for(i=0;i<n-1;i++)
    {
        temp1=first;
        temp2=temp1;
        temp1=temp1->next;
        for(j=0;j<n-i;j++)
        {
            if(temp2->score2 <= temp1->score2)
            {
                t=temp1->score2;             strcpy(t1,temp1->playername);
                temp1->score2=temp2->score2; strcpy(temp1->playername,temp2->playername);
                temp2->score2=t;             strcpy(temp2->playername,t1);
            }
            if(temp1->next!=NULL)
            {
            temp1=temp1->next;
            temp2=temp2->next;
            }
        }
    }
}

void writetofile()
{
    FILE *fp;
    fp=fopen("lb1.txt","w");
    node *temp;temp=first;
    while(temp->next!=NULL)
    {
        fprintf(fp,"%s %d ",temp->playername,temp->score2);
        temp=temp->next;
    }
    fprintf(fp,"%s %d ",temp->playername,temp->score2);
    fclose(fp);
}
void boardprint()
{
        //to update the linked list every time the game starts using the file.
        fileread();
        char playerid[10]="MARK";
        char pos[20];
        itoa((listsize+1),pos,10);
        strcat(playerid,pos);
        insertlist(score,playerid);
        sortlist();
        writetofile();
        char winners[1000];
        strcpy(winners,"Player ID");
        strcat(winners,"\t\t");
        strcat(winners,"SCORE\n\n");
        node *temp1;
        temp1=first;
        while(temp1->next!=NULL)
        {
            strcat(winners,temp1->playername);
            strcat(winners,"\t\t");
            char score3[100];
            itoa(temp1->score2,score3,10);
            strcat(winners,score3);
            strcat(winners,"\n");
            temp1=temp1->next;
        }
            strcat(winners,temp1->playername);
            strcat(winners,"\t\t");
            char score3[100];
            itoa(temp1->score2,score3,10);
            strcat(winners,score3);
            strcat(winners,"\n");
        char score1[10];//message box string of score.
        itoa(score,score1,10);
        char text[50]={"\t\tOops..!!GAME OVER\t\t\n\n\t\tYOUR SCORE IS- "};
        strcat(text,score1);
        MessageBox(NULL,text,"GAME OVER",1);
        MessageBox(NULL,winners,"The Leaderboard",1);
        exit(0);
}
//-------------------------END------------------------------------------------
