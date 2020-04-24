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

int x,y,setgraph=0,xline1,xline2,trackLength;

void setgraphics();
void closegraphics();
void startgame();
void loadingscreen();
void mainmenu();
void mycar(int);


int main(){

	if (setgraph==0)
	 setgraphics();
	x=getmaxx();
	y=getmaxy();
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
		rectangle(x/2-100,y-100,x/2-100+i,y-75);
		rectangle(x/2-100,y-100,x/2+100,y-75);
		i++;
		delay(10);
	}
	outtextxy(x/2-100,100,"Press any key to continue:");
	getch();
}

void mainmenu(){
	int selection=1;

	cleardevice();

	
	while(1){
		cleardevice();

		outtextxy(x/2-100,100,"A Car Racing Game");
	
		outtextxy(x/2-100,125,"Play");
		outtextxy(x/2-100,150,"Exit");
		circle(x/2-110,125,5);
		circle(x/2-110,150,5);
		setfillstyle(SOLID_FILL,BLUE);
		floodfill(x/2-110,100+25*selection,BLUE);

		switch(getch()){
			case 'W': 
			case 'w':
				if (selection!=1)
					selection--;
				break;
			case 's':
			case 'S':
				if (selection!=2)
					selection++;
				break;
			case 13://enterkey - CR
				if (selection==1)
					startgame();
				else
					exit(0);
				break;
			default:
				break;
		}

	}
}


void startgame(){
	int i,accident=0,mycarLocation=1;
	char msg[100];
	cleardevice();

	for(i=3;i!=0;i--){
		cleardevice();
		sprintf(msg,"Starting in %d...",i);
		outtextxy(x/2-50,100,msg);
		delay(1000);
	}
	i=0;
	xline1=(x-300)/2;
	xline2=300+xline1;
	trackLength=xline2-xline1;

	while(accident==0){
		cleardevice();
		line(xline1,0,xline1,y);
		line(xline2,0,xline2,y);
		mycar(mycarLocation);


		if(kbhit()){
			switch(getch()){
				case 'A':
				case 'a':
					if(mycarLocation!=0)
						mycarLocation--;
					break;
				case 'd':
				case 'D':
					if(mycarLocation!=2)
						mycarLocation++;
					break;
				case 'X':
				case 'x':
					exit(0);
					break;
				default:
					break;


			}
		}

	}
	getch();
}

void mycar(int carLocation){
	int x1,x2;
	x1=xline1+(trackLength/3*carLocation)+5;
	x2=xline1+(trackLength/3*(carLocation+1))-5;
	rectangle(x1,y-75,x2,y-5);
	rectangle(x1+20,y-75,x2-20,y-5);
	rectangle(x1+10,y-100,x2-10,y-75);
	circle(x1+5,y-86,5);
	circle(x2-5,y-86,5);
}