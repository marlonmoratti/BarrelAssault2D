#ifndef BARREL_H
#define BARREL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <tuple>

#include "shooter.h"
#include "colors.h"

using namespace std;

extern GLfloat gBarrelWidth, gBarrelHeight, gBarrelSpeed, gEnemyHeadRadius;

class Barrel {
    GLfloat x0, y0, x, y, width, height, speed;
    GLint lives;
    Shooter* shooter = nullptr;

    void drawBarrel(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    void drawLives(GLfloat x, GLfloat y, GLfloat scale, GLfloat lw);
public:
    Barrel(GLfloat x0=0, GLfloat y0=0, GLint lives=0, bool withEnemy=false) : x0(x0), y0(y0), lives(lives) {
        x = x0; y = y0;
        width = gBarrelWidth;
        height = gBarrelHeight;
        speed = gBarrelSpeed;

        if (withEnemy) shooter = new Shooter(
            x - width/10., y + height/2., gEnemyHeadRadius, withEnemy, {PURPLE, PURPLE_B}
        );
    };

    ~Barrel() { if (shooter) delete shooter; };

    void draw();
    void move(GLdouble dt);
    Shooter* getEnemy();
    bool checkCollision(tuple<Point, GLfloat> circle);
    bool decreaseLife(); // returns true if the barrel is destroyed
    bool isValid();
};

#endif
