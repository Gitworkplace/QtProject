#include "sceneholder.h"

SceneHolder* SceneHolder::sInstance = nullptr;

SceneHolder* SceneHolder::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new SceneHolder;
    }
    return sInstance;
}

void SceneHolder::AddRenderer(ScreenRenderer* renderer){
    screenRenderer = renderer;
}

void SceneHolder::SwitchScene(unsigned int iScene){
    screenRenderer->setScene(iScene);

}

