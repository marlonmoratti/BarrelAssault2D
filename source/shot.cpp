#include <math.h>

#include "../include/shot.h"
#include "../include/shape.h"

#define MAX_DISTANCE 500

void Shot::draw() {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawCircle(radius, {1, 1, 1});
    glPopMatrix();
}

void Shot::move() {
    x += speed * cos(angle);
    y += speed * sin(angle);
}

Point Shot::getPosition() {
    return Point(x, y);
}

bool Shot::isValid() {
    return sqrt(pow(x - x0, 2) + pow(y - y0, 2)) < MAX_DISTANCE;
}
