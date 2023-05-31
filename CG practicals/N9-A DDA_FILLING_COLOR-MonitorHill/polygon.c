#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
double x1,x2,y1,y2;
//struct pixel to store color in rgb format
typedef struct pixel
{
	float r,g,b;
}pixel;

pixel f_clr,b_clr;//fill color and boundary color
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);//to set background color
    glClear(GL_COLOR_BUFFER_BIT);//to apply back ground color to screen
    glColor3f(0.0, 0.0, 0.0);//to set color of object to be shown on screen
    gluOrtho2D(0,500,0,500);//to set 2D projection rectangle
}
void dda(double x1,double y1,double x2,double y2)
{
	double dx,dy,steps;
	float xi,yi;
	dx=x2-x1;
	dy=y2-y1;
	steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
	xi=dx/(float)steps;
	yi=dy/(float)steps;
	int i;
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(x1,y1);
	for(i=0;i<steps;i++)
	{
		x1+=xi;
		y1+=yi;
		glVertex2d(x1,y1);
	}
	glEnd();
	glFlush();
}
void boundary_fill(int x,int y)
{
	pixel c;
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,&c);//function to read color 
	if((c.r!=b_clr.r||c.g!=b_clr.g||c.b!=b_clr.b)&&(c.r!=f_clr.r||c.g!=f_clr.g||c.b!=f_clr.b))
	{
		glBegin(GL_POINTS);
		glColor3f(f_clr.r,f_clr.g,f_clr.b);
		glVertex2i(x,y);
		glEnd();
		glFlush();
		boundary_fill(x-1,y);
		boundary_fill(x+1,y);
		boundary_fill(x,y-1);
		boundary_fill(x,y+1);
	}
	glFlush();
}
void renderFunction()
{
	int i;
    glClear(GL_COLOR_BUFFER_BIT);
    dda(100,100,200,100);
    dda(200,100,170,75);
    dda(170,75,330,75);
    dda(330,75,300,100);
    dda(300,100,400,100);
    dda(100,100,100,300);
    dda(100,300,400,300);
    dda(400,300,400,100);
    dda(125,125,375,125);
    dda(125,125,125,275);
    dda(125,275,375,275);
    dda(375,275,375,125);
    dda(125,125,200,200);
    dda(200,200,250,125);
    dda(250,125,300,250);
    dda(300,250,375,125);
    b_clr.r=0.0f;
    b_clr.g=0.0f;
    b_clr.b=0.0f;
    f_clr.r=1.0f;
    f_clr.g=0.0f;
    f_clr.b=0.0f;
    boundary_fill(120,120);
    f_clr.r=0.0f;
    f_clr.g=1.0f;
    f_clr.b=0.0f;
    boundary_fill(135,130);
    boundary_fill(360,130);
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    init();
    glutDisplayFunc(renderFunction);
    glutMainLoop();    
    return 0;
}
