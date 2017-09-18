#include <stdio.h>
#include <gl/glut.h>
#include <math.h>
#include <string.h>

class wcPt2D 
{
public:
	GLfloat x, y;
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

const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;

inline GLint inside (GLint code)
{
	return GLint (!code);
}

inline GLint reject (GLint code1, GLint code2)
{
	return GLint (code1 & code2);
}

inline GLint accept (GLint code1, GLint code2)
{
	return GLint (code1 | code2);
}

GLubyte encode (wcPt2D pt, wcPt2D winMin , wcPt2D winMax)
{
	GLubyte code = 0x00;

	if (pt.x < winMin.x)
		code = code | winLeftBitCode;
	if (pt.x > winMax.x)
		code = code | winRightBitCode;
	if (pt.y < winMin.y)
		code = code | winBottomBitCode;
	if (pt.y > winMax.y)
		code = code | winTopBitCode;
	return (code);
}

void swapPts (wcPt2D * p1, wcPt2D * p2)
{
	wcPt2D tmp;

	tmp = *p1, *p1 = *p2, *p2 = tmp;
}

void swapCodes (GLubyte * c1, GLubyte *c2)
{
	GLubyte tmp;

	tmp = *c1, *c1 = *c2, *c2 = tmp;
}

void lintClipCohSuth (wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
	GLubyte code1, code2;
	GLint done = false, plotLine = false;
	GLfloat m;

	while (!done)
	{
		code1 = encode (p1, winMin, winMax);
		code2 = encode (p2, winMin, winMax);
		if (accept (code1, code2))
		{
			done = true;
			plotLine = true;
		}
		else
			if(reject (code1, code2))
				done = true;
			else
			{
				if (inside (code1))
				{
					swapPts (&p1, &p2);
					swapCodes (&code1, &code2);
				}
				if (p2.x != p1.x)
					m = (p2.y - p1.y) / (p2.x - p1.x);
				if (code1 & winLeftBitCode)
				{
					p1.y += (winMin.x - p1.x) * m;
					p1.x = winMin.x;
				}
				else
					if (code1 & winRightBitCode)
					{
						p1.y += (winMax.x - p1.x) * m;
						p1.x = winMax.x;
					}
					else
						if (code1 & winBottomBitCode)
						{
							if (p2.x != p1.x)
								p1.x += (winMin.y - p1.y) / m;
							p1.y = winMin.y;
						}
						else
							if (code1 & winTopBitCode)
							{
								if (p2.x !=p1.x)
									p1.x += (winMax.y - p1.y) / m;
								p1.y = winMax.y;
							}
			}
	}
	if (plotLine)
		lineBres (round (p1.x), round (p1.y), round (p2.x), round (p2.y));
}

void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	wcPt2D winMin = {50, 50};
	wcPt2D winMax = {100, 100};
	wcPt2D p1 = {125, 134};
	wcPt2D p2 = {12, 45};
	glColor3f (0.0, 0.4, 0.2);
	lintClipCohSuth(winMin, winMax, p1, p2);

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

