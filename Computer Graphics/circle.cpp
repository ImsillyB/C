#include <GL/glut.h>

class screenPt
{
private:
    GLint x, y;

public:
    screenPt()
    {
        x = y = 0;
    }
    void setCoords (GLint xCoordValue, GLint yCoordValue)
    {
        x = xCoordValue;
        y = yCoordValue;
    }

    GLint getx () const
    {
        return x;
    }

    GLint gety () const
    {
        return y;
    }
    void incrementx ()
    {
        x++;
    }
    void decrementy ()
    {
        y--;
    }
};

void setPixel (GLint xCoord, GLint yCoord)
{
    glBegin ( GL_POINTS );
    glVertex2i ( xCoord, yCoord );
    glEnd ();
}

void circleMidpoind ( GLint xc, GLint yc, GLint radius)
{
    screenPt circPt;
    
    GLint p = 1 - radius;

    circPt.setCoords (0, radius);

    void circlePlotPoints (GLint, GLint, screenPt);
    circlePlotPoints (xc, yc, circPt);

    while (circPt.getx () < circPt.gety ())
    {
        circPt.incrementx ();
        if (p < 0)
            p += 2 * circPt.getx () + 1;
        else
        {
            circPt.decrementy ();
            p += 2 * ( circPt.getx () - circPt.gety ()) + 1;
        }
        circlePlotPoints (xc, yc, circPt);
    }
}

void circlePlotPoints (GLint xc, GLint yc, screenPt circPt)
{
        setPixel (xc + circPt.getx (), yc + circPt.gety ());
        setPixel (xc - circPt.getx (), yc + circPt.gety ());
        setPixel (xc + circPt.getx (), yc - circPt.gety ());
        setPixel (xc - circPt.getx (), yc - circPt.gety ());
        setPixel (xc + circPt.gety (), yc + circPt.getx ());
        setPixel (xc - circPt.gety (), yc + circPt.getx ());
        setPixel (xc + circPt.gety (), yc - circPt.getx ());
        setPixel (xc - circPt.gety (), yc - circPt.getx ());
}

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
  
    glColor3f (0.0, 0.4, 0.2);
    circleMidpoind ( 50, 50, 25);
    glFlush ();
}

void main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (400, 300);
    glutCreateWindow ("circle");

    init ();
    glutDisplayFunc (lineSegment);
    glutMainLoop ();
}
