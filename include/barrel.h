#ifndef BARREL_H
#define BARREL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "shooter.h"

extern GLfloat gBarrelWidth, gBarrelHeight, gBarrelSpeed, gEnemyHeadRadius;

class Barrel {
    GLfloat x, y, width, height, speed;
    GLint lives;
    Shooter* shooter = nullptr;

    void drawBarrel(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    void drawLives(GLfloat x, GLfloat y, GLfloat scale, GLfloat lw);
public:
    Barrel(GLfloat x=0, GLfloat y=0, GLint lives=0, bool withEnemy=false) : x(x), y(y), lives(lives) {
        width = gBarrelWidth;
        height = gBarrelHeight;
        speed = gBarrelSpeed;

        if (withEnemy) shooter = new Shooter(
            x - width/10., y + height/2., gEnemyHeadRadius, {0.5, 0, 1}, withEnemy
        );
    };

    ~Barrel() { if (shooter) delete shooter; };

    void draw();
    void move(GLdouble dt);
    Shooter* getEnemy();
    bool isHit(GLfloat x, GLfloat y);
    bool decreaseLife(); // returns true if the barrel is destroyed
};

#endif
