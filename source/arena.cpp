#include "../include/arena.h"
#include "../include/shape.h"
#include "../include/colors.h"

void Arena::draw() {
    glPushMatrix();
        glTranslatef(0, -height/2., 0);
        Shape::drawRectangle(width, height, BLUE);
    glPopMatrix();

    Shape::drawLine(Point(-width/2., 0), Point(width/2., 0), lineWidth, BLACK);
}

tuple<Point, Point> Arena::getBoundaries() {
    return {
        Point(-width/2., -height/2.),
        Point( width/2., -lineWidth/2.),
    };
}
