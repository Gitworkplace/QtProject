#ifndef OBJTICKER_H
#define OBJTICKER_H

#include "idleobserver.h"
#include "physics.h"
#include <QElapsedTimer>
#include "playerAttributes.h"

#include "drawable.h"
#include "modeltransformation.h"
#include "scenemanager.h"
#include "QList"
#include <stdio.h>
#include <time.h>

// Klasse um unsere beiden Charaktere zu steuern
class ObjTicker : public IdleObserver

{
public:
    //CharacterTicker(DynamicCharacterWithCam* dynaCam, PlayerAttributes* pAttributes, Drawable* player_obj, PhysicObject* testObj);
    ObjTicker();
    void doIt();
    void AddObj(Drawable* obj);
    void AddSnow(Drawable* snow);
    void AddNumber(Drawable* obj);
private:
    PhysicEngine* _physicEngine;

    QList<ModelTransformation*> list;
    QList<ModelTransformation*> listSnow;
    QList<ModelTransformation*>::iterator i;

    Drawable* _obj;
    ModelTransformation* modelRotation;
    ModelTransformation* modelTransformation;
    // Timer für genaue Delta Zeitberechnung
    QElapsedTimer m_Timer;
    long long time;
    unsigned long long v_MoveFlagsDynCh;

    QMatrix4x4 spielerEngineModelMatrix;
    QVector4D startWert;

    QVector3D cameraPosition;
    Drawable* testObj;
    QMatrix4x4 testMatrix;
};

#endif // OBJTICKER_H
