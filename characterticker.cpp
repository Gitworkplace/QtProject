#include "characterticker.h"
#include "inputobserver.h"
#include "windows.h"

//CharacterTicker::CharacterTicker(DynamicCharacterWithCam* dynaCam, PlayerAttributes* pAttributes, Drawable* player_obj, PhysicObject *testObj) : IdleObserver()
CharacterTicker::CharacterTicker(DynamicCharacterWithCam* dynaCam, PlayerAttributes* pAttributes, Drawable* player_obj, PhysicEngine* physicengine) : IdleObserver()
{
    this->pAttributes = pAttributes;
    player = dynaCam;
    m_Timer.restart();

    _player_obj = player_obj;
    modelRotation = _player_obj->getProperty<ModelTransformation>();
    _playerPhys = _player_obj->getPhysicObject();

    _physicEngine = physicengine;

    startWert = QVector4D(0, 3, 0, 1);
}

void CharacterTicker::doIt(){
    v_MoveFlagsDynCh = 0;
    time = m_Timer.restart();

    switch(pAttributes->state){
    case 0: //spieler is tot
        if(pAttributes->backward){
            modelRotation->rotate(180, 0, 1, 0);
            pAttributes->backward = false;
        }
        Sleep(500);
        spielerEngineModelMatrix = _playerPhys->getEngineModelMatrix();
        spielerEngineModelMatrix.setColumn(3, startWert);
       _playerPhys->setEngineModelMatrix(spielerEngineModelMatrix);

        if(pAttributes->lifes < 0){
            pAttributes->state = 2;
        }
        else{
            pAttributes->state = 1;
        }
        break;

    case 1: // spieler lebt

        UpdateRayCast();
        CheckRayCast();

        if (InputObserver::isKeyPressed('d'))
        {
            if(pAttributes->backward){
                modelRotation->rotate(180, 0, 1, 0);
                pAttributes->backward = false;
            }
            v_MoveFlagsDynCh |= MovementFlag::StraveRight;
        }
        if (InputObserver::isKeyPressed('a'))
        {
            if(!pAttributes->backward){
                modelRotation->rotate(180, 0, 1, 0);
                pAttributes->backward = true;
            }
            v_MoveFlagsDynCh |= MovementFlag::StraveLeft;
        }
        if (InputObserver::isKeyPressed(Qt::Key_Space))
        {
            if(pAttributes->GODMODE == true){
                if(InputObserver::isKeyPressed(Qt::Key_Control)) {
                    modelRotation->translate(0, -0.10f, 0);
                }else
                    modelRotation->translate(0, 0.10f, 0);
            }
            else if(pAttributes->isJumping==false){
                v_MoveFlagsDynCh |= MovementFlag::Jump;
                pAttributes->isJumping=true;
            }
        }

        //dient nur zur Positionierung
        if (InputObserver::isKeyPressed('e'))
        {
            qInfo() << player->getPosition3DVector();
        }

        if (InputObserver::isKeyPressed('g')){
             pAttributes->GODMODE = true;
             _player_obj->getPhysicObject()->setGravity(QVector3D(0, 0, 0));
        }
        if (InputObserver::isKeyPressed('h')){
              pAttributes->GODMODE = false;
              _player_obj->getPhysicObject()->setGravity(QVector3D(0, -142, 0));
        }
        break;

    case 2: // spieler im Gameoverscreen
        if(InputObserver::isKeyPressed('y')){
            SceneHolder::Instance()->SwitchScene(0);
            pAttributes->Reset();
        }
        break;
    case 3: // Brücke zu case 4
        if(pAttributes->backward){
            modelRotation->rotate(180, 0, 1, 0);
            pAttributes->backward = false;
        }
        Sleep(100);
        spielerEngineModelMatrix = _playerPhys->getEngineModelMatrix(); //
        spielerEngineModelMatrix.setColumn(3, startWert);               // Spieler an Start zurücksetzen
        _playerPhys->setEngineModelMatrix(spielerEngineModelMatrix);     //
        pAttributes->state =4;
        break;
    case 4: //Level beendet
        if(InputObserver::isKeyPressed('y')){
            SceneHolder::Instance()->SwitchScene(0);
            pAttributes->ResetLevel();
        }
        break;


}
    player->moveCharacter(time, v_MoveFlagsDynCh);
}

void CharacterTicker::UpdateRayCast(){
    beginn3DVec = player->getPosition3DVector(); //_player_obj->getPhysicObject()->getEngineModelMatrix().column(3).toVector3D();
    //beginn3DVec.setY(beginn3DVec.y());
    beginn3DVec.setZ(0);

    end3DVec = beginn3DVec;
    end3DVec.setY(end3DVec.y()-1);

    end3DVecA = end3DVecB = end3DVec;
    end3DVecA.setX(beginn3DVec.x()-.3f);
    end3DVecB.setX(beginn3DVec.x()+.3f);

    v_PhysicObjectA = _physicEngine->rayTestClosestBody(beginn3DVec,end3DVecA);
    v_PhysicObjectB = _physicEngine->rayTestClosestBody(beginn3DVec,end3DVecB);
}
void CharacterTicker::CheckRayCast(){
    if (v_PhysicObjectA != nullptr)
    {
        UpdateJumpState(v_PhysicObjectA);
    }
    else if (v_PhysicObjectB != nullptr)
    {
        UpdateJumpState(v_PhysicObjectB);
    }
}
void CharacterTicker::UpdateJumpState(PhysicObject* v_PhysicObject){
    //qInfo() << v_PhysicObject->getPhysicType();
    //ground
    if (v_PhysicObject->getCollisionMask() == 42){ //nach CollisionMask abfragen, da die Deadzone auch den PhysicsType 0 hat
         pAttributes->isJumping=false;
         pAttributes->enemyDetected = false;
    }
    //enemy
    else if(v_PhysicObject->getPhysicType() == 2)
    {
        EnemyHit((Drawable*)v_PhysicObject->getGeometry());
    }
}
void CharacterTicker::EnemyHit(Drawable* enemy_obj){
    pAttributes->enemyDetected = true;
    v_MoveFlagsDynCh |= MovementFlag::Jump;
    enemy_obj->setEnabled(false);
    enemy_obj->getPhysicObject()->removeFromPhysicEngine();
    //deadEnemiesList.append(enemy_obj);
    pAttributes->EnemyKilled(enemy_obj);
}
