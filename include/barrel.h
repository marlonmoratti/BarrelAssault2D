#ifndef BARREL_H
#define BARREL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "shooter.h"

extern GLfloat gBarrelWidth, gBarrelHeight, gBarrelSpeed, gEnemyHeadRadius;

class Barrel {
    GLfloat x, y, width, height, lives, speed;
    Shooter* shooter = nullptr;

    void drawBarrel(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    void drawLives(GLfloat x, GLfloat y, GLfloat scale);
    void drawShooter(GLfloat x, GLfloat y);
public:
    Barrel(GLfloat x, GLfloat y, GLint lives, bool enemy) : x(x), y(y), lives(lives) {
        width = gBarrelWidth;
        height = gBarrelHeight;
        speed = gBarrelSpeed;

        if (enemy) shooter = new Shooter(
            x - width/6.,
            y + height/2.,
            gEnemyHeadRadius
        );
    };

    ~Barrel() { if (shooter) delete shooter; };

    void draw();
};

#endif
