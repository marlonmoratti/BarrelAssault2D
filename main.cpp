#include <iostream>
#include <GL/glut.h>

#include "tinyxml2/tinyxml2.hpp"
#include "include/arena.h"
#include "include/shooter.h"

using namespace std;
using namespace tinyxml2;

// Window dimensions
GLint gWidth, gHeight;

Arena gArena;

Shooter gPlayer;
GLfloat gPlayerHeadRadius;
GLfloat gPlayerSpeed;

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

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    gArena.draw();
    gPlayer.draw();

    glutSwapBuffers();
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
    gWidth = stoi(arena->Attribute("largura"));
    gHeight = stoi(arena->Attribute("altura"));

    XMLElement* jogador = rootElement->FirstChildElement("jogador");
    gPlayerHeadRadius = stoi(jogador->Attribute("raioCabeca"));
    gPlayerSpeed = stoi(jogador->Attribute("velocidade"));

    // XMLElement* inimigo = rootElement->FirstChildElement("inimigo");
    // XMLElement* barril = rootElement->FirstChildElement("barril");
    // XMLElement* tiro = rootElement->FirstChildElement("tiro");
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    loadConfiguration();

    gArena = Arena(gWidth, gHeight);
    gPlayer = Shooter(0.0, -gHeight/4., gPlayerHeadRadius, {0, 1, 0});

    // auto [p1, p2] = gArena.getBoundaries();
    // cout << "p1.x: " << p1.x << " p1.y: " << p1.y << "\n";
    // cout << "p2.x: " << p2.x << " p2.y: " << p2.y << "\n";

    // Create the window.
    glutInitWindowSize(gWidth, gHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trabalho 2D");

    // Define callbacks.
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMouseFunc([](int button, int state, int x, int y) {
        cout << "x: " << x << " y: " << y << "\n";
    });

    init();

    glutMainLoop();    
    return 0;
}
