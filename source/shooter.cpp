#include <math.h>
#include <algorithm>

#include "../include/shooter.h"
#include "../include/shape.h"

using namespace std;

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

Point Shooter::getGunAxisPoint() {
    auto [gunWidth, gunHeight] = getGunDimensions();
    return Point(x + (headRadius + gunWidth/2.), y - headRadius);
}

void Shooter::draw() {
    glPushMatrix();
        if (isEnemy) {
            glTranslatef(x, y, 0);
            glRotatef(180, 0, 0, 1);
            glTranslatef(-x, -y, 0);
        }

        auto [footWidth, footHeight] = getFootDimensions();
        drawFoot(x - (headRadius - footWidth), y, footWidth, -footHeight, -footAngle);
        drawFoot(x + (headRadius - footWidth), y, footWidth, footHeight, footAngle);

        drawBody(x, y, headRadius);

        auto [gunWidth, gunHeight] = getGunDimensions();
        Point gunAxisPoint = getGunAxisPoint();
        drawGun(gunAxisPoint.x, gunAxisPoint.y, gunWidth, gunHeight, aimingAngle);
    glPopMatrix();
}

void Shooter::move(GLfloat dx, GLfloat dy) {
    x += dx; y += dy;
    footAngle += (dy/headRadius) * 180/M_PI;
}

void Shooter::adjustAimingAngle(GLfloat dt) {
    GLfloat angle = aimingAngle + ((isEnemy) ? -dt : dt);
    if (abs(angle) <= 30) {
        aimingAngle = angle;
    }
}

void Shooter::setAimingAngleTo(GLfloat x, GLfloat y) {
    Point p = getGunAxisPoint();
    if (isEnemy) {
        p.translate(-this->x, -this->y);
        p.rotate(180);
        p.translate(this->x, this->y);
    }

    GLfloat xv = x - p.x, yv = y - p.y, norm = sqrt(pow(xv, 2) + pow(yv, 2));

    if (!norm) return;

    xv /= norm; yv /= norm;

    GLfloat angle = -(atan2(yv, xv) * 180/M_PI) - 90;
    this->aimingAngle = (abs(angle) > 90) ? 0 : -clamp((double) angle, -30., 30.);
}

tuple<Point, GLfloat> Shooter::getDimensions() {
    Point center(x, y);
    return { center, headRadius };
}

tuple<Point, Point> Shooter::getHitBox() {
    return {
        Point(x - headRadius, y - headRadius),
        Point(x + headRadius, y + headRadius)
    };
}

bool Shooter::checkCollision(tuple<Point, GLfloat> circle) {
    auto [circleCenter, circleRadius] = circle;
    GLfloat distance = sqrt(pow(x - circleCenter.x, 2) + pow(y - circleCenter.y, 2));
    return distance <= (headRadius + circleRadius);
}

Shot* Shooter::shoot() {
    Point p1, p2;
    auto [gunWidth, gunHeight] = getGunDimensions();

    p2.translate(0, gunHeight);
    p2.rotate(aimingAngle);
    p2.translate(x + (headRadius + gunWidth/2.), y - headRadius);

    p1.rotate(aimingAngle);
    p1.translate(x + (headRadius + gunWidth/2.), y - headRadius);

    if (isEnemy) {
        p2.translate(-x, -y);
        p2.rotate(180);
        p2.translate(x, y);

        p1.translate(-x, -y);
        p1.rotate(180);
        p1.translate(x, y);
    }

    GLfloat xv = p2.x - p1.x, yv = p2.y - p1.y,
        norm = sqrt(pow(xv, 2) + pow(yv, 2));
    xv /= norm; yv /= norm;

    return new Shot(p2.x, p2.y, atan2(yv, xv));
}
