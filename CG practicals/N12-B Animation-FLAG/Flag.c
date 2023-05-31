//Seat Number:S150058722
//Probelm Statement: Write a program in OpenGL on Linux Platform to animate  any one scene

#include<GL/glut.h>//including header file GL/glut
#include<iostream>//including iostream
#include<math.h>//including header file for mathematical operations
#include<stdio.h>//standard input output header file
using namespace std;

#define pi 3.14 
int framenumber=0;//initialising frame number

void drawdisk(double rad)//function to draw a disk
{
	int i;
	glBegin(GL_POLYGON);
	for(i=0;i<32;++i)
	{
		GLdouble angle= 2*pi*i/32;
		glVertex2f(rad*cos(angle),rad*sin(angle));
	}
	glEnd();
	glFlush();
}

void drawpod() //function to draw a podium 
{
	glColor3f(0.0, 0.0, 0.0);//color black
	glBegin(GL_POLYGON);//drawing a polygon
	glVertex2f(1,-1);//giving co ordinates
        glVertex2f(1,0);
        glVertex2f(6,0);
        glVertex2f(6,-1);
    glEnd();//end


    glFlush();
}

void drawflag()
{
	glColor3f(0.0, 1.0, 0.0);//green color
	glBegin(GL_POLYGON);//drawing a polygon
	glVertex2f(0.0f,0.0f);//giving co ordinates
        glVertex2f(1.5f,0.0f);
        glVertex2f(1.5f,0.5f);
        glVertex2f(0.0f,0.5f);
    glEnd();//end


    
    
    	glColor3f(1.0, 1.0, 1.0);//white color
	glBegin(GL_POLYGON);//drawing a polygon
	glVertex2f(0.0f,0.5f);//giving co ordinates
        glVertex2f(1.5f,0.5f);
        glVertex2f(1.5f,1.0f);
        glVertex2f(0.0f,1.0f);
    
	glEnd();//end

   
    
        glColor3f(1.0, 0.5, 0.5);//orange color
	glBegin(GL_POLYGON);//drawing a polygon
	glVertex2f(0.0f,1.0f);//giving co ordinates
        glVertex2f(1.5f,1.0f);
        glVertex2f(1.5f,1.5f);
        glVertex2f(0,1.5f);
    glEnd();//end
}

void drawchakra()//function to draw ashoka chakra
{	
	int i;
	glColor3f(0.0,0.0,1.0);//blue color
	drawdisk(0.5);//drawing disk of radius 0.5
	glColor3f(1.0,1.0,1.0);//white color
	drawdisk(0.4);//drawing disk of radius 0.4
	glColor3f(0.0,0.0,1.0);//blue color
	for(i=0;i<24;++i)//printing 24 lines inside the chakra
	{
		glRotatef(360/24,0,0,1);//rotating the lines
		glBegin(GL_LINES);//command to draw lines
		glVertex2f(0.0f,0.0f);//giving co ordinates
		glVertex2f(0.5f,0.0f);
		
		glEnd();//end
	}
	
	
}

void drawsun()//function for drawing sun
{
	int i;
	glColor3f(1.0,1.0,0.0);//Yellow Color for sun
	drawdisk(1);//drawing disk of radius 1
	for(i=0;i<15;++i)//displayinfg 15 lines
	{
		glRotatef(360/15,0,0,1);//rotating the lines
		glBegin(GL_LINES);//command to draw a line between two points
		glVertex2f(0.0f,0.0f);//first vertex
		glVertex2f(1.5f,0.0f);//second vertex
		glEnd();//end
		
		
	}
	
}

void draw()//main render function 
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();//load identity matrix
	
	drawpod();		 //drawing podium
	
	glColor3f(0.0,0.0,0.0);	 //balck color
	glLineWidth(50);	 //width of the pole
	glBegin(GL_LINES);
	glVertex2f(3.0,0.0);    //giving co ordinates of pole
	glVertex2f(3.0,3.5);
	glEnd();//end
	glLineWidth(1);
	
	glPushMatrix();
	glTranslated(3.02f,2.1f*(framenumber%300)/300,0);//performing translation operation on the flag
	drawflag();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(3.77f,0.75+2.1f*(framenumber%300)/300,0);//performing translation operation on chakra 
	glScaled(0.5,0.5,0);  //performing scaling operation on the chakra
	drawchakra();         
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(6,3,0); //performing translation operation on sun
	glRotated(0.7f*framenumber,0,0,1);//performing rotation operation on sun 
 	glScaled(0.5,0.5,1); //performing scaling operation on sun
	drawsun();
	glPopMatrix();
	
	glutSwapBuffers();//to avoid error between the two screens
	
}

void doframe(int v)
{
	framenumber++;//incrementing the frame number
	glutPostRedisplay();
	glutTimerFunc(30,doframe,0);//using timer function
}

void init()//function for initialization
{
	glClearColor(0.5, 0.5, 0.8, 0.0);//giving background color
	
	glMatrixMode(GL_PROJECTION);//opening matrix in projection mode
	glLoadIdentity();//load identity matrix
	glOrtho(0,7,-1,4,-1,1);
	glMatrixMode(GL_MODELVIEW);//opening in model view moed
	
}

int main(int argc,char **argv)//main function
{
    glutInit(&argc, argv);//intializing 
    glutInitDisplayMode(GLUT_DOUBLE);//specifying display mode 
    glutInitWindowSize(1366,768);//giving window size
    glutInitWindowPosition(0,0);//giving window position
    glutCreateWindow("Flag");//giving name "Flag" to create window
    init();//calling init function
    glutDisplayFunc(draw);//calling draw 
    glutTimerFunc(200,doframe,0);//timer function to reapeat the animation
    glutMainLoop();    
    return 0; //end of main
	
}
    
    
