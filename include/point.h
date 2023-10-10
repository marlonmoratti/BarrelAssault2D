#ifndef POINT_H
#define	POINT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Point {
public:
    GLfloat x, y;
    Point(GLfloat x=0, GLfloat y=0) : x(x), y(y) {};

    void translate(GLfloat dx, GLfloat dy);
    void rotate(GLfloat angle); // angle in degrees
};

#endif
