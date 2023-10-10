#ifndef SHOT_H
#define SHOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "point.h"

extern GLfloat gShotRadius, gShotSpeed;

class Shot {
    GLfloat radius, x0, y0, x, y, angle, speed;
public:
    Shot(GLfloat x0, GLfloat y0, GLfloat angle) : x0(x0), y0(y0), angle(angle) {
        radius = gShotRadius;
        x = x0; y = y0;
        speed = gShotSpeed;
    };

    void draw();
    void move(GLdouble dt);
    Point getPosition();
    bool isValid();
};

#endif
