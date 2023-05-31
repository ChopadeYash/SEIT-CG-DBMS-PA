#include <GL/freeglut.h>
#include <GL/gl.h>
#include<iostream>
#include<math.h>
using namespace std;
float oldx=-0.7,oldy=0.5;
void koch(float dir,float len,float iter)
{
	double dirrad=0.0174533*dir;
	float newx= oldx + len* cos(dirrad);
	float newy= oldy + len* sin(dirrad);
	
	if(iter==0)
	{
		glVertex2f(oldx,oldy);
		glVertex2f(newx,newy);
		newx=oldx;
		newy=oldy;
	}
	else
	{
		iter--;
		koch(dir,len,iter);
		dir+=60;
		koch(dir,len,iter);
		dir-=120;
		koch(dir,len,iter);
		dir+=60;
		koch(dir,len,iter);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		koch(0.0,0.05,2);
		koch(-120.0,0.05,2);
		koch(120.0,0.05,2);
	glEnd();
	glFlush();
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("KOCH_CURVES");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
