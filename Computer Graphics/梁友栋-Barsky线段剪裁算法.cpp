#include<math.h>
#include<gl/glut.h>
#include<stdio.h>
#include<string.h>

class wcPt2D
{
private:
	GLfloat x, y;

public:
	void wcPt3D()
	{
		x = y = 0.0;
	}

	void setCoords (GLfloat xCoord, GLfloat yCoord)
	{
		x = xCoord;
		y = yCoord;
	}

	GLfloat getx () const
	{
		return x;
	}

	GLfloat gety () const
	{
		return y;
	}
};

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
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

inline GLint round (const GLfloat a)
{
	return GLint (a + 0.5);
}

GLint clipTest (GLfloat p, GLfloat q, GLfloat *u1, GLfloat *u2)
{
	GLfloat r;
	GLint returnValue = true;

	if (p < 0.0)
	{
		r = q / p;
		if (r > *u2)
			returnValue = false;
		else
			if (r > *u1)
				*u1 = r;
	}
	else
		if (p > 0.0)
		{
			r = q / p;
			if (r < *u1)
				returnValue = false;
			else if (r < *u2)
				*u2 = r;
		}
		else
		if (q < 0.0)
			returnValue = false;

	return (returnValue);
}

void lineClipLiangBarsk (wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
	GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx() - p1.getx (), dy;

	if (clipTest (-dx, p1.getx() - winMin.getx(), &u1, &u2))
		if (clipTest (dx, winMax.getx() - p1.getx(), &u1, &u2))
		{
			dy = p2.gety () - p1.gety ();
			if (clipTest (-dy, p1.gety() - winMin.gety(), &u1, &u2))
				if (clipTest (dy, winMax.gety() - p1.gety(), &u1, &u2))
				{
					if (u2 < 1.0)
					{
						p2.setCoords (p1.getx() + u2 * dx, p1.gety() + u2 * dy);
					}
					if (u1 > 1.0)
					{
						p1.setCoords (p1.getx() + u1 * dx, p1.gety() + u1 * dy);
					}

					//glBegin (GL_LINES);
					//glVertex2i (round (p1.getx()), round ( p1.gety()));
					//glVertex2i (round( p2.getx()), round ( p2.gety()));
					//glEnd ();
					lineBres (round (p1.getx()), round ( p1.gety()), round( p2.getx()), round ( p2.gety()));
				}
		}

}

void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	wcPt2D winMin, winMax, p1, p2;
	winMin.setCoords (50, 50);
	winMax.setCoords (100, 100);
	p1.setCoords (20, 20);
	p2.setCoords (134,120);
	glColor3f (0.0, 0.4, 0.2);
	lineClipLiangBarsk (winMin, winMax, p1, p2);
	//lineBres (round (p1.getx()), round ( p1.gety()), round( p2.getx()), round ( p2.gety()));
	/*glBegin (GL_LINES);
	glVertex2i (round (p1.getx()), round ( p1.gety()));			
	glVertex2i (round( p2.getx()), round ( p2.gety()));
	glEnd ();*/

	glFlush ();
}

void main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (400, 300);
	glutCreateWindow ("²Ã¼ô´°¿Ú");

	init ();
	glutDisplayFunc (displayFcn);
	glutMainLoop ();
}

