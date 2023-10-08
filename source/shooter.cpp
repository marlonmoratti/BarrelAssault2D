#include "../include/shooter.h"
#include "../include/shape.h"

void Shooter::drawBody(GLfloat x, GLfloat y, GLfloat radius) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawCircle(radius, color);
    glPopMatrix();
}

void Shooter::drawFoot(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    glPushMatrix();
        glTranslatef(x, y, 0);
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
    drawFoot(x - (headRadius - footWidth), y - headRadius, footWidth, footHeight);
    drawFoot(x + (headRadius - footWidth), y - headRadius, footWidth, footHeight);

    drawBody(x, y, headRadius);

    GLfloat gunWidth = 2*headRadius/3., gunHeight = 4*headRadius;
    drawGun(x + (headRadius + gunWidth/2.), y - headRadius, gunWidth, gunHeight, aimingAngle);
}
