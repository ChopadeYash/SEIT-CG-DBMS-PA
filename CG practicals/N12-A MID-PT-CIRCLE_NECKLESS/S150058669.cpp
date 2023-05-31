/*
	Seat No : S150058669
	
	Problem Statement:
	Write a program in OpenGL on Linux Platform to draw a given design using midpoint/brasenham circle drawing algorithm. 
	Use mouse/without mouse to plot points 
*/


#include <iostream>
#include <math.h>
using namespace std;
#include <GL/glut.h>
#define torad 3.14/180
#define rad 180/3.14

int xc=0,yc=0;
int R=80;
int r=15;


void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    gluOrtho2D(-320,320,-240,240);
} 

void putpixels(int x,int y,int xc,int yc)
{
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex2i(xc+x, yc+y);
		glVertex2i(xc-x, yc+y);
		glVertex2i(xc+x, yc-y);
		glVertex2i(xc-x, yc-y);
		glVertex2i(xc+y, yc+x);
		glVertex2i(xc-y, yc+x);
		glVertex2i(xc+y, yc-x);
		glVertex2i(xc-y, yc-x);
	glEnd();
	glFlush();
}


void circle(int r,int xc,int yc)
{
	int x=0,y=r,p=1-r;
	
	while(x<=y)
	{
		putpixels(x,y,xc,yc);
		
		if(p>0)
		{
			x=x+1;
			y=y-1;
			p+=2*(x-y)+1;
		}
		else
		{
			x=x+1;
			p+=2*x+1;
		}
	}
}

void rot(int* x1,int* y1,float angle)
{
	angle*=torad;
	
	int x=*x1,y=*y1;
	int t=x;
	x=(x*cos(angle))+(y*sin(angle));
	y=y*cos(angle)-t*sin(angle);
	
	*x1=x; *y1=y;
}



void renderFunction()
{

		circle(R,xc,yc);	
		circle(r,xc,yc-(R+r));
		circle(r,xc,yc-(R+3*r));
		
		int _x=xc,_y=yc-(R+r);
		rot(&_x,&_y,(2*r/float(R+r))*rad);
		circle(r,_x,_y);
		
		_x=xc,_y=yc-(R+r);
		rot(&_x,&_y,-(2*r/float(R+r))*rad);
		circle(r,_x,_y);
		
		_x=xc,_y=yc+R+r;
		rot(&_x,&_y,60);
		circle(r,_x,_y);
		
		int xinc=2*r*cos(30*torad);
		int yinc=2*r*sin(30*torad);
		for(int i=0;i<6;i++)
		{
			_x+=xinc; _y+=yinc;
			rot(&_x,&_y,-6);
			circle(r,_x,_y);
		}	
		
		_x=xc,_y=yc+R+r;
		rot(&_x,&_y,-60);
		circle(r,_x,_y);
		for(int i=0;i<6;i++)
		{
			_x-=xinc; _y+=yinc;
			rot(&_x,&_y,6);
			circle(r,_x,_y);
		}
		
}

int main(int argc, char** argv)
{
	cout<<"\nEnter radius ";
	cin>>R;
	r=15*R/float(80);

// Initialize glut library
  glutInit(&argc, argv);
// Set Display Mode  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
// Set window size  
  glutInitWindowSize(640,480);
// Set window position  
  glutInitWindowPosition(100,100);
// Create Window
  glutCreateWindow("Perl Neckless");
  init();
// Register display callback function  
  glutDisplayFunc(renderFunction);
// Enter event processing loop
  glutMainLoop();    
  return 0;
}
