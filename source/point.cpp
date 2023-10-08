#include <math.h>

#include "../include/point.h"

void Point::translate(GLfloat dx, GLfloat dy) {
    x += dx; y += dy;
}

void Point::rotate(GLfloat angle) {
    angle *= (M_PI/180); // degrees to radians

    GLfloat xHat = x*cos(angle) - y*sin(angle),
            yHat = x*sin(angle) + y*cos(angle);

    x = xHat; y = yHat;
}
