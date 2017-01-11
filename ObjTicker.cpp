#include "objticker.h"
#include "inputobserver.h"

//CharacterTicker::CharacterTicker(DynamicCharacterWithCam* dynaCam, PlayerAttributes* pAttributes, Drawable* player_obj, PhysicObject *testObj) : IdleObserver()
ObjTicker::ObjTicker() : IdleObserver()
{
    _obj = nullptr;
    testObj = nullptr;

}

void ObjTicker::doIt(){
    if(testObj != nullptr){
     cameraPosition = SceneManager::instance()->getActiveContext()->getCamera()->getPosition();
     testMatrix.setColumn(3, QVector4D(cameraPosition.x()+5, cameraPosition.y()-1.5f, 10, 1));
     //qInfo() << testMatrix;
     testObj->getPhysicObject()->setEngineModelMatrix(testMatrix);
     //qInfo() << testObj->getPhysicObject()->getEngineModelMatrix();
             //getProperty<ModelTransformation>()->
    }
    //Geschenke
    for(i = list.begin(); i != list.end(); ++i){
        modelRotation = *i;
        modelRotation->rotate(0.25f, 0, 1, 0);
    }

    //Schneefall
    //int b=0;
    /*for(i=listSnow.begin();i!=listSnow.end();++i){
        modelTransformation=*i;
        modelTransformation->rotate(0.25f, 0, 1, 0);
        modelTransformation->translate((rand()%5)/2000.0, -(rand()%5)/200.f, 0);

    }*/
}

void ObjTicker::AddObj(Drawable* obj){
    list.append(obj->getProperty<ModelTransformation>());
}

void ObjTicker::AddSnow(Drawable *snow){
    listSnow.append(snow->getProperty<ModelTransformation>());
}


void ObjTicker::AddNumber(Drawable* obj){
    testObj = obj;
    testMatrix = obj->getPhysicObject()->getEngineModelMatrix();
}
