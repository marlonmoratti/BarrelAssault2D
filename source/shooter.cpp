#include <math.h>

#include "../include/shooter.h"
#include "../include/shape.h"

tuple<GLfloat, GLfloat> Shooter::getFootDimensions() {
    GLfloat width = headRadius/2, height = 2*headRadius;
    return { width, height };
}

tuple<GLfloat, GLfloat> Shooter::getGunDimensions() {
    GLfloat width = 2*headRadius/3., height = 4*headRadius;
    return { width, height };
}

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
    auto [footWidth, footHeight] = getFootDimensions();
    drawFoot(x - (headRadius - footWidth), y, footWidth, -footHeight, -footAngle);
    drawFoot(x + (headRadius - footWidth), y, footWidth, footHeight, footAngle);

    drawBody(x, y, headRadius);

    auto [gunWidth, gunHeight] = getGunDimensions();
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
    auto [gunWidth, gunHeight] = getGunDimensions();

    p2.translate(0, gunHeight);
    p2.rotate(aimingAngle);
    p2.translate(x + (headRadius + gunWidth/2.), y - headRadius);

    p1.rotate(aimingAngle);
    p1.translate(x + (headRadius + gunWidth/2.), y - headRadius);

    GLfloat xv = p2.x - p1.x, yv = p2.y - p1.y,
        norm = sqrt(pow(xv, 2) + pow(yv, 2));
    xv /= norm; yv /= norm;

    return new Shot(p2.x, p2.y, atan2(yv, xv));
}
