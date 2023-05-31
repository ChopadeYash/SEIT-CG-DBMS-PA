/*DDA AND BRESENHAM ALGORITHM 
 Roll no- S150058647*/

//HEADER FILES
#include<stdio.h>
#include<string.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

//STRUCTURE OF PIXEL
struct pixel
{
	GLint x;
	GLint y;
};

pixel p[10];						//ARRAY OF STRUCTURE FOR STORING POLYGON VERTICES
int count=0,flag=0,flag2=0;
GLint XA,XB,YA,YB;					//COORDINATES OF LINE

//TO CALCULATE ROUND VALUE
float round_val(float a)
{
	return float(a+0.5);
}

//DDA(DIGITAL DIFFERENTIAL ANALYZER) ALGORITHM
void DDA(GLfloat X1,GLfloat Y1,GLfloat X2,GLfloat Y2)
{
	float dx,dy,steps,xinc,yinc,k,x,y;
	
	dx=X2-X1;					//CALCULATING DX AND DY
	dy=Y2-Y1;
	
	steps=(abs(dx)>abs(dy))?abs(dx):abs(dy);	//CALCULATE STEPS
	xinc=dx/steps;
	yinc=dy/steps;
	
	x=X1;						//ASSIGN STARTING COORDINATES TO X AND Y
	y=Y1;

	glColor3f(1.0,1.0,1.0);				//SET COLOUR OF POINTS
	glPointSize(3);	
	glBegin(GL_POINTS);				//BEGIN PLOTTING POINTS
	for(k=0;k<steps;k++)				//TILL NO OF STEPS
	{
		x+=xinc;
		y+=yinc;
		if(flag2%8<3)					//IF FLAG%8 IS LESS THAN 4 THEN PLOT
		{
			glVertex2f(round_val(x),round_val(y));
		}
		flag2++;
	}
	glEnd();					//END DDA
	glFlush();					//DISPLAY ALL VALUES ON WINDOW
}
//PLOTTING PIXEL 
void drawpixel(GLint a,GLint b)
{
	glColor3f(1.0,1.0,1.0);				//SETTING OF COLOUR
	glPointSize(3);					//THICKNESS OF LINE
	glBegin(GL_POINTS);				//BEGIN PLOTTING OF POINTS
	if(flag%8<3)					//IF FLAG%8 IS LESS THAN 4 THEN PLOT
	{
		glVertex2i(a,b);			//PLOTTING PIXEL
	}
	flag++;						//INCREMENT FLAG
	glEnd();					//END
}

//BRESENHAM LINE DRAWING ALGORITHM
void bresenham(GLint X1,GLint Y1,GLint X2,GLint Y2)
{
	int dx,dy,xinc,yinc,x,y,i,p,inc1,inc2;		//DECALRING VARIABLES
	
	dx=abs(X2-X1);					//CALCULATE DX AND DY BOTH MUST BE POSITIVE
	dy=abs(Y2-Y1);	
	
	xinc=1;						//SET XINCREMENT AS 1
	if(X2<X1)
	xinc=-1;

	yinc=1;						//SET YINCREMENT AS 1
	if(Y2<Y1)
	yinc=-1;

	x=X1;
	y=Y1;

	if(dx>dy)					//CHECK SLOPE OF LINE(NEGATIVE)
	{
		drawpixel(x,y);				//PLOT PIXEL
		p=2*dy-dx;				//CALCULATE PIXEL
		inc1=2*(dy-dx);
		inc2=2*dy;
	
		for(i=0;i<dx;i++)			//LOOP TILL DX
		{
			if(p>0)				//IF P IS > 0
			{			
				p+=inc1;		//INC P WITH INC1
				y+=yinc;		//INC Y
			}
			else
			p+=inc2;			//INC P WITH INC2
		x+=xinc;				//INC X
		drawpixel(x,y);				//PLOT PIXEL
		}
	}
	else						//POSITIVE OR ZERO SLOPE
	{
		drawpixel(x,y);				//PLOT PIXEL
		p=2*dx-dy;				//CALCULATE PIXEL
		inc1=2*(dx-dy);
		inc2=2*dx;
	
		for(i=0;i<dy;i++)			//LOOP TILL DX
		{
			if(p>0)				//IF P IS > 0
			{			
				p+=inc1;		//INC P WITH INC1
				x+=xinc;		//INC Y
			}
			else
			p+=inc2;			//INC P WITH INC2
		y+=yinc;				//INC X
		drawpixel(x,y);				//PLOT PIXEL
		}
	}
	glFlush();					//TO DISPLAY ALL PIXELS PLOTTED
}
//DRAW STRING 
void draw_string(int c)
{
	char str[]="left click to draw line and right click to complete polygon";
	int len,i,j;
	glColor3f(1.0,1.0,1.0);

	//DRAWING STRING
	if(c==1)					//STRING WILL PRINT FOR ONLY MOUSE FUNCTION 
	{
		glRasterPos2f(-280,220);
		len=(int)strlen(str);
		for(i=0;i<len;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
		}
	}
	//DRAWING CHARACTER 'X'
	str[0]='X';
	glRasterPos2f(300,-12);
	i=0;
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
	

	//DRAWING CHARACTER 'Y'
	str[0]='Y';
	glRasterPos2f(5,-230);
	i=0;
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
	
	//DRAWING (0,0) AT ORIGIN
	strcpy(str,"(0,0)");
	glRasterPos2f(10,-15);
	len=(int)strlen(str);
	for(i=0;i<len;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,str[i]);
	}
}
//FUNCTION TO DRAW AXIS
void draw_axis(int c)
{
	draw_string(c);
	glColor3f(0.0,0.0,1.0);				//SET COLOUR FOR AXIS
	glBegin(GL_LINES);				//START PLOTTING LINES
	glVertex2d(-320,0);
	glVertex2d(320,0);
	glVertex2d(0,-240);
	glVertex2d(0,240);
	glEnd();					//END
	glFlush();					//TO DISPLAY ALL PIXELS PLOTTED
}

