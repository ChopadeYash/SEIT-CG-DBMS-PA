#include<GL/glut.h>
#include<iostream>
using namespace std;
int frame=0;
void Init()
{
  glClearColor(1,1,0.5,1); 
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,640,0,480);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
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

void wheel2()
{
 circle(120,35,15);
 glBegin(GL_LINES);
  glVertex2i(120,50);
  glVertex2i(120,20);
  glEnd();
  
  glBegin(GL_LINES);
  glVertex2i(105,35);
  glVertex2i(135,35);
  glEnd();
  
}
void wheel1()
{
  circle(60,35,15);
 
  
  glBegin(GL_LINES);
  glVertex2i(60,50);
  glVertex2i(60,20);
  glEnd();
  
   glBegin(GL_LINES);
  glVertex2i(45,35);
  glVertex2i(75,35);
  glEnd();
  
 
  
}
void car()
{
  glColor3f(0.5,0.5,0.5);
  glBegin(GL_QUADS);
  glVertex2i(50,50);
  glVertex2i(150,50);
  glVertex2i(150,100);
  glVertex2i(50,100);
  glEnd();
  
  glColor3f(0.5,0,0);
  glBegin(GL_QUADS);
  glVertex2i(75,100);
  glVertex2i(130,100);
  glVertex2i(120,125);
  glVertex2i(100,125);
  glEnd();
  
  glPushMatrix();
  glTranslated(60,35,0);
  glRotated(frame*30,0,0,1);
  glTranslated(-60,-35,0);
  wheel1();
  glPopMatrix();
  
  glPushMatrix();
  glTranslated(120,35,0);
  glRotated(frame*30,0,0,1);
  glTranslated(-120,-35,0);
  wheel2();
  glPopMatrix();

}
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.5,0,0);
glBegin(GL_TRIANGLES);
glVertex2i(0,200);
glVertex2i(160,400);
glVertex2i(320,200);
glEnd();
glBegin(GL_TRIANGLES);
glVertex2i(320,200);
glVertex2i(480,400);
glVertex2i(640,200);
glEnd();

glPushMatrix();
glTranslated(frame*50,0,0);
car();
glPopMatrix();
glFlush();

}
void doframe(int v)
{
  frame++;
  glutPostRedisplay();
  glutTimerFunc(500,doframe,0);

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
