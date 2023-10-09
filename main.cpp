#include <iostream>
#include <GL/glut.h>

#include "tinyxml2/tinyxml2.hpp"
#include "include/arena.h"
#include "include/shooter.h"
#include "include/shot.h"

using namespace std;
using namespace tinyxml2;

#define AIMING_SENSITIVITY 0.2

int keyStatus[256] = { 0 };

// Window dimensions
GLint gWidth, gHeight;

Arena gArena;

Shooter gPlayer;
GLfloat gPlayerHeadRadius;
GLfloat gPlayerSpeed;

Shot* shot = nullptr;
GLfloat gShotRadius = 10, gShotSpeed = 50;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-(gWidth/2), (gWidth/2), -(gHeight/2), (gHeight/2), -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void movePlayer(GLdouble dt) {
    auto [pLeftBottom, pRightTop] = gPlayer.getHitBox();
    auto [aLeftBottom, aRightTop] = gArena.getBoundaries();

    GLfloat dx = 0, dy = 0, wallDistance = 0, inc = (gPlayerSpeed * dt);
    if(keyStatus[(int)('a')]) {
        wallDistance = abs(aLeftBottom.x - pLeftBottom.x);
        dx -= (pLeftBottom.x - inc > aLeftBottom.x) ? inc : wallDistance;
    }

    if(keyStatus[(int)('d')]) {
        wallDistance = abs(aRightTop.x - pRightTop.x);
        dx += (pRightTop.x + inc < aRightTop.x) ? inc : wallDistance;
    }

    if(keyStatus[(int)('s')]) {
        wallDistance = abs(aLeftBottom.y - pLeftBottom.y);
        dy -= (pLeftBottom.y - inc > aLeftBottom.y) ? inc : wallDistance;
    }

    if(keyStatus[(int)('w')]) {
        wallDistance = abs(aRightTop.y - pRightTop.y);
        dy += (pRightTop.y + inc < aRightTop.y) ? inc : wallDistance;
    }
    gPlayer.move(dx, dy);
}

void idle() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    movePlayer(timeDiference);

    if(shot){
        shot->move();

        //Trata colisao
        // if (alvo.Atingido(tiro)){
        //     alvo.Recria(rand()%500 - 250, 200);
        // }

        if (!shot->isValid()){ 
            delete shot;
            shot = NULL;
        }
    }

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    gArena.draw();
    gPlayer.draw();

    if (shot) shot->draw();

    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 1;
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    static int previousPosition = x;
    int currentPosition, delta;

    currentPosition = x;
    delta = currentPosition - previousPosition;
    previousPosition = x;

    gPlayer.adjustAimingAngle(-delta * AIMING_SENSITIVITY);
    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == 0 && state == 0 && shot == nullptr) {
        shot = gPlayer.shoot();
    }
}

void loadConfiguration() {
    XMLDocument doc;
    if (doc.LoadFile("configuracoes.xml") != XML_SUCCESS) {
        printf("Erro ao carregar o arquivo de configurações.\n");
        exit(1);
    }

    XMLElement *rootElement = doc.RootElement();
    if (rootElement == nullptr) {
        printf("Elemento 'root' não encontrado.\n");
        exit(1);
    }

    XMLElement* arena = rootElement->FirstChildElement("arena");
    gWidth = stof(arena->Attribute("largura"));
    gHeight = stof(arena->Attribute("altura"));

    XMLElement* jogador = rootElement->FirstChildElement("jogador");
    gPlayerHeadRadius = stof(jogador->Attribute("raioCabeca"));
    gPlayerSpeed = stof(jogador->Attribute("velocidade"));

    // XMLElement* inimigo = rootElement->FirstChildElement("inimigo");
    // XMLElement* barril = rootElement->FirstChildElement("barril");
    // XMLElement* tiro = rootElement->FirstChildElement("tiro");

    gArena = Arena(gWidth, gHeight);
    gPlayer = Shooter(0.0, -gHeight/4., gPlayerHeadRadius, {0, 1, 0});

    // auto [p1, p2] = gArena.getBoundaries();
    // cout << "p1.x: " << p1.x << " p1.y: " << p1.y << "\n";
    // cout << "p2.x: " << p2.x << " p2.y: " << p2.y << "\n";
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    loadConfiguration();

    // Create the window.
    glutInitWindowSize(gWidth, gHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trabalho 2D");

    // Define callbacks.
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);

    init();

    glutMainLoop();    
    return 0;
}
