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

void fileread()					//function to read the previous stored data of scores from the file
{
    int value,size;value=0;char playerid[10];
    FILE *fp;
    fp=fopen("lb1.txt","r");
    if (NULL != fp)				//checks if file is empty
    {
        fseek (fp, 0, SEEK_END);
        size = ftell(fp);
        if (0 == size)
        {
            //printf("file is empty\n");
            fclose(fp);				//closes file if it is empty and jumps out of function.
            return;
        }
        else
        {
            rewind(fp);				//brings pointer to starting of file
            while((fscanf(fp,"%s %d ",playerid,&value))!=EOF)
	    {
                insertlist(value,playerid);	//calls insertlist to insert the extracted data into the linked list.
                listsize++;			//calculates the size of the created linked list.
            }
        }
    fclose(fp);
}
}
void insertlist(int val,char playerid[10])	//function to insert the extracted data from file into the linked list.
{
    node *new_node;
	new_node=(node*)malloc(sizeof(node));	//allocating memory for saving the extracted data to the Linked list
	new_node->score2=val;			//copying score
	strcpy(new_node->playername,playerid);	//copying playername
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
void sortlist()				//Implementation of Bubble sort algorithm to sort the linked list in descending order according to score
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
            if(temp2->score2 <= temp1->score2)		//descending order condition
            {
                t=temp1->score2;             strcpy(t1,temp1->playername);		//substituting the score and names simultaneously
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

void writetofile()				//function to write the updated linked list(with the new score) to file.
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
void boardprint()			//the master function calling other functions and displaying the message boxes.
{
         fileread();			//fill up the linked list with the previous data if any.
        char playerid[10]="MARK";	//creating the player ids according to the sequence of game play
        char pos[20];			//                          " "
        itoa((listsize+1),pos,10);	//			    " "
        strcat(playerid,pos);		//			    " "
        insertlist(score,playerid);	//inserting the new score into the linked list containing the previous gameplay data.
        sortlist();			//sorting the updated linked list.
        writetofile();			//writing the all new linked to the file.
	
	//DISPLAYING MESSAGE BOXES FROM HERE
	/*Since message box accepts only String arguments,we will be typecasting every integer(score) stored in the linked 
	list and then will be appending all of the linked list data into the message box string array which is 'winners'*/
	
	char winners[1000];
        strcpy(winners,"Player ID\t\t");		//copying headings of the leaderboard
        strcat(winners,"SCORE\n\n");			//	      " "
        node *temp1;	
        temp1=first;
        while(temp1->next!=NULL)			//traversing the linked list and appending data of each node to the string winners.
        {
            strcat(winners,temp1->playername);		//appending the playernames
            strcat(winners,"\t\t");
            char score3[100];
            itoa(temp1->score2,score3,10);		//typecasting the score(int) to String and storing it in score3 char array.
            strcat(winners,score3);			//appending score.
            strcat(winners,"\n");
            temp1=temp1->next;
        }
            strcat(winners,temp1->playername);
            strcat(winners,"\t\t");
            char score3[100];
            itoa(temp1->score2,score3,10);
            strcat(winners,score3);			//copying details of last node which could not get executed in above loop.
            strcat(winners,"\n");
        char score1[10];				//char array to store data of individual score message box.
        itoa(score,score1,10);
        char text[50]={"\t\tOops..!!GAME OVER\t\t\n\n\t\tYOUR SCORE IS- "};
        strcat(text,score1);
        MessageBox(NULL,text,"GAME OVER",1);		//printing the individual score message box.
        MessageBox(NULL,winners,"The Leaderboard",1);	//printing the leaderboard message box.
        exit(0);
}
//-------------------------END------------------------------------------------
