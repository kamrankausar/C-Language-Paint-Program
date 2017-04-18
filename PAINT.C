//Code created by Md Kamran Kausar
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>

union REGS i,o;
int X,Y,COLOR=15,SIZE=0,CLEAR=0;

main()
{
	int gd=DETECT,gm,maxx,maxy,x,y,button,prevx,prevy,errorcode;
	char ch=99;
	initgraph(&gd,&gm,"c:\tc\bgi");
	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		gotoxy(12,13);
		printf("Graphics error: %s", grapherrormsg(errorcode));
		textcolor(RED + BLINK);
		cprintf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
    //	introduction();
	setbkcolor(0);
	maxx=getmaxx();
	maxy=getmaxy();
	COLOR=8;
	start();
	setcolor(15);
	settextstyle(3,1,1);
	outtextxy(25,102,"Devloped By:-Hasnain & Asif");
	settextstyle(1,0,1);
	outtextxy(170,10,"A Simple computer graphics package.");
	ohm();
	setcolor(4);
	rectangle(0,0,maxx-3,maxy);//outer box
	rectangle(2,2,maxx-5,maxy-2);
	begin:
	setcolor(9);
	AGAIN:
	   if(CLEAR)
	   {
		cleardevice();
		CLEAR=0;
		setcolor(15);
		settextstyle(3,1,4);
		outtextxy(-75,17,"nikhilkr@hotmail.com");
		settextstyle(10,0,4);
		outtextxy(70,-75,"NIKHIL'S PAINT 0.2");
		ohm();
		setcolor(4);
		rectangle(-100,-85,537,393);//outer box
		rectangle(-98,-83,536,391);
	   }
	setviewport(100,85,633,110,0);
	menu();
	if(initmouse()==0)
	{
		closegraph();
		restorecrtmode();
		printf("MOUSE DRIVER NOT LOADED");
		exit(1);
	}
	restrictmouseptr(0,0,maxx-8,maxy-5);
	showmouseptr();
	while(!kbhit())
	{
		getmousepos(&button,&x,&y);
		if((button & 1)==1)
		{
			hidemouseptr(); //hide mouse while drawing
			menu();
			prevx=x;
			prevy=y;
			while((button & 1)==1)
			{
				if(y>130 && prevy>130)//DRAW INSIDE WORK AREA
				{
					setcolor(COLOR);
					if(SIZE)
					{
						setfillstyle(1,COLOR);
						ellipse(x-100,y-85,0,360,SIZE,SIZE);
						fillellipse(x-100,y-85,SIZE,SIZE);
					}
					else
						line(prevx-100,prevy-85,x-100,y-85);
					prevx=x;
					prevy=y;
				}
				getmousepos(&button,&x,&y);
			}
			if(CLEAR)
				 goto AGAIN;
			showmouseptr();
		}
	}
	ch=getche();
	goto begin;
}
tools(int x,int y,int colour,int io)//   io => cursor inside/outside
{
	int xx,yy;
	setcolor(colour);
	if((x>577 && x<631)&&(y>100 && y<110) && io)
	{
		settextstyle(7,0,1);
		outtextxy(487,2,"QUIT");
	}
	else if(x>469 && x<593 && y>100 && y<110 && io)
	{
		settextstyle(11,0,1);
		outtextxy(372,2,"  BRUSH SIZE");
	}
	else if(x>100 && x<469 && y>85 && y<110 && io)
		rectangle(-2,-2,369,25);
	else if(io==0)
	{
		settextstyle(11,0,1);
		outtextxy(372,2,"  BRUSH SIZE");
		settextstyle(7,0,1);
		outtextxy(487,2,"QUIT");
		setcolor(7);
		rectangle(-2,-2,369,25);
	}
	return;
}
set_color()
{
	int i,j,x=0;
	setcolor(1);
	for(i=15;i>=0;i--)
	{
		setcolor(15);
		ellipse(x+12,13,0,360,11,11);
		setfillstyle(1,i);
		fillellipse(x+12,13,11,11);
		x+=23;
	}
	return;
}
menu()
{
	int maxx,maxy;
	maxx=getmaxx();
	maxy=getmaxy();
	setcolor(8);
       //	setlinestyle(1,1,1);
	rectangle(0,0,maxx-107,maxy-88);//inner box
	setcolor(7);
	rectangle(-3,-3,maxx-106,maxy-88);
	gotoxy(31,8);
	line(0,25,533,25);//toolbar line
	line(369,25,369,0);//color divide line
	line(478,25,478,0);//fill divide line
	line(370,10,477,10);//partition line of size
	rectangle(386,10,417,25);//brush size
	rectangle(400,10,434,25);//  " "
	rectangle(448,10,465,25);//  " "
	settextstyle(11,0,1);
	rectangle(145,25,202,45);//circle box line
	rectangle(260,25,377,45);
	outtextxy(90,32,"CIRCLE   BOX    LINE   LINE PATTERN ");
	outtextxy(382,32,"CLEAR");
	line(0,45,531,45);
	line(425,25,425,45); // x/y divide line
	line(80,25,80,45);//TIME
	setcolor(14);
	settextstyle(11,0,1);
	setcolor(13);
	outtextxy(375,15,"0 1 2 3 4 5 6");
	set_color();
	return;
}
initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
}
showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
	return;
}
hidemouseptr()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
	return;
}
restrictmouseptr(int x1,int y1,int x2,int y2)
{
	i.x.ax=7;
	i.x.cx=x1;
	i.x.dx=x2;
	int86(0x33,&i,&o);
	i.x.ax=8;
	i.x.cx=y1;
	i.x.dx=y2;
	int86(0x33,&i,&o);
	return;
}
getmousepos(int *button,int *x,int *y)
{
	struct time t;
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
	gotoxy(68,8);
	printf("X:%d  Y:%d",*x,*y);
	gettime(&t);
	gotoxy(14,8);
	printf("%2d:%02d:%02d ",t.ti_hour, t.ti_min, t.ti_sec);
	ohm();
	if(*y<110)
		tools(*x,*y,10,1);
	else if(*y>110)
		tools(*x,*y,6,0);//outside the tool-box
	if((*button & 1)==1)
		click(*x,*y);
	return;
}
click(int x,int y)
{
	if((x>100 && x<123)&&(y>90 && y<110))//COLOR OF BRUSH SELECTION
		COLOR=15;
	else if((x>123 && x<146)&&(y>90 && y<110))
		COLOR=14;
	else if((x>146 && x<169)&&(y>90 && y<110))
		COLOR=13;
	else if((x>169 && x<192)&&(y>90 && y<110))
		COLOR=12;
	else if((x>192 && x<215)&&(y>90 && y<110))
		COLOR=11;
	else if((x>215 && x<238)&&(y>90 && y<110))
		COLOR=10;
	else if((x>238 && x<261)&&(y>90 && y<110))
		COLOR=9;
	else if((x>261 && x<284)&&(y>90 && y<110))
		COLOR=8;
	else if((x>284 && x<307)&&(y>90 && y<110))
		COLOR=7;
	else if((x>307 && x<330)&&(y>90 && y<110))
		COLOR=6;
	else if((x>330 && x<353)&&(y>90 && y<110))
		COLOR=5;
	else if((x>353 && x<376)&&(y>90 && y<110))
		COLOR=4;
	else if((x>376 && x<399)&&(y>90 && y<110))
		COLOR=3;
	else if((x>399 && x<422)&&(y>90 && y<110))
		COLOR=2;
	else if((x>422 && x<444)&&(y>90 && y<110))
		COLOR=1;
	else if((x>444 && x<469)&&(y>90 && y<110))
		COLOR=0;
	else if((x>469 && x<486)&&(y>90 && y<110)) //BRUSH SIZE SELECTION
		SIZE=0;
	else if((x>486 && x<500)&&(y>90 && y<110))
		SIZE=1;
	else if((x>500 && x<517)&&(y>90 && y<110))
		SIZE=2;
	else if((x>517 && x<534)&&(y>90 && y<110))
		SIZE=3;
	else if((x>534 && x<548)&&(y>90 && y<110))
		SIZE=4;
	else if((x>548 && x<565)&&(y>90 && y<110))
		SIZE=5;
	else if((x>565 && x<577)&&(y>90 && y<110))
		SIZE=6;
	else if((x>180 && x<244)&&(y>112 && y<130))
		draw(2,0);
	else if((x>244 && x<302)&&(y>112 && y<130))
		draw(1,0);
	else if((x>302 && x<360)&&(y>112 && y<130))
		draw(3,0);
	else if((x>360 && x<477)&&(y>112 && y<130))
		draw(3,1);
	else if((x>477 && x<579)&&(y>112 && y<130))
		CLEAR=1;
	else if((x>579 && x<631)&&(y>90 && y<110))  //QUIT CLICKED
	{
		start();
		exit(1);
	}
	return;
}
draw(int flag,int pat)
{
	int button,x,y,sx,sy,x1,x2,y1,y2,tx,ty,lx,ly,prex,prey,rx,ry;
	do
	{
		showmouseptr();
		getmousepos(&button,&tx,&ty);
		if((button && 2 ==2)&& ty>131 && tx>100)
		{
			hidemouseptr();
			prex=sx=x=x1=x2=tx;
			prey=sy=y=y1=y2=ty;
			lx=x;
			ly=y;
			setcolor(COLOR);
			rx=x2-x1;
			ry=y2-y1;
			if(flag==2)
				ellipse(x1-100,y1-85,0,360,rx,ry);
			else if(flag==1)
				rectangle(x1-100,y1-85,x2-100,y2-85);
			else if(flag==3 &&pat==0)
				line(lx-100,ly-85,tx-100,ty-85);
			getmousepos(&button,&tx,&ty);
			while((button &2)==2)
			{
				if((x!=tx || y!=ty) && ty>130 && tx>100)
				{
					setcolor(0);
					ry=y2-y1;
					rx=x2-x1;
					if(flag==2)
					{
						if(((y1-ry)>131 && (x1-rx)>100))
							ellipse(x1-100,y1-85,0,360,rx,ry);
						else
							start();
					}
					else if(flag==1&& (y2-85)>25)
						rectangle(x1-100,y1-85,x2-100,y2-85);
					else if(flag==3)
						line(lx-100,ly-85,tx-100,ty-85);
					x=tx;
					y=ty;
					if(x<sx)
					{
						x1=x;
						x2=sx;
					}
					else
					{
						x1=sx;
						x2=x;
					}
					if(y<sy)
					{
						y1=y;
						y2=sy;
					}
					else
					{
						y1=sy;
						y2=y;
					}
					setcolor(COLOR);
					ry=y2-y1;
					rx=x2-x1;
					if(flag==2)
					{
						if(((y1-ry)>131 && (x1-rx)>100))
							ellipse(x1-100,y1-85,0,360,rx,ry);
						else
						{
							settextstyle(11,0,1);
							setcolor(9);
							outtextxy(430,52,"OUT OF RANGE");
							start();
							delay(800);
							setcolor(0);
							outtextxy(430,52,"OUT OF RANGE");
						}
					}
					else if(flag==1)
						rectangle(x1-100,y1-85,x2-100,y2-85);
					else if(flag==3 &&pat==0)
					{
						line(lx-100,ly-85,x-100,y-85);
						setcolor(0);
						line(lx-100,ly-85,prex-100,prey-85);
						prex=tx;
						prey=ty;
					}
					else if(flag==3 && pat==1)
						line(lx-100,ly-85,x-100,y-85);
				}
				getmousepos(&button,&tx,&ty);
			}
			showmouseptr();
			if(flag==3)
			{
				setcolor(COLOR);
				line(lx-100,ly-85,x-100,y-85);
			}
		}
	}
	while((button & 1)!=1);
	return;
}
introduction()
{
	char a[10]="MATRIX";
	int i;
	setbkcolor(1);
	gotoxy(35,13);
	delay(1400);
	for(i=0;i<6;i++)
	{
		delay(400);
		printf("%c ",a[i]);
		sound(5000);
		delay(50);
		nosound();
	}
	setcolor(10);
	line(200,210,450,210);
	sound(8000);
	delay(400);
	nosound();
	cleardevice();
	setcolor(4);
	settextstyle(8,0,3);
	outtextxy(200,200,"PRESS ANY KEY...");
	getch();
	cleardevice();
	return;
}
start()
{
	sound(2550);
	delay(100);
	nosound();
	return;
}
ohm()
{
	setfillstyle(1,COLOR);
	fillellipse(-40,-45,45,15);
	setcolor(COLOR+2);
	settextstyle(8,0,3);
	outtextxy(-64,-62,"JMI");
	return;
}
