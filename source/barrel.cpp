#include "../include/barrel.h"
#include "../include/shape.h"

void Barrel::drawBarrel(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        Shape::drawRectangle(width, height, {1, 0.5, 0});
    glPopMatrix();
}

void Barrel::drawLives(GLfloat x, GLfloat y, GLfloat scale) {

}

void Barrel::drawShooter(GLfloat x, GLfloat y) {

}

#include <iostream>

void Barrel::draw() {
    drawBarrel(x, y, width, height);
    std::cout << x << " " << y << " " << width << " " << height << "\n";
};
