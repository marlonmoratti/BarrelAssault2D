#include "../include/game.h"

Game::~Game() {
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
    for (auto shot : shots) {
        shot->move(dt);
        tuple<Point, GLfloat> shotDimensions = shot->getDimensions();

        barrels.remove_if([shot, shotDimensions](auto barrel) {
            if (barrel->checkCollision(shotDimensions)) {

                shot->setCollision();

                if (barrel->decreaseLife()) {
                    delete barrel;
                    return true;
                }
            }

            return false;
        });

        if (player.checkCollision(shotDimensions)) {
            shot->setCollision();
            defeat = true; return;
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
    for (auto barrel : barrels) {
        barrel->move(dt);

        auto [playerCenter, playerRadius] = player.getDimensions();
        if (auto enemy = barrel->getEnemy()) {
            enemy->setAimingAngleTo(playerCenter.x, playerCenter.y);
        }

        if (barrel->checkCollision({ playerCenter, playerRadius })) {
            defeat = true; return;
        }
    }
}
