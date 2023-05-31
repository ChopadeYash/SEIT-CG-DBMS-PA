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
void windmill()
{
 glColor3f(0,0,1);
 
 glBegin(GL_QUADS);
 glVertex2i(0,15);
 glVertex2i(1,15); 
 glVertex2i(-25,200);
 glVertex2i(25,200);
 glEnd();
 
 glBegin(GL_QUADS);
 glVertex2i(0,-15);
 glVertex2i(1,-15); 
 glVertex2i(-25,-200);
 glVertex2i(25,-200);
 glEnd();
 
 glBegin(GL_QUADS);
 glVertex2i(-15,0);
 glVertex2i(-15,1); 
 glVertex2i(-200,25);
 glVertex2i(-200,-25);
 glEnd();

 glBegin(GL_QUADS);
 glVertex2i(15,0);
 glVertex2i(15,1); 
 glVertex2i(200,25);
 glVertex2i(200,-25);
 glEnd();
 
 


}



void display()
{
glClear(GL_COLOR_BUFFER_BIT);

glLineWidth(6);
glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex2i(0,-15);
glVertex2i(50,-50);
glEnd();

glBegin(GL_LINES);
glVertex2i(0,-15);
glVertex2i(-50,-50);
glEnd();

glLineWidth(5);
glColor3f(0.5,0.5,0.5);
glBegin(GL_QUADS);
glVertex2i(50,-50);
glVertex2i(-50,-50);
glVertex2i(-50,-400);
glVertex2i(50,-400);
glEnd();



circle(0,0,15);



glPushMatrix();
glRotated(frame*6,0,0,1);
windmill();
glPopMatrix();

glFlush();
}

void doframe(int v)
{
  frame++;
  glutPostRedisplay();
  glutTimerFunc(100,doframe,0);

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
