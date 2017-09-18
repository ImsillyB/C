#include <gl/glut.h>

class wcPt2D
{
public:
	GLfloat x, y;
};

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-100.0, 100.0, -100.0, 100.0);

	glMatrixMode (GL_MODELVIEW);
}

void triangle (wcPt2D *verts)
{
	GLint k;

	glBegin (GL_TRIANGLES);
	for ( k = 0; k < 3; k ++)
		glVertex2f (verts [k].x, verts [k].y);
	glEnd ();
}
void displayFcn (void)
{
	wcPt2D verts [3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0}};

	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f (0.0, 0.0, 1.0);
	glViewport (0, 0, 300, 300);
	triangle (verts);

	glColor3f (1.0, 0.0, 0.0);
	glViewport (300, 0, 300, 300);
	glRotatef (90.0, 0.0, 0.0, 1.0);
	triangle (verts);

	glFlush ();
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (600, 300);
	glutCreateWindow ("Split_screen Example");

	init ();
	glutDisplayFunc (displayFcn);

	glutMainLoop();
}