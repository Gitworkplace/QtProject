#ifndef TRYCALLBACK_H
#define TRYCALLBACK_H

#include "physics.h"

#include "drawable.h"
#include "color.h"
#include "modeltransformation.h"
#include "playerattributes.h"
#include "qvector4d.h"
#include "qmatrix4x4.h"


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


        //PA->anzahlGeschenke++;
        PA->GiftPicked((Drawable*)giftPhys->getGeometry());
        //PA->interf->erhoehen();
    }

    //deathzone
    void HitByDeathzone(PhysicObject*& a, PhysicObject*& b, QList<CollisionPointInfo>& c){

        if(b->getCollisionMask() == 8){
                //PA->state = 0;
                //PA->lifes--;
                 PA->PlayerDied();
            /*
            if(PA->backward){
                player_obj = (Drawable*)b->getGeometry();
                player_obj->getProperty<ModelTransformation>()->rotate(180, 0, 1, 0);
                PA->backward = false;
            }
            v_Matrix = b->getEngineModelMatrix();
            QVector4D vec4(0, 3, 0, 1);
            v_Matrix.setColumn(3, vec4);
            b->setEngineModelMatrix(v_Matrix);
            PA->state = false; */
        }
        //"zerstöre" alles andere
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

private:
    //Drawable* player_obj;
    Drawable* gift_obj;
    Drawable* obj;
    PlayerAttributes* PA;
};

#endif // TRYCALLBACK_H
