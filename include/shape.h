#ifndef SHAPE_H
#define SHAPE_H

#include <GL/gl.h>
#include <tuple>

#include "point.h"

using namespace std;

class Shape {
public:
    static void drawRectangle(GLfloat width, GLfloat height, tuple<GLfloat, GLfloat, GLfloat> color);
    static void drawCircle(GLfloat radius, tuple<GLfloat, GLfloat, GLfloat> color);
    static void drawLine(Point p1, Point p2, GLfloat lw, tuple<GLfloat, GLfloat, GLfloat> color);
};

#endif
