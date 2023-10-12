#ifndef GAME_H
#define GAME_H

#include <list>

#include "arena.h"
#include "shooter.h"
#include "shot.h"
#include "barrel.h"

using namespace std;

class Game {
    bool victory = false, defeat = false;
    Arena& arena; Shooter& player;
    list<Shot*>& shots; list<Barrel*>& barrels;
    int* keyStatus;
public:
    Game(Arena& arena, Shooter& player, int* keyStatus, list<Shot*>& shots, list<Barrel*>& barrels)
            : arena(arena), player(player), keyStatus(keyStatus), shots(shots), barrels(barrels) {};
    ~Game();

    bool isVictory();
    bool isDefeat();
    void movePlayer(GLfloat inc);
    void moveShot(GLdouble dt);
    void moveBarrel(GLdouble dt);
};

#endif
