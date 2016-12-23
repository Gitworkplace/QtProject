#ifndef SCENEHOLDER_H
#define SCENEHOLDER_H

#include "screenrenderer.h"
#include "scene.h"
#include "scenemanager.h"

class SceneHolder
{
public:
    static SceneHolder* Instance();
    void AddRenderer(ScreenRenderer* renderer);
    void SwitchScene(unsigned int iScene);

private:
    SceneHolder(){}
    static SceneHolder* sInstance;


    ScreenRenderer* screenRenderer;
};

#endif // SCENEHOLDER_H
