#include <stdio.h>

#include "../include/barrel.h"
#include "../include/shape.h"

void Barrel::drawBarrel(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawRectangle(width, height, {1, 0.5, 0});
    glPopMatrix();
}

void Barrel::drawLives(GLfloat x, GLfloat y, GLfloat scale) {
    static char str[100];
    glColor3f(0.0, 0.0, 0.0);
    sprintf(str, "%d", lives);

    glLineWidth(3);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(0.25, 0.25, 1.0);

        for (int i = 0; str[i]; i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN , str[i]);
        }
    glPopMatrix();

}

void Barrel::draw() {
    drawBarrel(x, y, width, height);
    drawLives(x + width/4., y + height/3., 0);
    if (shooter) shooter->draw();
};

void Barrel::move(GLdouble dt) {
    y += -(speed * dt);
    if (shooter) shooter->move(0, -(speed * dt));
}

Shooter* Barrel::getEnemy() {
    return shooter;
}

bool Barrel::isHit(GLfloat x, GLfloat y) {
    Point leftBottom(this->x - width/2., this->y), rightTop(this->x + width/2., this->y + height);
    return x >= leftBottom.x
        && x <= rightTop.x
        && y >= leftBottom.y
        && y <= rightTop.y;
}

bool Barrel::decreaseLife() {
    return !(--lives);
}
