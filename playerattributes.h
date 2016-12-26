#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H
#include "interface.h"
#include "qlist.h"

class PlayerAttributes
{
public:
    PlayerAttributes(Interface* interf);

    void GiftPicked(Drawable* gift);
    void EnemyKilled(Drawable* enemy);
    void PlayerDied();
    void Reset();
    void ResetLevel();


    char state = 1;

    bool isJumping = false;
    bool backward = false;
    bool enemyDetected = false;

    int anzahlGeschenke = 0;
    int lifes = 3;

    bool GODMODE = false;
    Interface* interf;

    QList<Drawable*> killedEnemys;
    QList<Drawable*> pickedGifts;
    QList<Drawable*>::iterator i;


};

#endif // PLAYERATTRIBUTES_H
