/*
	Roll No - S150058721
	
	Date - 26/04/2019

	Problem Statement - Write a program in openGL on linux platform to draw a polygon as shown at right and perform 
			    following 2D transformation on it : Keeping center as reference point,rotate by 45 deg. 
			    anti-clockwise.Fill it with different colors.
*/
#include<stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include<math.h>
#include<string.h>

#define SIZE 120
#define sqrSize 30

struct Point
{
	double x,y;
}P[16],P1[16],M;
//P array stores original co-ordinates and P1 stores changed co-ordinates
//M stores mid point 

//color stucture to store any color in RGB format
struct Color
{
	float r,g,b;
};

//function to set default properties
void init()
{
	//sets background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//set defalut color
	glColor3f(0.0, 0.0, 0.0);
	//sets default point size
	glPointSize(1.0);
	//sets the default matrix mode as GL_PROJECTION which provides 2D viewing space
	glMatrixMode(GL_PROJECTION);
	//sets the matrix with identity matrix
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);
}

//function to initialise the window parameters
void setWindow(char title[10])
{
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow(title);
	init();
}

//function to multiply 2 matrices and store the result in third matrix
void multMat(double matA[3][3],double (*res)[3],double op[3][3])
{
	double ans;
	int i,j,k;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{	
			ans = 0;
			for(k=0;k<3;k++)
			{
				ans += op[i][k]*matA[k][j];
			}
			res[i][j] = ans;
		}
	}

}

//function to rotate the give co-ordinates by an angle
void rotate(double matA[3][3],double (*res)[3],double angle)
{
	double op[3][3] = {{cos(angle),-sin(angle),0},{sin(angle),cos(angle),0},{0,0,1}};
	multMat(matA,res,op);
}

//function to translate the give co-ordinates by given parameters
void translate(double matA[3][3],double (*res)[3],double x,double y)
{
	double op[3][3] = {{1,0,x},{0,1,y},{0,0,1}};
	multMat(matA,res,op);
}

//function to fill color using flood fill
void floodFill(double x,double y,Color c1)
{
	Color c2;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&c2);//function return the value of current pixel
	//if the pixel is not equal to boundary pixel then color the pixel
	if(c2.r != 0 || c2.g != 0 || c2.b != 0)
	{
		glBegin(GL_POINTS);
			glColor3f(c1.r,c1.g,c1.b);
			glVertex2i(x,y);
		glEnd();
		floodFill(x+1,y,c1);
		floodFill(x-1,y,c1);
		floodFill(x,y+1,c1);
		floodFill(x,y-1,c1);				
	}
}

//function to display any string
void printString(float x,float y,char string[20])
{
	glRasterPos2f(x,y);//gives starting pos to display string
	int len = strlen(string);
	int i;
	for(i=0;i<len;i++)//displays one character at a time
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13,string[i]);
	}
}