//MOUSE FUNCTION
void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )//FOR LEFT CLICK
	{
		if(count==0)				//TAKING STARTING POINT AS INPUT
		{
			p[0].x=-(320-x);
			p[0].y=240-y;
			count++;			//INCREMENT COUNT
		}	
		else
		{
			p[count].x=-(320-x);		//TAKE NEXT POINT INPUT
			p[count].y=240-y;
			bresenham(p[count-1].x,p[count-1].y,p[count].x,p[count].y);	//CALL BRESENHAM TO DRAW LINE
			count++;			//INCREMENT COUNT
		}
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN && count>2)			//FOR RIGHT CLICK
	{
		bresenham(p[0].x,p[0].y,p[count-1].x,p[count-1].y);
	}
}

//WITHOUT MOUSE DISPLAY OF LINE
void disp()
{
	draw_axis(2);
	bresenham(XA,YA,XB,YB);
	//DDA(XA,YA,XB,YB);
}

//INIT FUNCTION
void init()
{
	glClearColor(0.0,0.0,0.0,1.0);			//SETTING BACKGROUND COLOR
	glClear(GL_COLOR_BUFFER_BIT);			//CLEARING SCREEN
	gluOrtho2D(-320,320,-240,240);			//SETTING COORDINATES OF FRAME
}

//MAIN FUNCTION
int main(int argc,char ** argv)
{
	int ch;
	printf("\n***MENU***\n1.With mouse\n2.Without mouse\n\nEnter choice::");
	scanf("%d",&ch);
	if(ch==2)
	{
		printf("\nEnter starting points::\nX(-320 to 320)::");
		scanf("%d",&XA);
		printf("Y(-240 to 240)::");
		scanf("%d",&YA);
		printf("\nEnter end points::\nX(-320 to 320)::");
		scanf("%d",&XB);
		printf("Y(-240 to 240)::");
		scanf("%d",&YB);
	}
	glutInit(&argc,argv);				//INITIALIZING GLUT
	glutInitDisplayMode(GLUT_RGB);			//SETTING DISPLAY MODE
	glutInitWindowSize(640,480);			//SETTING WINDOW SIZE
	glutInitWindowPosition(100,100);		//SETTING WINDOW POSITION
	glutCreateWindow("Bresenham");			//CREATE WINDOW 
	init();
	if(ch==2)
	{
		glutDisplayFunc(disp);
	}
	if(ch==1)
	{
		draw_axis(1);
		glutMouseFunc(mouse);
	}
	glutMainLoop();					//CONTINUOUS LOOP
	return 0;
}
