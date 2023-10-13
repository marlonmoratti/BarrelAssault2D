#include <stdio.h>
#include <math.h>

#include "../include/barrel.h"
#include "../include/shape.h"

void Barrel::drawBarrel(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawRectangle(width, height, {1, 0.5, 0});
    glPopMatrix();
}

void Barrel::drawLives(GLfloat x, GLfloat y, GLfloat scale, GLfloat lw) {
    static char str[100];
    sprintf(str, "%d", lives);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(scale, scale, 1.0);
        Shape::drawText(str, lw, {0, 0, 0});
    glPopMatrix();
}

void Barrel::draw() {
    drawBarrel(x, y, width, height);
    drawLives(x + width/4., y + height/3., height/75. * 0.25, height/75. * 3);
    if (shooter) shooter->draw();
};

void Barrel::move(GLdouble dt) {
    y += -(speed * dt);
    if (shooter) shooter->move(0, -(speed * dt));
}

Shooter* Barrel::getEnemy() {
    return shooter;
}

bool Barrel::checkCollision(tuple<Point, GLfloat> circle) {
    Point barrelCenter = Point(x, y + height/2.),
          barrelLeftBottom = Point(x - width/2., y),
          barrelRightTop = Point(x + width/2., y + height);

    auto [circleCenter, circleRadius] = circle;

    GLfloat nearestX = max(barrelLeftBottom.x, min(circleCenter.x, barrelRightTop.x)),
            nearestY = max(barrelLeftBottom.y, min(circleCenter.y, barrelRightTop.y));
    GLfloat distance = sqrt(pow(nearestX - circleCenter.x, 2) + pow(nearestY - circleCenter.y, 2));

    // return circleCenter.x >= barrelLeftBottom.x
    //     && circleCenter.x <= barrelRightTop.x
    //     && circleCenter.y >= barrelLeftBottom.y
    //     && circleCenter.y <= barrelRightTop.y;

    return distance <= circleRadius;
}

bool Barrel::decreaseLife() {
    return !(--lives);
}