//function is used to color the rotated chessboard
void colorChessboard()
{
	double res[3][3],res1[3][3],res2[3][3];
	Color c1;
	c1.r = 0;
	c1.g = 0;
	c1.b = 0;
	double matA[3][3] = {{(P[0].x+P[4].x)/2,(P[5].x+P[6].x)/2,(P[4].x+P[5].x)/2},
			     {(P[0].y+P[10].y)/2,(P[0].y+P[10].y)/2,(P[10].y+P[11].y)/2},
		            {1,1,1}};
	translate(matA,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	floodFill(res2[0][0],res2[1][0],c1);
	floodFill(res2[0][1],res2[1][1],c1);
	floodFill(res2[0][2],res2[1][2],c1);

	double matB[3][3] = {{(P[6].x+P[1].x)/2,(P[0].x+P[4].x)/2,(P[5].x+P[6].x)/2},
			     {(P[10].y+P[11].y)/2,(P[11].y+P[12].y)/2,(P[11].y+P[12].y)/2},
		            {1,1,1}};
	translate(matB,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	floodFill(res2[0][0],res2[1][0],c1);
	floodFill(res2[0][1],res2[1][1],c1);
	floodFill(res2[0][2],res2[1][2],c1);

	double matC[3][3] = {{(P[4].x+P[5].x)/2,(P[6].x+P[1].x)/2,1},
			     {(P[12].y+P[3].y)/2,(P[12].y+P[3].y)/2},
		            {1,1,1}};
	translate(matC,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	floodFill(res2[0][0],res2[1][0],c1);
	floodFill(res2[0][1],res2[1][1],c1);
}

//function is used to roatate the chess board
void rotateChessboard()
{

	double res[3][3],res1[3][3],res2[3][3];
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.5,0.5,0.5);
	printString(550,230,"X-AXIS");
	printString(270,450,"Y-AXIS");	
	
	glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex2i(320,0);
		glVertex2i(320,480);
	
		glVertex2i(0,240);
		glVertex2i(640,240);
	glEnd();	
	
	//for points 0,1,2
	double matA[3][3] = {{P[0].x,P[1].x,P[2].x},{P[0].y,P[1].y,P[2].y},{1,1,1}};
	translate(matA,res,-M.x,-M.y);//translate mid-point to origin
	rotate(res,res1,3.14159265/4);//rotate about origin
	translate(res1,res2,M.x,M.y);//translate back to default pos
	P1[0].x = res2[0][0];
	P1[0].y = res2[1][0];
	P1[1].x = res2[0][1];
	P1[1].y = res2[1][1];
	P1[2].x = res2[0][2];
	P1[2].y = res2[1][2];
	
	//for points 3,4,5
	double matB[3][3] = {{P[3].x,P[4].x,P[5].x},{P[3].y,P[4].y,P[5].y},{1,1,1}};
	translate(matB,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	P1[3].x = res2[0][0];
	P1[3].y = res2[1][0];
	P1[4].x = res2[0][1];
	P1[4].y = res2[1][1];
	P1[5].x = res2[0][2];
	P1[5].y = res2[1][2];
	
	//for points 6,7,8
	double matC[3][3] = {{P[6].x,P[7].x,P[8].x},{P[6].y,P[7].y,P[8].y},{1,1,1}};
	translate(matC,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	P1[6].x = res2[0][0];
	P1[6].y = res2[1][0];
	P1[7].x = res2[0][1];
	P1[7].y = res2[1][1];
	P1[8].x = res2[0][2];
	P1[8].y = res2[1][2];
	
	//for points 9,10,11
	double matD[3][3] = {{P[9].x,P[10].x,P[11].x},{P[9].y,P[10].y,P[11].y},{1,1,1}};
	translate(matD,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	P1[9].x = res2[0][0];
	P1[9].y = res2[1][0];
	P1[10].x = res2[0][1];
	P1[10].y = res2[1][1];
	P1[11].x = res2[0][2];
	P1[11].y = res2[1][2];

	//for points 12,13,14
	double matE[3][3] = {{P[12].x,P[13].x,P[14].x},{P[12].y,P[13].y,P[14].y},{1,1,1}};
	translate(matE,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	P1[12].x = res2[0][0];
	P1[12].y = res2[1][0];
	P1[13].x = res2[0][1];
	P1[13].y = res2[1][1];
	P1[14].x = res2[0][2];
	P1[14].y = res2[1][2];

	//for point 15
	double matF[3][3] = {{P[15].x,1,1},{P[15].y,1,1},{1,1,1}};
	translate(matF,res,-M.x,-M.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,M.x,M.y);
	P1[15].x = res2[0][0];
	P1[15].y = res2[1][0];
	
	//draw the chessboard with new rotated co-ordinates
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);
		glVertex2i(P1[0].x,P1[0].y);
		glVertex2i(P1[1].x,P1[1].y);
		glVertex2i(P1[2].x,P1[2].y);
		glVertex2i(P1[3].x,P1[3].y);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(0,0,0);

		glVertex2i(P1[4].x,P1[4].y);
		glVertex2i(P1[7].x,P1[7].y);
		
		glVertex2i(P1[5].x,P1[5].y);
		glVertex2i(P1[8].x,P1[8].y);

		glVertex2i(P1[6].x,P1[6].y);
		glVertex2i(P1[9].x,P1[9].y);

		glVertex2i(P1[10].x,P1[10].y);
		glVertex2i(P1[13].x,P1[13].y);

		glVertex2i(P1[11].x,P1[11].y);
		glVertex2i(P1[14].x,P1[14].y);

		glVertex2i(P1[12].x,P1[12].y);
		glVertex2i(P1[15].x,P1[15].y);
	glEnd();
	
	colorChessboard();//color the chessboard

	glColor3f(1,0,0);
	printString(M.x-95,M.y+110,"ROTATED BY 45 DEG ANTI-CLOCKWISE");
	glColor3f(0.5,0.5,0.5);	
	printString(320,240,"( 0 , 0 )");

	glFlush();
}

void drawChessboard()
{
	//initialize all the points of chessboard
	P[1].x = P[0].x+SIZE;
	P[1].y = P[0].y;

	P[2].x = P[0].x+SIZE;
	P[2].y = P[0].y+SIZE;

	P[3].x = P[0].x;
	P[3].y = P[0].y+SIZE;

	P[4].x = P[0].x+sqrSize;
	P[4].y = P[0].y;
	
	P[5].x = P[0].x+2*sqrSize;
	P[5].y = P[0].y;

	P[6].x = P[0].x+3*sqrSize;
	P[6].y = P[0].y;

	P[7].x = P[0].x+sqrSize;
	P[7].y = P[0].y+SIZE;
	
	P[8].x = P[0].x+2*sqrSize;
	P[8].y = P[0].y+SIZE;

	P[9].x = P[0].x+3*sqrSize;
	P[9].y = P[0].y+SIZE;

	
	P[10].x = P[0].x;
	P[10].y = P[0].y+sqrSize;
	
	P[11].x = P[0].x;
	P[11].y = P[0].y+2*sqrSize;

	P[12].x = P[0].x;
	P[12].y = P[0].y+3*sqrSize;

	
	P[13].x = P[0].x+SIZE;
	P[13].y = P[0].y+sqrSize;
	
	P[14].x = P[0].x+SIZE;
	P[14].y = P[0].y+2*sqrSize;

	P[15].x = P[0].x+SIZE;
	P[15].y = P[0].y+3*sqrSize;	
		
	M.x = (P[5].x);
	M.y = (P[11].y);

	//draw the initial chessboard
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);
		glVertex2i(P[0].x,P[0].y);
		glVertex2i(P[1].x,P[1].y);
		glVertex2i(P[2].x,P[2].y);
		glVertex2i(P[3].x,P[3].y);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);

		glVertex2i(P[4].x,P[4].y);
		glVertex2i(P[7].x,P[7].y);
		
		glVertex2i(P[5].x,P[5].y);
		glVertex2i(P[8].x,P[8].y);

		glVertex2i(P[6].x,P[6].y);
		glVertex2i(P[9].x,P[9].y);

		glVertex2i(P[10].x,P[10].y);
		glVertex2i(P[13].x,P[13].y);

		glVertex2i(P[11].x,P[11].y);
		glVertex2i(P[14].x,P[14].y);

		glVertex2i(P[12].x,P[12].y);
		glVertex2i(P[15].x,P[15].y);
	glEnd();
	//color the chessboard
	Color c1;
	c1.r = 0;
	c1.g = 0;
	c1.b = 0;		
	floodFill((P[0].x+P[4].x)/2,(P[0].y+P[10].y)/2,c1);
	floodFill((P[5].x+P[6].x)/2,(P[0].y+P[10].y)/2,c1);
	floodFill((P[4].x+P[5].x)/2,(P[10].y+P[11].y)/2,c1);
	floodFill((P[6].x+P[1].x)/2,(P[10].y+P[11].y)/2,c1);
	floodFill((P[0].x+P[4].x)/2,(P[11].y+P[12].y)/2,c1);
	floodFill((P[5].x+P[6].x)/2,(P[11].y+P[12].y)/2,c1);
	floodFill((P[4].x+P[5].x)/2,(P[12].y+P[3].y)/2,c1);
	floodFill((P[6].x+P[1].x)/2,(P[12].y+P[3].y)/2,c1);

	glColor3f(1,0,0);
	printString(M.x-35,M.y+90,"CHESSBOARD");
	glColor3f(0.5,0.5,0.5);
	printString(320,240,"( 0 , 0 )");
	
	
}

void keyListener(unsigned char key,int x,int y)
{
	if(key == 'c' || key == 'C')//if 'c' or 'C' is pressed then roatate
	{
		rotateChessboard();
	}
	else if(key == 'r' || key == 'R')//if 'r' or 'R' is pressed then reset 
	{
		glutPostRedisplay();//calls the display function
	}

}

void display()
{	
	//function to clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.5,0.5,0.5);
	printString(550,230,"X-AXIS");
	printString(270,450,"Y-AXIS");

	//display axis
	glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex2i(320,0);
		glVertex2i(320,480);
	
		glVertex2i(0,240);
		glVertex2i(640,240);
	glEnd();	

	drawChessboard();	

	glFlush();
}
int main(int argc, char** argv)
{
	printf("\n*****************************\n");
	printf("\nENTER STARTING POINT : \n");
	printf("X : ");
	scanf("%lf",&P[0].x);
	P[0].x+=320;
	printf("Y : ");
	scanf("%lf",&P[0].y);
	P[0].y+=240;
	printf("\n*****************************\n");
	glutInit(&argc, argv);//initialize the library functions 
    	glutInitDisplayMode(GLUT_SINGLE);//set the display mode with one buffer
	setWindow("CHESSBOARD");//create a window with given title
    	glutDisplayFunc(display);
	glutKeyboardFunc(keyListener);
    	glutMainLoop();//keep on rendering the window    
    	return 0;
}
