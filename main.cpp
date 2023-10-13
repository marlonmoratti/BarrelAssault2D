#include <iostream>
#include <cctype>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <list>

#include "tinyxml2/tinyxml2.hpp"
#include "include/arena.h"
#include "include/shooter.h"
#include "include/shot.h"
#include "include/barrel.h"
#include "include/game.h"

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

list<Shot*> gShots;
GLfloat gShotRadius;
GLfloat gShotSpeed;
GLfloat gShotMaxDistance;

list<Barrel*> gBarrels;
GLfloat gBarrelWidth;
GLfloat gBarrelHeight;
GLfloat gBarrelSpeed;
GLint gBarrelLives;
GLint gScoreToWin;
GLfloat gEnemyHeadRadius;
GLfloat gShotsPerSecond;
GLfloat gDistanceBetweenBarrels;

Game *gGame = nullptr;

void spawnBarrel(GLdouble dt) {
    if (gGame->isVictory() || gGame->isDefeat()) return;

    static GLfloat distance = 0;

    distance += gBarrelSpeed * dt;
    if (!gBarrels.empty() && distance < (gBarrelHeight + gDistanceBetweenBarrels)) return;

    GLfloat x = (rand() % ((int) (gWidth - gBarrelWidth)/2)) * (-1 * (rand() % 2));
    GLfloat y = gHeight/2. - gBarrelHeight;

    gBarrels.push_back(
        new Barrel(x, y, gBarrelLives, (rand() % 2))
    );

    distance = 0;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-(gWidth/2), (gWidth/2), -(gHeight/2), (gHeight/2), -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    gGame->movePlayer(gPlayerSpeed * timeDiference);
    gGame->moveShot(timeDiference);
    gGame->moveBarrel(timeDiference);
    gGame->enemyShooting(timeDiference, gShotsPerSecond);

    spawnBarrel(timeDiference);

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gGame->isDefeat()) {
        gGame->drawDefeat();

        glutSwapBuffers();
        return;
    }

    if (gGame->isVictory()) {
        gGame->drawVictory();

        glutSwapBuffers();
        return;
    }

    gArena.draw(); gPlayer.draw();

    for (auto shot : gShots) {
        shot->draw();
    }

    for (auto barrel : gBarrels) {
        barrel->draw();
    }

    gGame->drawScoreBoard();
    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
    keyStatus[tolower(key)] = 1;
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    keyStatus[tolower(key)] = 0;
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
    if (button == 0 && state == 0) {
        gShots.push_back(gPlayer.shoot());
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

    XMLElement* tiro = rootElement->FirstChildElement("tiro");
    gShotRadius = stof(tiro->Attribute("raio"));
    gShotSpeed = stof(tiro->Attribute("velocidade"));

    XMLElement* barril = rootElement->FirstChildElement("barril");
    gBarrelWidth = stof(barril->Attribute("largura"));
    gBarrelHeight = stof(barril->Attribute("altura"));
    gBarrelSpeed = stof(barril->Attribute("velocidade"));
    gBarrelLives = stoi(barril->Attribute("numeroTiros"));
    gScoreToWin = stoi(barril->Attribute("nParaGanhar"));
    gDistanceBetweenBarrels = stof(barril->Attribute("distanciaEntre"));

    XMLElement* inimigo = rootElement->FirstChildElement("inimigo");
    gEnemyHeadRadius = stof(inimigo->Attribute("raioCabeca"));
    gShotsPerSecond = stof(inimigo->Attribute("tirosPorSegundo"));

    gArena = Arena(gWidth, gHeight);
    gPlayer = Shooter(0.0, -gHeight/4., gPlayerHeadRadius, {0, 1, 0});
    gShotMaxDistance = max(gWidth, gHeight);

    gGame = new Game(gArena, gPlayer, keyStatus, gShots, gBarrels, gScoreToWin);
}

int main(int argc, char *argv[]) {
    srand(0);

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
