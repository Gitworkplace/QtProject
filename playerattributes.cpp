#include "playerattributes.h"

PlayerAttributes::PlayerAttributes(Interface* interf)
{
    this->interf=interf;
}
void PlayerAttributes::GiftPicked(Drawable* gift){
    pickedGifts.append(gift);
    anzahlGeschenke++;
    interf->erhoehen(anzahlGeschenke);
}

void PlayerAttributes::EnemyKilled(Drawable* enemy){
    killedEnemys.append(enemy);

}
void PlayerAttributes::PlayerDied(){

    for(i = killedEnemys.begin(); i != killedEnemys.end(); ++i){
        (*i)->setEnabled(true);
        (*i)->getPhysicObject()->registerPhysicObject();
    }

    for(i = pickedGifts.begin(); i != pickedGifts.end(); ++i){
        (*i)->setEnabled(true);
        (*i)->getPhysicObject()->registerPhysicObject();
    }
    killedEnemys.clear();
    pickedGifts.clear();
    state = 0;
    interf->erniedrigen(lifes);
    interf->ResetGeschenke();
    anzahlGeschenke = 0;
    lifes--;
}

void PlayerAttributes::ResetLevel(){ //Wird ausgeführt, wenn Level beendet
    for(i = killedEnemys.begin(); i != killedEnemys.end(); ++i){
        (*i)->setEnabled(true);
        (*i)->getPhysicObject()->registerPhysicObject();
    }

    for(i = pickedGifts.begin(); i != pickedGifts.end(); ++i){
        (*i)->setEnabled(true);
        (*i)->getPhysicObject()->registerPhysicObject();
    }
    killedEnemys.clear();
    pickedGifts.clear();
    Reset();
}

void PlayerAttributes::Reset(){

    isJumping = false;
    backward = false;
    enemyDetected = false;
    anzahlGeschenke = 0;
    lifes = 3;
    GODMODE = false;
    //if(state == 2){
    interf->Reset();
    //}
    state = 1;
}
