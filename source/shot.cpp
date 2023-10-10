#include <math.h>

#include "../include/shot.h"
#include "../include/shape.h"

extern GLfloat gShotMaxDistance;

void Shot::draw() {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawCircle(radius, {1, 1, 1});
    glPopMatrix();
}

void Shot::move(GLdouble dt) {
    x += (speed * cos(angle)) * dt;
    y += (speed * sin(angle)) * dt;
}

Point Shot::getPosition() {
    return Point(x, y);
}

bool Shot::isValid() {
    return sqrt(pow(x - x0, 2) + pow(y - y0, 2)) < gShotMaxDistance;
}
