#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>

class wcPt3D
{
public :
	GLfloat x, y, z;
	
};

const GLdouble pi =3.14159;

GLsizei winWidth = 600, winHeight = 600;

GLfloat xx = 100.0, yy = 50.0, zz = 50.0;
GLfloat xref = 50.0, yref = 50.0, zref = 0.0;
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;

GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

GLfloat dnear = 25.0, dfar = 125.0;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	gluLookAt (xx, yy, zz, xref, yref, zref, Vx, Vy, Vx);

	glMatrixMode (GL_PROJECTION);
	glFrustum (xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void rotate3D (wcPt3D p1, wcPt3D p2, GLfloat thetaAngle)
{
	float vx = (p2.x - p1.x);
	float vy = (p2.y - p1.y);
	float vz = (p2.z - p1.z);

	glTranslatef (p1.x, p1.y, p1.z);
	glRotatef (thetaAngle, vx, vy, vz);
	glTranslatef (-p1.x, -p1.y, -p1.z);
}

void scale3D (GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
	glTranslatef (fixedPt.x, fixedPt.y, fixedPt.z);
	glScalef (sx, sy, sz);
	glTranslatef (-fixedPt.x, -fixedPt.y, -fixedPt.z);
}



void displayFcn (void)
{
	wcPt3D p1 = {10, 10, 10};
	wcPt3D p2 = {20, 20, 20};
	wcPt3D fixedPt = {0.5, 0.2, 0.6};

	glMatrixMode (GL_MODELVIEW);

	GLfloat tx = 0.0, ty = 10.0, tz = 50.0;
	GLfloat sx = 0.5, sy = 0.5, sz = 0.5;
	GLdouble theta = pi / 2.0;

	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f (0.0, 0.0, 1.0);
	glRecti (50, 100, 200, 150);

	glPushMatrix();
	glColor3f (1.0, 0.0, 0.0);

	glTranslatef (tx, ty, tz);
	glRecti (50, 100, 200, 150);

	glPopMatrix ();
	glPushMatrix ();

	scale3D(sx, sy, sz, fixedPt);
	glRecti (50, 100, 200, 150);

	glPopMatrix ();
	rotate3D (p1, p2, theta);
	glRecti (50, 100, 200, 150);

	glFlush();
}

void winshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
void main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("wuwuwuwuwu");

	init();
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (winshapeFcn);

	glutMainLoop ();
}
