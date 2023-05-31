#include<GL/glut.h>
#include<iostream>

using namespace std;
int frame=0;
void Init()
{
  glClearColor(1,1,1,1); 
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-640,640,-480,480);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
}

void dda(int x1,int y1,int x2,int y2)
{
  float dx=x2-x1;
  float dy=y2-y1;
  float steps=((abs(dx)>abs(dy))?abs(dx):abs(dy));
  float xinc=dx/steps;
  float yinc=dy/steps;
  int x=x1,y=y1;
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  while(steps>=0)
  {
    x+=xinc;
    y+=yinc;
    glVertex2i(x,y);
    steps--;
  } 
  glEnd();
}

void putpixel(int x,int y)
{
glColor3f(0,0,0);
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();

}

void show(int xc,int yc,int x,int y)
{
  putpixel(xc+x,yc+y);
  putpixel(xc-x,yc+y);
  putpixel(xc+x,yc-y);
  putpixel(xc-x,yc-y);
  putpixel(xc+y,yc+x);
  putpixel(xc-y,yc+x);
  putpixel(xc+y,yc-x);
  putpixel(xc-y,yc-x);

}

void circle(int xc,int yc,int r)
{
  int x=0,y=r,p=1-r;
  show(xc,yc,x,y);
  while(x<y)
  {
    x++;
    if(p<0)
    p+=2*x+1;
    
    else 
    {
      y--;
      p+=2*(x-y)+1;
    }
  
   show(xc,yc,x,y);
  }

glFlush();
}


void second()
{
  glLineWidth(1);
  glColor3f(1,0,0);
  dda(0,0,0,100);
}


void minute()
{
  glColor3f(0,0,1);
  glLineWidth(3);
  glBegin(GL_LINES);
  glVertex2i(0,0);
  glVertex2i(80,0);
  glEnd();
}

void hour()
{
  glColor3f(0,0,0);
  glLineWidth(6);
  glBegin(GL_LINES);
  glVertex2i(0,0);
  glVertex2i(0,-50);
  glEnd();
}

void pendulum()
{
  glColor3f(0,0,0);
  glLineWidth(3);
  glBegin(GL_LINES);
  glVertex2i(0,-200);
  glVertex2i(0,-300);
  glEnd();
  
  circle(0,-340,40);

}
void coords()
{
circle(0,150,3);
circle(150,0,3);
circle(-150,0,3);
circle(0,-150,3);
circle(0,-150,3);

}
void display()
{
int angle;
 glClear(GL_COLOR_BUFFER_BIT);
circle(0,0,200);
coords();
glColor3f(0,0,0);

glPushMatrix();
glRotated(-frame*6,0,0,1);
second();
glPopMatrix();

glPushMatrix();
glRotated(-frame*6/60,0,0,1);
minute();
glPopMatrix();

glPushMatrix();
glRotated(-frame*6/3600,0,0,1);
hour();
glPopMatrix();
if(frame%2==0)
angle=30;
else 
angle=-30;

glPushMatrix();
glRotated(angle,0,0,1);
pendulum();
glPopMatrix();

glFlush();

}
void doframe(int v)
{
  frame++;
  glutPostRedisplay();
  glutTimerFunc(1000,doframe,0);

}
int main(int argv,char** argc)
{
 glutInit(&argv,argc);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(640,480);
 glutInitWindowPosition(0,0);
 glutCreateWindow("animation");
 Init();
 glutDisplayFunc(display);
 glutTimerFunc(100,doframe,0);
 glutMainLoop();
 return 0; 

}
