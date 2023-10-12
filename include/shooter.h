#ifndef SHOOTER_H
#define SHOOTER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <tuple>

#include "point.h"
#include "shot.h"

using namespace std;

class Shooter {
    GLfloat x, y, headRadius, aimingAngle = 0, footAngle = 0;
    tuple<GLfloat, GLfloat, GLfloat> color;
    bool isEnemy;

    tuple<GLfloat, GLfloat> getFootDimensions();
    tuple<GLfloat, GLfloat> getGunDimensions();
    void drawBody(GLfloat x, GLfloat y, GLfloat radius);
    void drawFoot(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle);
    void drawGun(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle);
    Point getGunAxisPoint();
public:
    Shooter(GLfloat x=0, GLfloat y=0, GLfloat headRadius=0, tuple<GLfloat, GLfloat, GLfloat> color={0, 0, 0}, bool isEnemy=false)
            : x(x), y(y), headRadius(headRadius), color(color), isEnemy(isEnemy) {};

    void draw();
    void move(GLfloat dx, GLfloat dy);
    void adjustAimingAngle(GLfloat dt);
    void setAimingAngleTo(GLfloat x, GLfloat y);
    tuple<Point, GLfloat> getDimensions();
    tuple<Point, Point> getHitBox();
    bool checkCollision(tuple<Point, GLfloat> circle);
    Shot* shoot();
};

#endif
