#ifndef SHOT_H
#define SHOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <tuple>

#include "point.h"

using namespace std;

extern GLfloat gShotRadius, gShotSpeed;

class Shot {
    GLfloat radius, x0, y0, x, y, angle, speed;
    bool collision = false, enemy;
public:
    Shot(GLfloat x0, GLfloat y0, GLfloat angle, bool isEnemy) : x0(x0), y0(y0), angle(angle), enemy(isEnemy) {
        radius = gShotRadius;
        x = x0; y = y0;
        speed = gShotSpeed;
    };

    void draw();
    void move(GLdouble dt);
    void setCollision();
    tuple<Point, GLfloat> getDimensions();
    bool isValid();
    bool isEnemy();
};

#endif
