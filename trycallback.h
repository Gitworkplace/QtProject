#ifndef TRYCALLBACK_H
#define TRYCALLBACK_H

#include "physics.h"

#include "drawable.h"
#include "color.h"
#include "modeltransformation.h"
#include "playerattributes.h"
#include "qvector4d.h"
#include "qmatrix4x4.h"
#include "sceneholder.h"


// Dummy Klasse für Callback erzeugen, kann jede beliebige Klasse auch sein
class TryCallback
{
public:

    TryCallback(PlayerAttributes* PA){
    this->PA = PA;
    }

    //gifts
    void callback(PhysicObject*& giftPhys, PhysicObject*& b, QList<CollisionPointInfo>& c){
        giftPhys->removeFromPhysicEngine();
        gift_obj = (Drawable*)giftPhys->getGeometry();
        gift_obj->setEnabled(false);
        PA->GiftPicked((Drawable*)giftPhys->getGeometry());
    }

    //deathzone
    void HitByDeathzone(PhysicObject*& a, PhysicObject*& b, QList<CollisionPointInfo>& c){
        if(b->getCollisionMask() == 8){
                 PA->PlayerDied();
        }
        else{
        b->removeFromPhysicEngine();
        obj = (Drawable*)b->getGeometry();
        obj->setEnabled(false);
        }
    }
    //enemy
    void HitByEnemy(PhysicObject*& a, PhysicObject*& playerPhys, QList<CollisionPointInfo>& c){
        if(playerPhys->getCollisionMask() == 8){
            if(PA->enemyDetected == true){
             return;
            }
            PA->PlayerDied();
        }
    }
    //ReachedGoal
    void reachedGoal(PhysicObject*& a, PhysicObject*& b, QList<CollisionPointInfo>& c){
        PA->state = 3;
        SceneHolder::Instance()->SwitchScene(2); //Scene 2 = Level Clear Scene

    }

private:
    Drawable* gift_obj;
    Drawable* obj;
    PlayerAttributes* PA;
};

#endif // TRYCALLBACK_H

















