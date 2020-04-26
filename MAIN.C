/*
Project of BIT first semester:

##^^A 2D car racing game^^##

Description:


Starting date:20 April,2020

Completion date:-----------

A project by:
-Rohan Dhimal
-Prahlad Neupane
-Puskar Humagain
-Bibek Dhital

Special Thanks to


*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <time.h>



//global variables
int x,y,xline1,xline2,trackLength,speed,readhighscore=0;
long int score;
char msg[100];
struct enemycarPosition{
	int x1,x2,y1,y2;
} e;
struct mycarPosition{
	int x1,x2,y1,y2;
} m;
struct enemycarPosition1{
	int x1,x2,y1,y2;
} e1;

struct highsc{
	char name[20];
	long int hscore;
}h[5];

//user-defined functions
void setgraphics();
void startgame();
void loadingscreen();
void mainmenu();
void mycar(int);
void enemycar(int *);
int collisionDetection(struct mycarPosition mc,struct enemycarPosition ec);
int collisionDetection1(struct mycarPosition mc,struct enemycarPosition1 ec1);
void draw(long int,int);
int scoreincrease(long int,int);
void pause();
void gameover(long int);
void defaultColor();
void colorSelect(int,int);
void enemycar1(int *);
void displayControls();
void showHighscores();
void readHighscore();
void showCredits();
void takeuserdetails(long int);
int updateHighscore();
int checkifscoredHigh(long int);




int main(){

	setgraphics();
	x=getmaxx();
	y=getmaxy();
	defaultColor();
	loadingscreen();
	mainmenu();
	closegraph();
	return 0;

}

void setgraphics() {
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C://turboc3//bgi");
}

void loadingscreen(){
	int i=0;
	cleardevice();
	settextstyle(4,0,5);//font direction size
	outtextxy(x/2-200,y/2,"A 2D Car Racing Game");
	delay(1000);

	settextstyle(3,0,1);
	outtextxy(x/2-100,y-120,"LOADING....");

	while (i!=200){
		rectangle(x/2-100,y-85,x/2-100+i,y-75);
		rectangle(x/2-100,y-85,x/2+100,y-75);
		i++;
		delay(10);
	}
}

void mainmenu(){
	int selection=0;

	cleardevice();

	settextstyle(3,0,3);
	defaultColor();


	while(1){
		cleardevice();

		score=0;
		speed=1;


		outtextxy(x/2-100,100,"Play");
		outtextxy(x/2-100,150,"Controls");
		outtextxy(x/2-100,200,"HighScores");
		outtextxy(x/2-100,250,"Customize");
		outtextxy(x/2-100,300,"Credits");
		outtextxy(x/2-100,350,"Exit");
		circle(x/2-110,125,5);
		circle(x/2-110,175,5);
		circle(x/2-110,225,5);
		circle(x/2-110,275,5);
		circle(x/2-110,325,5);
		circle(x/2-110,375,5);

		setfillstyle(SOLID_FILL,BLUE);
		floodfill(x/2-110,125+50*selection,BLUE);

		switch(getch()){
			case 'W':
			case 'w':
				if (selection==0)
					selection=5;
				else
					selection--;
				break;
			case 's':
			case 'S':
				if (selection==5)
					selection=0;
				else
					selection++;
				break;
			case 13://enterkey - CR
				if (selection==0){
					startgame();
				}
				else if(selection==1){
					displayControls();
				}
				else if(selection==2){
					showHighscores();
				}
				else if(selection==3){
					//customize();
				}
				else if (selection==4){
					showCredits();
				}
				else {
					exit(0);
				}

				break;
			default:
				break;
		}

	}
}


void startgame(){
	int i,mycarLocation=1,collision=0,activateEnemy1=0;
	int *enemycarPos,*enemycarPos1;
	cleardevice();
	randomize();
	setbkcolor(WHITE);
	setcolor(BLUE);

	for(i=3;i!=0;i--){
		cleardevice();
		sprintf(msg,"Starting in %d...",i);
		outtextxy(x/2-50,100,msg);
		delay(500);
	}

	colorSelect(7,WHITE);//lightgray
	settextstyle(0,0,1);
	xline1=x/2-75;
	xline2=x/2+75;
	trackLength=xline2-xline1;
	*enemycarPos=0;
	*enemycarPos1=0;

	while(1){
		cleardevice();
		draw(score,speed);
		enemycar(enemycarPos);
		if (activateEnemy1==1){
			enemycar1(enemycarPos1);
			*enemycarPos1=*enemycarPos1+speed+1;
		}
		mycar(mycarLocation);

		collision=collisionDetection(m,e)+collisionDetection1(m,e1);
		if (collision==1){
			gameover(score);
		}


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
				case 'p':
				case 'P':
					pause();
					break;
				case 'X':
				case 'x':
					exit(0);
					break;
				default:
					break;


			}
		}
		*enemycarPos=*enemycarPos+speed+1;
		score=score+speed*1;
		if (*enemycarPos>y/2)
			activateEnemy1=1;
		speed=speedincrease(score,speed);
		delay(10);

	}
}

void mycar(int carLocation){
	m.x1=xline1+(trackLength/3*carLocation)+3;
	m.x2=xline1+(trackLength/3*(carLocation+1))-3;
	m.y1=y-3;
	m.y2=y-50;
	rectangle(m.x1,m.y1-35,m.x2,m.y1);//big block
	rectangle(m.x1+10,m.y2+13,m.x2-10,m.y1);//middle block
	rectangle(m.x1+5,m.y2,m.x2-5,m.y2+13);//front block
	setcolor(WHITE);
	bar(m.x1+3,m.y2+3,m.x1+5,m.y2+13);//left tyre
	bar(m.x2-3,m.y2+3,m.x2-5,m.y2+13);//right tyre


}

void enemycar(int *i){
	static int enemycarLoc;
	if (*i==0){
		enemycarLoc=random(100)%3;
		e.x1=xline1+3+(trackLength/3)*enemycarLoc;
		e.x2=xline1+(trackLength/3*(enemycarLoc+1))-3;
	}
	e.y1=*i+3;
	e.y2=*i+48;
	rectangle(e.x1,e.y1,e.x2,e.y1+33);//big block
	rectangle(e.x1+5,e.y1+33,e.x2-5,e.y2);//front block
	setfillstyle(SOLID_FILL,WHITE);
	bar(e.x1+3,e.y1+33,e.x1+5,e.y2-3);//left tyre
	bar(e.x2-5,e.y1+33,e.x2-3,e.y2-3);//right tyre
	if(e.y1>y)
		*i=-speed-1;
}

void enemycar1(int *j){
	static int enemycarLoc1;
	if (*j==0){
		enemycarLoc1=random(100)%3;
		e1.x1=xline1+3+(trackLength/3)*enemycarLoc1;
		e1.x2=xline1+(trackLength/3*(enemycarLoc1+1))-3;
	}
	e1.y1=*j+3;
	e1.y2=*j+48;
	rectangle(e1.x1,e1.y1,e1.x2,e1.y1+33);//big block
	rectangle(e1.x1+5,e1.y1+33,e1.x2-5,e1.y2);//front block
	setfillstyle(SOLID_FILL,WHITE);
	bar(e1.x1+3,e1.y1+33,e1.x1+5,e1.y2-3);//left tyre
	bar(e1.x2-5,e1.y1+33,e1.x2-3,e1.y2-3);//right tyre
	if(e1.y1>y)
		*j=-speed-1;
}

int collisionDetection(struct mycarPosition mc,struct enemycarPosition ec  ){
	if (ec.x1>mc.x2){
		return 0;
	}
	else{
		if(ec.x2<mc.x1) {
			return 0;
		}else{
			if(ec.y1>mc.y1){
				return 0;
			}else{
				if(ec.y2<mc.y2){
					return 0;
				}else{
					return 1;
				}
			}
		}
	}

}
int collisionDetection1(struct mycarPosition mc,struct enemycarPosition1 ec ){
	if (ec.x1>mc.x2){
		return 0;
	}
	else{
		if(ec.x2<mc.x1) {
			return 0;
		}else{
			if(ec.y1>mc.y1){
				return 0;
			}else{
				if(ec.y2<mc.y2){
					return 0;
				}else{
					return 1;
				}
			}
		}
	}

}

void draw(long int sc,int sp){
	line(xline1,0,xline1,y);
	line(xline2,0,xline2,y);
	sprintf(msg, "Score : %ld ",sc);
	outtextxy(xline2+20,y/2,msg);
	sprintf(msg,"Speed: %d",sp);
	outtextxy(xline1-100,y/2,msg);

}

int speedincrease(long int sc ,int sp){

	switch(sp){
		case 1:
			if (sc>1000)
				sp++;
			break;
		case 2:
			if (sc>2000)
				sp++;
			break;
		case 3:
			if (sc>4000)
				sp++;
			break;
		case 4:
			if (sc>8000)
				sp++;
			break;
		case 5:
			if (sc>16000)
				sp++;
			break;
		case 6:
			if (sc>32000)
				sp++;
			break;
		case 7:
			if (sc>64000)
				sp++;
			break;
		case 8:
			if (sc>120000)
				sp++;
			break;
		case 9:
			if (sc>240000)
				sp++;
			break;
		default:
			break;
	}
	return sp;


}

void pause(){
	int the_end=0;

	setfillstyle(SOLID_FILL,8);//darkgray

	bar(xline1,y/2-210,xline2,y/2-180);

	//pause symbol
	line(xline1+50,y/2-200,xline1+50,y/2-190);//straight line
	line(xline1+50,y/2-200,xline1+60,y/2-195);//back slash line
	line(xline1+50,y/2-190,xline1+60,y/2-195);//front slash line

	outtextxy(xline1+70,y/2-200,"Paused");
	while(!the_end){
		switch(getch()){
			case 'p':
			case 'P':
				the_end=1;
				break;
			case 'm':
			case 'M':
				mainmenu();
				break;
			case 'x':
			case 'X':
				exit(0);
				break;
			default:
				break;
		}
	}
}

void gameover(long int sc){
	setfillstyle(SOLID_FILL,8);//darkgray

	bar(xline1,y/2-210,xline2,y/2-180);

	outtextxy(xline1+40,y/2-200,"Game Over");
	delay(10);
	getch();
	cleardevice();
	sprintf(msg,"Score: %ld",score);
	outtextxy(10,100,msg);
	if (checkifscoredHigh(sc)==1)  {
			outtextxy(10,130,"Congrats! You made your way to the Highscore Table.");
			outtextxy(10,150,"Press any key to continue.");
			getch();
			takeuserdetails(score);
	}
	else{
		outtextxy(10,130,"Sorry! You couldn't made your way to the Highscore Table.");
		outtextxy(10,150,"Press any key to return to mainmenu.");
		getch();
	}
	mainmenu();
}

void defaultColor(){
	setbkcolor(WHITE);
	setcolor(BLUE);
}

void colorSelect(int a,int b){
	setbkcolor(a);
	setcolor(b);
}

void displayControls(){
	cleardevice();
	settextstyle(3,0,4);
	outtextxy(x/2-100,100,"CONTROLS");
	settextstyle(3,0,2);
	outtextxy(100,150,"Upward");
	outtextxy(400,150,"W");
	outtextxy(100,175,"Downward");
	outtextxy(400,175,"S");
	outtextxy(100,200,"Left");
	outtextxy(400,200,"A");
	outtextxy(100,225,"Right");
	outtextxy(400,225,"D");
	outtextxy(100,250,"Pause/Resume");
	outtextxy(400,250,"P");
	outtextxy(100,275,"Direct Exit (while playing)");
	outtextxy(400,275,"X");
	outtextxy(100,300,"Mainmenu (when paused)")  ;
	outtextxy(400,300,"M");
	outtextxy(100,400,"Press any key to return to mainmenu.");

	getch();
	mainmenu();

}

void showCredits(){
	cleardevice();
	settextstyle(3,0,4);
	outtextxy(x/2-100,100,"CREDITS");
	settextstyle(3,0,2);
	outtextxy(100,150,"This game is developed by:");
	outtextxy(125,175,"-Rohan Dhimal");
	outtextxy(125,200,"-Prahlad Neupane");
	outtextxy(125,225,"-Puskar Humagain");
	outtextxy(125,250,"-Bibek Dhital");
	outtextxy(100,275,"Special thanks to: Kamal Rana Sir");

	outtextxy(100,350,"Press any key to return to mainmenu.");

	getch();
	mainmenu();

}

void showHighscores(){
	int i;
	cleardevice();

	if (readhighscore==0)
		readHighscore();

	settextstyle(3,0,4);
	outtextxy(x/2-100,100,"HighScore");

	settextstyle(3,0,3);

	for (i=0;i<5;i++){
		sprintf(msg,"%d. %s",i+1,h[i].name);
		outtextxy(100,150+i*25,msg);
		sprintf(msg,"%ld",h[i].hscore);
		outtextxy(400,150+i*25,msg);
	}

	outtextxy(100,150+i*25+100,"Press any key to return to mainmenu.");
	getch();
}

void readHighscore(){

	size_t elements_read;
	FILE *fp;
	fp=fopen("highscore.bin","rb");
	if (fp==NULL){
		outtextxy(x/2-50,y/2,"Error");
		getch();
		mainmenu();
	}else{

		elements_read=fread(&h,sizeof(struct highsc),5,fp);
		fclose(fp);
		if (elements_read==0){
			outtextxy(x/2-50,y/2,"Error");
			getch();
			mainmenu();
		}else{
			readhighscore=1;
		}

	}

}

void takeuserdetails(long int sc){

	char inputbuf[20];
	int input_pos = 0;
	char c;
  	int the_end = 0;

  	strcpy(inputbuf,"\0");

  	 do { 
		cleardevice();
		outtextxy(10,140,"Enter your name:");
		setfillstyle(SOLID_FILL,8);
		bar(10,160,300,200);

		outtextxy (15,175, inputbuf);
		c = getch();
		switch (c)
		{
			case 8: /* backspace */
			if (input_pos)
			{
				input_pos--;
				inputbuf[input_pos] = 0;
			}
			break;
			case 13: /* return */
			the_end = 1;
			break;
			case 27: /* Escape = Abort */
			inputbuf[0] = 0;
			the_end = 1;
			break;
			default:
			if (input_pos < 20-1 && c >= ' ' && c <= '~')
			{
				inputbuf[input_pos] = c;
				input_pos++;
				inputbuf[input_pos] = 0;
			}
 		}
	} while (!the_end);


	h[4].hscore=sc;
	strcpy(h[4].name,inputbuf);
	if (updateHighscore()==0){
		outtextxy(10,220,"Unable to updte Highscore.");
		outtextxy(10,240,"Press any key to return to mainmenu.");
	}else{
		outtextxy(10,220,"Highscore successfully updated.");
		outtextxy(10,240,"Press any key to return to mainmenu.");

	}
	


	
	getch();

}

int updateHighscore(){
	char ch[20];
	int i,j=4;
	long int k;
	size_t elements_written;
	FILE *fp;

	for(i=3;i>0,j>0;i--){
		if (h[j].hscore>h[i].hscore){

			k=h[j].hscore;
			h[j].hscore=h[i].hscore;
			h[i].hscore=k;

			strcpy(ch,h[j].name);
			strcpy(h[j].name,h[i].name);
			strcpy(h[i].name,ch);

			j=i;

		}else{
			break;
		}
	}

	fp=fopen("highscore.bin","wb");
	if (fp==NULL){
		return 0;
	}else{
		elements_written=fwrite(&h,sizeof(struct highsc),5,fp);
		fclose(fp);
		if (elements_written==0){
			return 0;
		}else{
			return 1;
		}

	}


	
}


int checkifscoredHigh(long int sc){
	if (readhighscore==0)
		readHighscore();
	if (sc>h[4].hscore)
		return 1;
	else
		return 0;
}







