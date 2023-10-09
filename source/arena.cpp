#include "../include/arena.h"
#include "../include/shape.h"

void Arena::draw() {
    glPushMatrix();
        glTranslatef(0, -height/2., 0);
        Shape::drawRectangle(width, height, {0, 0, 1});
    glPopMatrix();

    Shape::drawLine(Point(-width/2., 0), Point(width/2., 0), lineWidth, {1, 1, 1});
}

tuple<Point, Point> Arena::getBoundaries() {
    return {
        Point(-width/2., -height/2.),
        Point( width/2., -lineWidth/2.),
    };
}
