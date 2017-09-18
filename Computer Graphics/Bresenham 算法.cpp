#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

void init ( void )
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode ( GL_PROJECTION );
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void setPixel (GLint xCoord, GLint yCoord)
{
	glPointSize (2.0);
	glBegin ( GL_POINTS );
	glVertex2i ( xCoord, yCoord );
	glEnd ();
}


void lineBres (float x0 , float y0 , float xEnd , float yEnd)
{
	int dx = fabsl ( xEnd - x0 ), dy = fabsl( yEnd - y0 );
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * ( dy - dx );
	int x, y;
	if ( x0 > xEnd )
	{
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else
	{
		x = x0;
		y = y0;
	}
	setPixel( x, y );
	while( x < xEnd )
	{
		x++;
		if( p < 0 )
			p += twoDy;
		else
		{
			y ++;
			p += twoDyMinusDx;
		}
		setPixel ( x, y );

	}
}
void lineSegment ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glColor3f ( 0.0, 0.4, 0.2 );
	 lineBres ( 34, 30, 54, 32 );
	glFlush ();
}
void main ( int argc, char**argv )
{
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_SINGLE|GLUT_RGB );
	glutInitWindowPosition ( 50, 100 );
	glutInitWindowSize ( 800, 600 );
	glutCreateWindow ("Bresenham");
	init ();
	glutDisplayFunc ( lineSegment );
	glutMainLoop ();
}


