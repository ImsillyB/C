#include<stdio.h>
#include<gl/glut.h>
#include<math.h>
#define M_PI 3.14159

const float DegreesToRadians = M_PI / 180.0;

GLsizei winWidth = 500, winHeight = 500;

class point3
{
public:
	GLfloat x, y, z;
/*
public:
	point3 ()
	{
		x = y = z = 0.0;
	}

	void setCoords (GLfloat xCoord, GLfloat yCoord, GLfloat zCoord)
	{
		x = xCoord;
		y = yCoord;
		z = zCoord;
	}

	GLfloat getx () const
	{
		return x;
	}

	GLfloat gety () const
	{
		return y;
	}

	GLfloat getz () const
	{
		return z;
	}*/
};


void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
}

void displayFcn()
{
	glClear (GL_COLOR_BUFFER_BIT);

	gluLookAt (2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	int k = 0;
	//GLfloat quad_data[342];

	point3 quad_data[342];
	for (float phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		float phir = phi * DegreesToRadians;
		float phir20 = (phi + 20.0) * DegreesToRadians;

		for (float theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			float thetar = theta * DegreesToRadians;
			//quad_data[k].setCoords (sin(thetar) * cos(phir), cos(thetar) * cos(thetar), sin(phir));
			quad_data[k].x = sin(thetar) * cos(phir);
			quad_data[k].y = cos(thetar) * cos(phir);
			quad_data[k].z = sin(phir);
			k ++;
			//quad_data[k].setCoords (sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20));
			quad_data[k].x = sin(thetar) * cos(phir20);
			quad_data[k].y = cos(thetar) * cos(phir20);
			quad_data[k].z = sin(phir20);
			k ++;
		}
	}

	k = 0;
	//GLfloat strip_data[40];
	point3 strip_data[40];

	//strip_data[k].setCoords (0.0, 0.0, 1.0);
	strip_data[k].x = 0.0;
	strip_data[k].y = 0.0;
	strip_data[k].z = 1.0;
	k ++;

	float sin80 = sin(80.0 * DegreesToRadians);
	float cos80 = cos(80.0 * DegreesToRadians);

	for (float theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		float thetar = theta * DegreesToRadians;
		//strip_data[k].setCoords (sin(thetar) * cos80, cos(thetar) * cos80, sin80);
	    strip_data[k].x = sin(thetar) * cos80;
	    strip_data[k].y = cos(thetar) * cos80;
	    strip_data[k].z = sin80;
		k ++;
	}

	//strip_data[k].setCoords (0.0, 0.0, -1.0);
	strip_data[k].x = 0.0;
	strip_data[k].y = 0.0;
	strip_data[k].z = -1.0;
	k ++;

	for (float theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		float thetar = theta * DegreesToRadians;
		//strip_data[k].setCoords (sin(thetar) * cos80, cos(thetar) * cos80, sin80);
		strip_data[k].x =  sin(thetar) * cos80;
	    strip_data[k].y =  cos(thetar) * cos80;
	    strip_data[k].z = - sin80;
		k ++;
	}

	glColor3f (0.0, 0.4, 0.2);
	for (k = 0; k < 341; k ++)
	{
	    glBegin (GL_LINES);
	        glVertex3f(quad_data[k].x, quad_data[k].y, quad_data[k].z);
	        glVertex3f(quad_data[k+1].x, quad_data[k+1].y, quad_data[k+1].z);
		//glDrawArrays(GL_TRIANGLE_STRIP,quad_data[0], 342);
		//glDrawArrays(GL_TRIANGLE_FAN, strip_data[0], 40);
	    glEnd ();
	}

	for (k = 1; k < 19; k ++)
	{
	    glBegin (GL_LINES);
		    glVertex3f(strip_data[0].x, strip_data[0].y, strip_data[0].z);
	        glVertex3f(strip_data[k].x, strip_data[k].y, strip_data[k].z);
	        //glVertex3f(strip_data[k+1].x, strip_data[k+1].y, strip_data[k+1].z);
		//glDrawArrays(GL_TRIANGLE_STRIP,quad_data[0], 342);
		//glDrawArrays(GL_TRIANGLE_FAN, strip_data[0], 40);
	    glEnd ();
	}

	for (k = 21; k < 40; k ++)
	{
	    glBegin (GL_LINES);
		    glVertex3f(strip_data[20].x, strip_data[20].y, strip_data[20].z);
	        glVertex3f(strip_data[k].x, strip_data[k].y, strip_data[k].z);
	        //glVertex3f(strip_data[k+1].x, strip_data[k+1].y, strip_data[k+1].z);
		//glDrawArrays(GL_TRIANGLE_STRIP,quad_data[0], 342);
		//glDrawArrays(GL_TRIANGLE_FAN, strip_data[0], 40);
	    glEnd ();
	}
	
	glFlush ();
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth, newHeight);

	glMatrixMode (GL_PROJECTION);
	glOrtho (-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);

	glMatrixMode (GL_MODELVIEW);

	glClear (GL_COLOR_BUFFER_BIT);
}

void main(int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("看看能不能成功");

	init ();
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (winReshapeFcn);

	glutMainLoop ();
}