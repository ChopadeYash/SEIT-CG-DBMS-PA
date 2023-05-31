/*
S150058677
PROBLEM STATEMENT:: IMPLEMENT CIRCLE PATTERN USING MIDPOINT CIRCLE DRAWING ALGORITHM.
*/
#include <GL/glut.h>    //HEADER FILES
#include <stdio.h>
#include <iostream>
#include <math.h>
# define PI 3.14235f    
using namespace std;
      
float cx,cy,radius,a,b,c,d;   
int flag=0,f1=0;
float m;
void Init()       //INITIALIZATION
{
      glClearColor(1.0,1.0,1.0,0.0);
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(1.0,0.0,0.0);
}      
void circle(float a,float b,float r)      //MIDPOINT CIRCLE DRAWING ALGORITHM
{
      int pk,xk,yk;
      glBegin(GL_POINTS);
            glVertex2f(a,b+r);      //PLOT INITIAL POINT(0,R)
      glEnd();
      glFlush();
      pk=1-r;           //INITIAL VALUE OF PARAMETER
      xk=0;yk=r;
      
      while(xk<=yk)     //TILL XK<YK
      {
             xk=xk+1;
            if(pk<0)
            {     
              
                  pk=pk+2*xk+1;     //MIDPOINT IS INSIDE CIRCLE
                  yk=yk;
            }
            else
            {
                                      //MIDPOINT IS OUTSIDE CIRCLE
                  pk=pk+2*(xk-yk)+1;
                  yk=yk-1;
            }
            glBegin(GL_POINTS);
                  glVertex2f(a+xk,b+yk);        //PLOT SYMMETRY POINTS
                  glVertex2f(a+xk,b-yk);
                  glVertex2f(a-xk,b+yk);
                  glVertex2f(a-xk,b-yk);                   
                 glVertex2f(a+yk,b+xk);
                 glVertex2f(a+yk,b-xk);
                 glVertex2f(a-yk,b+xk);
                 glVertex2f(a-yk,b-xk); 
            glEnd();
            glFlush();        
            
         
      }
      
}                       
void display()    //DISPLAY FUNCTION
{
      int j=0;
      circle(cx,cy,radius);         //INNER RING
      circle(cx,cy,radius-10);      //OUTER RING
      while(j<=90)      
      {
            circle((cx+(radius+5)*cos(PI/180*j)),(cy+(radius+5)*sin(PI/180*j)),5);  //FOR UPPER RIGHT PART OF OUTER BANGLES
            j=j+6;
      }    
          j=0;   
      while(j<=90)
      {
            circle((cx-(radius+5)*cos((PI/180)*j)),(cy-(radius+5)*sin((PI/180)*j)),5);   //FOR LOWER LEFT PART OF OUTER BANGLES 
            j=j+6;
      }
      j=0;   
      while(j<=90)
      {
            circle((cx-(radius+5)*cos((PI/180)*j)),(cy+(radius+5)*sin((PI/180)*j)),5);    //FOR UPPER LEFT PART OF OUTER BANGLES
            j=j+6;
      }          
      j=0;   
      while(j<=90)
      {
            circle((cx+(radius+5)*cos((PI/180)*j)),(cy-(radius+5)*sin((PI/180)*j)),5);   //FOR LOWER RIGHT PART OF OUTER BANGLES 
            j=j+6;
      } 
      cout<<"\tCOMPLETE";
      
}      
void display1()
{
      int j=0;
      if(flag==1)
      {
            circle(a,b,m);
            circle(a,b,m-10);
          while(j<=90)
          {
            circle((a+(m+5)*cos(PI/180*j)),(b+(m+5)*sin(PI/180*j)),5);        //FOR UPPER RIGHT PART OF OUTER BANGLES
            j=j+6;
          }    
          j=0;   
            while(j<=90)
            {
                  circle((a-(m+5)*cos((PI/180)*j)),(b-(m+5)*sin((PI/180)*j)),5);    //FOR UPPER LEFT PART OF OUTER BANGLES
                  j=j+6;
            }
            j=0;   
            while(j<=90)
            {
                  circle((a-(m+5)*cos((PI/180)*j)),(b+(m+5)*sin((PI/180)*j)),5);   //FOR UPPER LEFT PART OF OUTER BANGLES 
                  j=j+6;
            }          
            j=0;   
            while(j<=90)
            {
                  circle((a+(m+5)*cos((PI/180)*j)),(b-(m+5)*sin((PI/180)*j)),5);     //FOR LOWER RIGHT PART OF OUTER BANGLES
                  j=j+6;
            } 
            cout<<"\tCOMPLETE";
            
      } 
      else
      {
            glClearColor(1.0,1.0,1.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_LINES);
            glVertex2f(10,10);
            glVertex2f(11,10);
            glEnd();
            glFlush();
            
      }
      
                 
}      

void myMouse(int button,int state,int x,int y)
{
      
      switch(button)
      {
            case GLUT_LEFT_BUTTON:                          //left click
                                    if(state==GLUT_DOWN)
                                    {
                                          if(f1==0)
                                          {
                                                a=x;b=480-y;
                                                f1=1;
                                          }     
                                    }
                                    else
                                          return;
                                    break;
            case GLUT_RIGHT_BUTTON:                         //right click
                                    if(state==GLUT_DOWN)
                                    {
                                          c=x;d=480-y;
                                          m=sqrt((c-a)*(c-a) +(d-b)*(d-b));
                                          flag=1;
                                          Init();
                                          display1();
                                    }
                                    break;
     }
                                                                                                                        
}                                                                                         
int main(int argc,char **argv)
{     
      int ch;
      cout<<"\nCIRCLE";
      cout<<"\nMENU\n1.ENTER CIRCLE PARAMETERS FROM TERMINAL \n2.GIVE CIRCLE PARAMETERS FROM MOUSE\n3.EXIT\nENTER UR CHOICE::";
      cin>>ch;
      switch(ch)
      {
            case 1:
                        cout<<"\nENTER THE CENTER OF CIRCLE\nX-Co-ordinate:: ";
                        cin>>cx;
                        cout<<"\nY Co-ordinate::";
                        cin>>cy;
                        cout<<"\nENTER THE RADIUS::";
                        cin>>radius;
                        glutInit(&argc,argv);         //initialize glut library
                        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);          //give the mode of display
                        glutInitWindowPosition(0,0);        //position
                        glutInitWindowSize(640,480);        //size
                        glutCreateWindow("BANGLE");         //create window
                        Init();
                        gluOrtho2D(0,640,0,480);
                        glutDisplayFunc(display);
                        glutMainLoop();
                        break;
           case 2:
                        glutInit(&argc,argv);
                        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
                        glutInitWindowPosition(450,500);
                        glutInitWindowSize(640,480);
                        glutCreateWindow("BANGLE");
                        Init();
                        gluOrtho2D(0,640,0,480);
                        glutDisplayFunc(display1);             
                        glutMouseFunc(myMouse);
                        glutMainLoop();
                        break;
          case 3:
                        break;
       }
       return 0;
       
}                                       
