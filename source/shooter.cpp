#include <math.h>

#include "../include/shooter.h"
#include "../include/shape.h"

void Shooter::drawBody(GLfloat x, GLfloat y, GLfloat radius) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawCircle(radius, color);
    glPopMatrix();
}

void Shooter::drawFoot(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(angle, 1, 0, 0);
        Shape::drawRectangle(width, height, {0, 0, 0});
    glPopMatrix();
}

void Shooter::drawGun(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(angle, 0, 0, 1);
        Shape::drawRectangle(width, height, {1, 0, 0});
    glPopMatrix();
}

void Shooter::draw() {
    GLfloat footWidth = headRadius/2, footHeight = 2*headRadius;
    drawFoot(x - (headRadius - footWidth), y, footWidth, -footHeight, -footAngle);
    drawFoot(x + (headRadius - footWidth), y, footWidth, footHeight, footAngle);

    drawBody(x, y, headRadius);

    GLfloat gunWidth = 2*headRadius/3., gunHeight = 4*headRadius;
    drawGun(x + (headRadius + gunWidth/2.), y - headRadius, gunWidth, gunHeight, aimingAngle);
}

void Shooter::move(GLfloat dx, GLfloat dy) {
    x += dx; y += dy;
    footAngle += (dy/headRadius) * 180/M_PI;
}

void Shooter::adjustAimingAngle(GLfloat dt) {
    GLfloat angle = aimingAngle + dt;
    if (abs(angle) <= 30) {
        aimingAngle = angle;
    }
}

tuple<Point, Point> Shooter::getHitBox() {
    return {
        Point(x - headRadius, y - headRadius),
        Point(x + headRadius, y + headRadius)
    };
}

Shot* Shooter::shoot() {
    Point p1, p2;
    GLfloat gunWidth = 2*headRadius/3., gunHeight = 4*headRadius;

    p2.translate(0, gunHeight);
    p2.rotate(aimingAngle);
    p2.translate(x + (headRadius + gunWidth/2.), y - headRadius);

    p1.rotate(aimingAngle);
    p1.translate(x + (headRadius + gunWidth/2.), y - headRadius);

    GLfloat x0 = p2.x - p1.x, y0 = p2.y - p1.y,
        norm = sqrt(pow(x0, 2) + pow(y0, 2));
    x0 /= norm; y0 /= norm;

    return new Shot(p2.x, p2.y, atan2(y0, x0));
}
