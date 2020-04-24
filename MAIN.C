// Project of BIT first semester
//Starting date:20 April,2020
//Completion date:-----------
//A project by Rohan Dhimal

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

int maxx,maxy,setgraph=0;

void setgraphics();
void closegraphics();
void startgame();
void loadingscreen();
void mainmenu();


int main(){

	if (setgraph==0)
	 setgraphics();
	maxx=getmaxx();
	maxy=getmaxy();
	setbkcolor(WHITE);
	setcolor(BLUE);
	loadingscreen();
	mainmenu();
	closegraphics();
	return 0;

}

void setgraphics() {
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C://turboc3//bgi");
	setgraph=1;
}

void closegraphics(){
	closegraph();
	setgraph=0;
}

void loadingscreen(){
	int i=0;
	cleardevice();
	while (i!=200){
		rectangle(maxx/2-100,maxy-100,maxx/2-100+i,maxy-75);
		rectangle(maxx/2-100,maxy-100,maxx/2+100,maxy-75);
		i++;
		delay(10);
	}
	outtextxy(maxx/2-100,100,"Press any key to continue:");
	getch();
}

void mainmenu(){
	char enteredChar;
	menu:
	cleardevice();
	outtextxy(maxx/2-100,100,"A Car Racing Game");
	outtextxy(maxx/2-100,125,"A: Play");
	outtextxy(maxx/2-100,150,"B: Exit");
	outtextxy(maxx/2-100,175,"Choose A or B.");
	enteredChar1:
	enteredChar=getch();
	if (enteredChar=='a'||enteredChar=='A')
		startgame();
	else if(enteredChar=='b'||enteredChar=='B'){
		rectangle(maxx/2-200,maxy-200,maxx/2+200,maxy-175);
		outtextxy(maxx/2-175,maxy-186,"Are u sure u want to exit: (Y/N) ?");
		enteredChar2:
		enteredChar=getch();
		if (enteredChar=='y' || enteredChar=='Y')
			exit(0);
		else if(enteredChar=='n' || enteredChar=='N')
			goto menu;
		else
			goto enteredChar2;

	}else
		goto enteredChar1;
}

void startgame(){
	cleardevice();
	outtextxy(maxx/2-50,100,"Levels:");
	outtextxy(maxx/2-50,125,"Level 1");
	outtextxy(maxx/2-50,150,"Level 2");
	getch();
}
