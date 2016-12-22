#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H
#include "interface.h"

class PlayerAttributes
{
public:
    PlayerAttributes(Interface* interf);



    char lives = 1;
    bool isJumping = false;
    bool backward = false;
    bool enemyDetected = false;
    int anzahlGeschenke = 0;
    int anzahlPunkte = 0;

    bool GODMODE = false;
    Interface* interf;
};

#endif // PLAYERATTRIBUTES_H
