#ifndef SHOOTER_H
#define SHOOTER_H

#include <GL/gl.h>
#include <tuple>

#include "point.h"
#include "shot.h"

using namespace std;

class Shooter {
    GLfloat x, y, headRadius, aimingAngle = 0, footAngle = 0;
    tuple<GLfloat, GLfloat, GLfloat> color;

    tuple<GLfloat, GLfloat> getFootDimensions();
    tuple<GLfloat, GLfloat> getGunDimensions();
    void drawBody(GLfloat x, GLfloat y, GLfloat radius);
    void drawFoot(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle);
    void drawGun(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle);
public:
    Shooter(GLfloat x=0, GLfloat y=0, GLfloat headRadius=0, tuple<GLfloat, GLfloat, GLfloat> color={0, 0, 0})
            : x(x), y(y), headRadius(headRadius), color(color) {};

    void draw();
    void move(GLfloat dx, GLfloat dy);
    void adjustAimingAngle(GLfloat dt);
    tuple<Point, Point> getHitBox();
    Shot* shoot();
};

#endif
