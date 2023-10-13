#include <stdio.h>

#include "../include/game.h"
#include "../include/shape.h"

void Game::freeGameMemory() {
    for (auto shot : shots) {
        delete shot;
    }
    shots.clear();

    for (auto barrel : barrels) {
        delete barrel;
    }
    barrels.clear();
}

bool Game::isVictory() {
    return victory;
}

bool Game::isDefeat() {
    return defeat;
}

void Game::movePlayer(GLfloat inc) {
    if (isVictory() || isDefeat()) return;

    auto [pLeftBottom, pRightTop] = player.getHitBox();
    auto [aLeftBottom, aRightTop] = arena.getBoundaries();

    GLfloat dx = 0, dy = 0, wallDistance = 0;
    if(keyStatus[(int)('a')]) {
        wallDistance = abs(aLeftBottom.x - pLeftBottom.x);
        dx -= min(inc, wallDistance);
    }

    if(keyStatus[(int)('d')]) {
        wallDistance = abs(aRightTop.x - pRightTop.x);
        dx += min(inc, wallDistance);
    }

    if(keyStatus[(int)('s')]) {
        wallDistance = abs(aLeftBottom.y - pLeftBottom.y);
        dy -= min(inc, wallDistance);
    }

    if(keyStatus[(int)('w')]) {
        wallDistance = abs(aRightTop.y - pRightTop.y);
        dy += min(inc, wallDistance);
    }
    player.move(dx, dy);
}

void Game::moveShot(GLdouble dt) {
    if (isVictory() || isDefeat()) return;

    for (auto shot : shots) {
        shot->move(dt);
        tuple<Point, GLfloat> shotDimensions = shot->getDimensions();

        barrels.remove_if([shot, shotDimensions, this](auto barrel) {
            if (!shot->isEnemy() && barrel->checkCollision(shotDimensions)) {

                shot->setCollision();

                if (barrel->decreaseLife()) {
                    if (++score == scoreToWin) victory = true;

                    delete barrel;
                    return true;
                }
            }

            return false;
        });

        if (isVictory()) {
            freeGameMemory();
            return;
        }

        if (shot->isEnemy() && player.checkCollision(shotDimensions)) {
            shot->setCollision();

            defeat = true;
            freeGameMemory();
            return;
        }
    }

    shots.remove_if([](auto shot) {
        bool isValid = shot->isValid();
        if (!isValid) {
            delete shot;
        }
        return !isValid;
    });
}

void Game::moveBarrel(GLdouble dt) {
    if (isVictory() || isDefeat()) return;

    for (auto barrel : barrels) {
        barrel->move(dt);

        auto [playerCenter, playerRadius] = player.getDimensions();
        if (auto enemy = barrel->getEnemy()) {
            enemy->setAimingAngleTo(playerCenter.x, playerCenter.y);
        }

        if (barrel->checkCollision({ playerCenter, playerRadius })) {
            defeat = true;
            freeGameMemory();
            return;
        }
    }
}

void Game::enemyShooting(GLdouble dt, GLfloat shotsPerSecond) {
    if (isVictory() || isDefeat()) return;

    static GLint totalTime = 0;
    totalTime += dt;

    GLint millisecondsPerShot = (1. / shotsPerSecond) * 1000;
    GLint nShots = totalTime / millisecondsPerShot;
    totalTime %= millisecondsPerShot;

    
    for (auto barrel : barrels) {
        if (auto enemy = barrel->getEnemy()) {

            for (int i = 0; i < nShots; i++) {
                shots.push_back(enemy->shoot());
            }

        }
    }
}

extern GLint gWidth, gHeight;

void Game::drawScoreBoard() {
    static char str[100];
    sprintf(str, "Barris destruidos: %d", score);

    GLfloat scale = gHeight/700. * 0.15;
    GLfloat lw = gHeight/700. * 1.5;

    glPushMatrix();
        glTranslatef(-15*gWidth/32., 4*gHeight/9., 0);
        glScalef(scale, scale, 1.0);
        Shape::drawText(str, lw, {1, 1, 1});
    glPopMatrix();
}

void Game::drawVictory() {
    static char str[100];
    sprintf(str, "Parabens, voce venceu!!!");

    GLfloat scale = gHeight/700. * 0.15;
    GLfloat lw = gHeight/700. * 1.5;

    glPushMatrix();
        glTranslatef(-gWidth/4., 0, 0);
        glScalef(scale, scale, 1.0);
        Shape::drawText(str, lw, {1, 1, 1});
    glPopMatrix();
}

void Game::drawDefeat() {
    static char str[100];
    sprintf(str, "Que pena, voce perdeu :(");

    GLfloat scale = gHeight/700. * 0.15;
    GLfloat lw = gHeight/700. * 1.5;

    glPushMatrix();
        glTranslatef(-gWidth/4., 0, 0);
        glScalef(scale, scale, 1.0);
        Shape::drawText(str, lw, {1, 1, 1});
    glPopMatrix();
}
