#include "../include/shape.h"
#include "../include/point.h"

void Shape::drawRectangle(GLfloat width, GLfloat height, tuple<GLfloat, GLfloat, GLfloat> color) {
    auto [R, G, B] = color;
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
        glVertex3f(-width/2.,    0.0, 0.0);
        glVertex3f( width/2.,    0.0, 0.0);
        glVertex3f( width/2., height, 0.0);
        glVertex3f(-width/2., height, 0.0);
    glEnd();
}

void Shape::drawCircle(GLfloat radius, tuple<GLfloat, GLfloat, GLfloat> color) {
    auto [R, G, B] = color;
    glColor3f(R, G, B);

    glPushMatrix();
        GLfloat angleBetweenPoints = 10;
        GLint nPoints = 360 / angleBetweenPoints;
        Point p(radius, 0);

        glBegin(GL_POLYGON);
        for(int i = 0; i < nPoints; i++) {
            glVertex3f(p.x, p.y, 0);
            p.rotate(angleBetweenPoints);
        }
        glEnd();
    glPopMatrix();
}

void Shape::drawLine(Point p1, Point p2, GLfloat lw, tuple<GLfloat, GLfloat, GLfloat> color) {
    auto [R, G, B] = color;
    glColor3f(R, G, B);

    glLineWidth(lw);
    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
}
