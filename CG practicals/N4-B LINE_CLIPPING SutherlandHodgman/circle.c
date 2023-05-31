#include<stdio.h>	//initial inclusions
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
int xc,yc,xo,yo,r;
static int p=0;
void setpoint(int x,int y)		//setting point on the window
{
	if(p>2)
	{
		if(p==4)
			p=0;
		else
			p++;
	}
	else
	{
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		p++;
	}
	

}
void plotpoint(int x,int y)  //plotting points in all octants
{
	setpoint(xc+x,yc+y);
	setpoint(xc-x,yc+y);
	setpoint(xc+x,yc-y);
	setpoint(xc-x,yc-y);
	setpoint(xc+y,yc+x);
	setpoint(xc-y,yc+x);
	setpoint(xc+y,yc-x);
	setpoint(xc-y,yc-x);
}
void midpoint(int rad)		//midpoint circle drawing algorithm
{
	int x=0,y=rad,p=1-rad;
	plotpoint(x,y);			//plotting initial point
	while(y>x)				//iterating till y>x
	{
		x=x+1;				//incrementing x
		if(p>0)				//checking condition for p
		{
			y--;			//decrementing y
			p+=2*(x-y)+1;	//changing value of p
		}
		else
		{
			p+=2*x+1;		//changing value of p
		}
		plotpoint(x,y);
	}

}
void mouse(int btn,int state,int x,int y)
{
	static int q=1;
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)//checking left click
	{
		switch(q)
		{
			case 1:midpoint(r);
					q++;
					break;
			case 2:yc=yc+2*r;
					midpoint(r);
					q++;
					break;
			case 3:yc=yo;
					yc=yc-2*r;
					midpoint(r);
					q++;
					break;
			case 4:xc=xo;
					yc=yo;
					xc=xc+2*r*0.866;
					yc=yc+r;
					midpoint(r);
					q++;
					break;
			case 5:xc=xo;
					yc=yo;
					xc=xc+2*r*0.866;
					yc=yc-r;
					midpoint(r);
					q++;
					break;
			case 6:xc=xo;
					yc=yo;
					xc=xc-2*r*0.866;
					yc=yc-r;
					midpoint(r);
					q++;
					break;
			case 7:xc=xo;
					yc=yo;
					xc=xc-2*r*0.866;
					yc=yc+r;
					midpoint(r);
					q++;
					break;
			case 8:xc=xo;
					yc=yo;
					midpoint(3*r);
					q++;
					break;
					
					
		}
		
		glFlush();
	}

}
void init()
{
	glClearColor(1.0,1.0,1.0,0);		//clearing background color to new color
	glClear(GL_COLOR_BUFFER_BIT);		//clearing buffer
	gluOrtho2D(0,640,0,480);		//decalring ortho 2d coordinates
	glPointSize(1);						//decalring point size
	glFlush();
}
int main(int argc,char **argv)
{
	printf("Enter coordinates of centre of circle\n");
	printf("\nX: ");
	scanf("%d",&xc);			//accepting centre
	printf("\nY: ");
	scanf("%d",&yc);			//accepting centre
	xo=xc;
	yo=yc;
	printf("\nEnter radius of circle:");
	scanf("%d",&r);				//accepting radius
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Circle Pattern");
	init();
	//glutDisplayFunc(disp);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
