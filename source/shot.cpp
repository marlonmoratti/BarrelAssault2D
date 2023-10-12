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

void Shot::setCollision() {
    collision = true;
}

tuple<Point, GLfloat> Shot::getDimensions() {
    Point center(x, y);
    return { center, radius };
}

bool Shot::isValid() {
    return !collision && sqrt(pow(x - x0, 2) + pow(y - y0, 2)) < gShotMaxDistance;
}
