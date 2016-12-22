#ifndef CHARACTERTICKER_H
#define CHARACTERTICKER_H

#include "idleobserver.h"
#include "physics.h"
#include <QElapsedTimer>
#include "playerAttributes.h"

#include "drawable.h"
#include "modeltransformation.h"
#include "scenemanager.h"

#include "qlist.h"

// Klasse um unsere beiden Charaktere zu steuern
class CharacterTicker : public IdleObserver
{
public:
    //CharacterTicker(DynamicCharacterWithCam* dynaCam, PlayerAttributes* pAttributes, Drawable* player_obj, PhysicObject* testObj);
    CharacterTicker(DynamicCharacterWithCam* dynaCam, PlayerAttributes* pAttributes, Drawable* player_obj, PhysicEngine* physicEngine);

    void doIt();
    void UpdateRayCast();
    void CheckRayCast();
    void UpdateJumpState(PhysicObject* v_PhysicObject);
    void EnemyHit(Drawable* enemy_obj);

private:
    PhysicEngine* _physicEngine;
    //QVector3D v_RayDirection; // Der Richtungsvektor auf welchen der Cursor // in der Szene zeigt in Weltkoordinaten

    //QVector3D v_RayPosition;


    PhysicObject* v_PhysicObjectA; // Finde das am nähesten liegende PhysicObject heraus, welches den Strahl zwischen Start und Endposition schneidet
    PhysicObject* v_PhysicObjectB;

    QVector3D beginn3DVec;
    QVector3D end3DVec;
    QVector3D end3DVecA;
    QVector3D end3DVecB;


    //Player* player;
    PlayerAttributes* pAttributes;
    DynamicCharacterWithCam* player;

    Drawable* _player_obj;
    PhysicObject* _playerPhys;
    ModelTransformation* modelRotation;

    // Timer für genaue Delta Zeitberechnung
    QElapsedTimer m_Timer;
    long long time;
    unsigned long long v_MoveFlagsDynCh;

    QMatrix4x4 spielerEngineModelMatrix;
    QVector4D startWert;

    QList<Drawable*> deadEnemiesList;
    QList<Drawable*>::iterator i;

    //evtl. mit
    //switch statement?!?
    //bool backward = false;
};

#endif // CHARACTERTICKER_H
