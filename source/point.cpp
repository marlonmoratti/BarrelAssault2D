#include <math.h>

#include "../include/point.h"

void Point::translate(GLfloat dx, GLfloat dy) {
    x += dx; y += dy;
}

void Point::rotate(GLfloat angle) {
    angle *= (M_PI/180); // degrees to radians

    GLfloat x = this->x*cos(angle) - this->y*sin(angle),
            y = this->x*sin(angle) + this->y*cos(angle);

    this->x = x; this->y = y;
}
