#ifndef ARENA_H
#define ARENA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <tuple>

#include "point.h"

using namespace std;

class Arena {
    GLfloat width, height, lineWidth = 5;
public:
    Arena(GLfloat width=0, GLfloat height=0) : width(width), height(height) {};

    void draw();
    tuple<Point, Point> getBoundaries();
};

#endif
