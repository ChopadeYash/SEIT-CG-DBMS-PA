#include <GL/freeglut.h>
#include <GL/gl.h>

int frame=3777;
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);	//black colour of window
	gluOrtho2D(-150,500,-150,500);
}

void bresenhem(float xc,float yc,float r)
{
	float x=0,y=r,p=1-r;
	glBegin(GL_POINTS);
	while(x<=y)
	{
		x++;
		glVertex2f(xc-x,yc+y);	//print point
		glVertex2f(xc-x,yc-y);	//print point
		glVertex2f(xc+x,yc+y);	//print point
		glVertex2f(xc+x,yc-y);	//print point
		glVertex2f(xc+y,yc-x);	//print point
		glVertex2f(xc+y,yc+x);	//print point
		glVertex2f(xc-y,yc-x);	//print point
		glVertex2f(xc-y,yc+x);	//print point
		if(p<0)
			p+=2*x+1;	//add 2x+1 in p
		else
		{
			y--;	//decrement y
			p+=2*x-2*y+1;	//add 2x-2y+1 in p
		}
		
	}
	glEnd();
	glFlush();
}

void dda(float x1,float y1,float x2,float y2)
{
	float dx,dy,steps,xinc,yinc;
	int k=0;
	dx=abs(x2-x1);	//calculate dx
	dy=abs(y2-y1); //calculate dy
	if(dx>dy)
		steps=dx;	//steps  has value of dx
	else
		steps=dy;	//steps  has value of dy
	
	xinc=dx/steps;  //if steps is equal to dx then xinc=1 
	yinc=dy/steps; //if steps is equal to dy then yinc=1 
	glBegin(GL_POINTS);
	for(k=0;k<=steps;k++)
	{
		glVertex2d(x1,y1);
		x1=xinc+x1;	//increment x1 by xinc
		y1=yinc+y1;	//increment y1 by yinc
	}
	glEnd();
	glFlush();
}
int sign(float x)
{
	if(x<0)
	return -1;
	if(x==0)
	return 0;
	return 1;
}
void bres(float x1,float y1,float x2,float y2)
{
	float dx,dy,k=1,p,x,y;
	int ex=0;
	
	int s1=sign((x2-x1));
	int s2=sign((y2-y1));
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dy>dx)
	{
		float temp;
		temp=dx;
		dx=dy;
		dy=temp;
		ex=1;
	}
	p=2*dy-dx;
	glBegin(GL_POINTS);
	x=x1;
	y=y1;
	while(k<=dx)
	{
		glVertex2f(x,y);
		if(p>=0)
		{
			if(ex==1)
			x=x+s1;
			else
			y=y+s2;
			p-=2*dx;
		}
		if(ex==1)
			y=y+s2;
		else
			x=x+s1;
		p+=2*dy;
		k++;
	}
	glEnd();
	glFlush();	
}
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);	//yellow colour of truck
	
	bres(15,220,15,280);	//for line drawing using bresenhem
	//dda(15,220,15,280);	//for line drawing
	dda(15,280,45,360);	//for line drawing using dda
	dda(45,360,85,360);	//for line drawing using dda
	dda(85,360,85,380);	//for line drawing using dda
	dda(85,380,95,380);	//for line drawing using dda
	dda(95,220,95,380);	//for line drawing using dda
	dda(100,380,400,380);	//for line drawing using dda
	dda(400,220,400,380);	//for line drawing using dda
	dda(100,220,400,220);	//for line drawing using dda
	dda(100,220,100,380);	//for line drawing using dda
	dda(15,220,95,220);	//for line drawing using dda
	dda(35,301,87,301);	//for line drawing using dda
	dda(87,259,87,301);	//for line drawing using dda
	dda(35,259,87,259);	//for line drawing using dda
	dda(35,259,35,301);	//for line drawing using dda
	dda(45,291,77,291);	//for line drawing using dda
	dda(77,269,77,291);	//for line drawing using dda
	dda(45,269,77,269);	//for line drawing using dda
	dda(45,269,45,291);	//for line drawing using dda
	
	
	bresenhem(55,200,10);	//for inner circle of tyer
	bresenhem(55,200,20);	//for outer circle of tyer
	bresenhem(150,200,10);	//for inner circle of tyer
	bresenhem(150,200,20);	//for outer circle of tyer
	bresenhem(335,200,10);	//for inner circle of tyer
	bresenhem(335,200,20);	//for outer circle of tyer
	
}


void display()
{
	glPushMatrix();
	glTranslatef((frame%500),0,0);	
	render();
	glPopMatrix();
}
void doframe(int v)
{
	frame--;
	glutPostRedisplay();
	glutTimerFunc(20,doframe,0);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE );
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("line");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(40,doframe,0);
	glutMainLoop();
}

	
