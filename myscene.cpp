#include "opengl.h"
#include "scene.h"
#include "modeltransformation.h"
#include "keyboardtransformation.h"
#include "color.h"
#include "simplecube.h"
#include "simpleplane.h"
#include "simplesphere.h"
#include "trianglemesh.h"
#include "texture.h"
#include "characterticker.h"
#include "objticker.h"
#include "mainwindow.h"
#include "scenemanager.h"
#include "screenrenderer.h"
#include "shadermanager.h"
#include <time.h>
#include "simplecube.h"

#include "playerattributes.h"
#include "trycallback.h"
#include "sunlight.h"
#include "interface.h"

//Pfad aus .pro
static QString path(SRCDIR);
// Physic Engine Erzeugen und einen Pointer auf Instanz holen
static int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
static PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);
// Spieler Atribute Erzeugen
static Interface* interf=new Interface(path);
static PlayerAttributes* playerAttributes = new PlayerAttributes(interf);
static ObjTicker* objTicker = new ObjTicker();


Node* CreatePlayer();
Node* CreateLevel();
Node* CreateLevelCollision();
void CreateDeathzone();
Node* CreateGifts();
Node* CreateEnemies();
Node* CreateGUI();
Node *CreateSnow();
Node* CreateLights();
Node* CreateSchlitten();
Node* initScene1();
Node* initSceneGameOver();
Node* initSceneLevelClear();
unsigned int myScene;            //0
unsigned int gameOverScene;      //1
unsigned int levelClearScene;    //2


void SceneManager::initScenes()
{
    Camera* cam = new Camera;
    //std::cout<<std::endl<<std::endl<<"PFAD:"<<path.toStdString()<<std::endl<<std::endl;

    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);

    myScene = SceneManager::instance()->addScene(initScene1());
    gameOverScene = SceneManager::instance()->addScene(initSceneGameOver());
    levelClearScene = SceneManager::instance()->addScene(initSceneLevelClear());


    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    //ScreenRenderer* myRenderer2 = new ScreenRenderer(myContextNr, gameOverScene);
    SceneHolder::Instance()->AddRenderer(myRenderer);
    //SceneHolder::Instance()->AddRenderer(myRenderer);
    Q_UNUSED(SceneHolder::Instance());

    // Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    //SceneManager::instance()->setActiveScene(gameOverScene);
    SceneManager::instance()->setActiveContext(myContextNr);
   // SceneManager::instance()->setFullScreen();
}
/*TODO
 * Shader
 * Schnee Reset
 *
 *
 * */

Node* initSceneGameOver(){
    Node* root = new Node;
    Drawable* GameOver_obj = new Drawable(new TriangleMesh(path + QString("/zeug/GUI/Game_Over.obj")));
    GameOver_obj->getProperty<ModelTransformation>()->translate(1, -5, 0);
    Drawable* GameOverContinue_obj=new Drawable(new TriangleMesh(path + QString("/zeug/GUI/Game_Over_ContinueText.obj")));
    GameOverContinue_obj->getProperty<ModelTransformation>()->translate(-3.5, 2, 0);

    root->addChild(new Node(GameOver_obj));
    root->addChild((new Node(GameOverContinue_obj)));
    return root;

}

Node *initSceneLevelClear(){
    Node* root=new Node;

    Drawable* LevelClear_obj = new Drawable(new TriangleMesh(path + QString("/zeug/GUI/Level_Clear.obj")));
    LevelClear_obj->getProperty<ModelTransformation>()->translate(-0, -0, 0);
    Drawable* LevelClearContinue_obj=new Drawable(new TriangleMesh(path + QString("/zeug/GUI/Game_Over_ContinueText.obj")));
    LevelClearContinue_obj->getProperty<ModelTransformation>()->translate(-4.5, 4, 0);

    root->addChild(new Node(LevelClear_obj));
    root->addChild((new Node(LevelClearContinue_obj)));

    return root;
}


Node* initScene1()
{


    Node* root = new Node;
    root->addChild(CreatePlayer());
    root->addChild(CreateLevel());
    CreateDeathzone();  //wenn als Node -> Deadzone sichtbar
    root->addChild(CreateGifts());
    root->addChild(CreateEnemies());
    root->addChild(CreateGUI());
    root->addChild(CreateSnow());
    root->addChild(CreateLights());
    root->addChild(CreateSchlitten());

    return root;
}



Node* CreatePlayer(){
    Drawable* player_obj = new Drawable(new TriangleMesh(path + QString("/zeug/Player.obj"))); //"C:\\Users\\stlnsche\\Desktop\\computergrafik\\Player.obj"));
    //Shader Spieler
    //Shader* s =ShaderManager::getShader( path + QString("/zeug/Shader/texture.vert"),
    //                                             path + QString("/zeug/Shader/player.frag"));
    //player_obj->setShader(s);

    ModelTransformation* v_Transformation = player_obj->getProperty<ModelTransformation>();
    v_Transformation->translate(0.f, 4.f, 0.f);

    // Character Objekt erzeugen mit einer Verfolgerkamera
    DynamicCharacterWithCam* player = v_PhysicEngine->createNewDynamicCharacterWithCam(player_obj);
    // Kamera anhängen, die bestimmung der kameraposition wird nun komplett von dem character übernommen, einzig allein
    // die x achsendrehung kann noch beeinflusst werden
    player->setCam(SceneManager::instance()->getActiveContext()->getCamera());
    player->setRelativeCamPosition(0.f, 10.f, 20.f);
    player->setUpDownView(-20.0F);

    player_obj->getPhysicObject()->registerPhysicObject();
    PhysicObjectConstructionInfo* v_Constrinf_ball = new PhysicObjectConstructionInfo();
    v_Constrinf_ball->setRestitution(0.0f);
    v_Constrinf_ball->setCcdActivation(true);
    v_Constrinf_ball->setCollisionHull(CollisionHull::BoxAABB);
    player_obj->getPhysicObject()->setConstructionInfo(v_Constrinf_ball);
    player_obj->getPhysicObject()->setCollisionMask(8);

    player_obj->getPhysicObject()->setGravity(QVector3D(0.0, -142, 0.0));
    //player_obj->getPhysicObject()->
    player->setBrakeFactor(1.0);
    player->setJumpSpeed(35);
    player->setMaxStraveNormalSpeed(15);

    new CharacterTicker(player, playerAttributes, player_obj, v_PhysicEngine);

    Node* Player_objNode = new Node(player_obj);
    return Player_objNode;
}
Node* CreateLevel(){

    Drawable* level_obj = new Drawable(new TriangleMesh(path + QString("/zeug/LevelNeu.obj")));

    //Shader Level
    //Shader* s=ShaderManager::getShader( path + QString("/zeug/Shader/texture.vert"),
    //                                             path + QString("/zeug/Shader/texture.frag"));
    //level_obj->setShader(s);

    level_obj->setStaticGeometry(true); // Der Oberfläche ein statisches verhalten zuweisen
    PhysicObject* v_PlanePhys = v_PhysicEngine->createNewPhysicObject(level_obj);

    PhysicObjectConstructionInfo* v_Constrinf = new PhysicObjectConstructionInfo();
    v_Constrinf->setCollisionHull(CollisionHull::BVHTriangleMesh);
    v_Constrinf->setRestitution(0.0f);
    v_Constrinf->setFriction(0.0f);
    v_PlanePhys->setConstructionInfo(v_Constrinf);

    v_PlanePhys->registerPhysicObject();
    v_PlanePhys->setCollisionMask(42);



    return new Node(level_obj);
}
Node* CreateLevelCollision(){
    Drawable* level_Collision_obj = new Drawable(new TriangleMesh(path + QString("/zeug/Level_Oberflaeche.obj")));
    level_Collision_obj->setStaticGeometry(true);
    PhysicObject* v_LevelOberflaechePhys = v_PhysicEngine->createNewPhysicObject(level_Collision_obj);

    PhysicObjectConstructionInfo* v_Constrinf_levelcoll = new PhysicObjectConstructionInfo();
    v_Constrinf_levelcoll->setCollisionHull(CollisionHull::BVHTriangleMesh);
    v_LevelOberflaechePhys->setConstructionInfo(v_Constrinf_levelcoll);

    v_LevelOberflaechePhys->registerPhysicObject();
    v_LevelOberflaechePhys->setCollisionMask(42);

    return new Node(level_Collision_obj);
}
void CreateDeathzone(){
    Drawable* level_deathzone_obj = new Drawable(new TriangleMesh(path + QString("/zeug/deathzone.obj")));
    level_deathzone_obj->setStaticGeometry(true);
    PhysicObject* v_LevelDeathzonePhys = v_PhysicEngine->createNewPhysicObject(level_deathzone_obj);

    PhysicObjectConstructionInfo* v_Constrinf_Deathzone = new PhysicObjectConstructionInfo();
    v_Constrinf_Deathzone->setCollisionHull(CollisionHull::BoxAABB); // Automatische generierung einer Box
    v_LevelDeathzonePhys->setConstructionInfo(v_Constrinf_Deathzone);
    v_LevelDeathzonePhys->registerPhysicObject();

    SpecificResponseObject<TryCallback>* v_CallbackReceiver2 =
    new SpecificResponseObject<TryCallback>(new TryCallback(playerAttributes), &TryCallback::HitByDeathzone);
    v_LevelDeathzonePhys->addResponseObject(v_CallbackReceiver2);

    //return new Node(level_deathzone_obj);
}
Node* CreateGifts(){
    //ObjTicker* giftTicker = new ObjTicker();

    Node* GiftsHolderNode = new Node;
    SpecificResponseObject<TryCallback>* v_CallbackReceiver =
    new SpecificResponseObject<TryCallback>(new TryCallback(playerAttributes), &TryCallback::callback);
    // Dem Trigger den Callback hinzufügen welcher bei einer Collision ausgeführt wird
    // Der Callback wird außerdem nur für das Object aufgerufen an das es angehangen wurde
    // Zuerst Drawable erzeugen und platzieren, dort wird auch der Trigger platziert

    int iAnzahl = 5;
    Drawable* gifts[iAnzahl] ={0};
    Trigger* giftTriggers[iAnzahl] ={0};
    Drawable* gift_geo = new Drawable(new TriangleMesh(path + QString("/zeug/Geschenk.obj")));

    float xPositionen[iAnzahl] = {33, 35, 37, 46.5f, 53.5f};
    float yPositionen[iAnzahl] = {13,  13,  13,   10.5f,   10.5f};
    //1
    for(int i= 0; i < iAnzahl; i++){
        gifts[i] = new Drawable(gift_geo->getGeometry());
        gifts[i]->getProperty<ModelTransformation>()->translate(xPositionen[i], yPositionen[i], 0.f);
        //gifts[i]->getProperty<ModelTransformation>()->translate(-2, 2, 0.f);

        GiftsHolderNode->addChild(new Node(gifts[i]));

        giftTriggers[i] = new Trigger(v_PhysicEngine, gifts[i]);
        // Registrieren, standardmäßig ist der Trigger eine Box 1 hoch 1 breit 1 tief, mit getConstructionInfo() kann die
        // form noch verändert werden
        // Da das drawable keine geometrie besitzt kann auch keine form automatisch generiert werden,falls man dies dennoch
        // machen will muss man die gemoetrie des drawables später auf NULL setzen
        giftTriggers[i]->registerTrigger();
        giftTriggers[i]->addResponseObject(v_CallbackReceiver);
        objTicker->AddObj(gifts[i]);
    }
    return GiftsHolderNode;
}
Node* CreateEnemies(){

    Node* enemiesNode = new Node();

    SpecificResponseObject<TryCallback>* v_CallbackReceiver3 =
    new SpecificResponseObject<TryCallback>(new TryCallback(playerAttributes), &TryCallback::HitByEnemy);
    // Dem Trigger den Callback hinzufügen welcher bei einer Collision ausgeführt wird
    // Der Callback wird außerdem nur für das Object aufgerufen an das es angehangen wurde
    // Zuerst Drawable erzeugen und platzieren, dort wird auch der Trigger platziert

    int iAnzahl = 5;
    Drawable* enemy_geo = new Drawable(new TriangleMesh(path + QString("/zeug/Gegner.obj")));
    Drawable* enemies_obj[iAnzahl] ={0};
    DynamicCharacter* enemiesChar[iAnzahl] = {0};
    PhysicObject* enemiesPhys[iAnzahl] = {0};
    PhysicObjectConstructionInfo* ConstrinfEnemy[iAnzahl] = {0};

    int xPositionen[iAnzahl] = {7, 14, 42, 140, 153};
    float yPositionen[iAnzahl] = {1.9f,  1.9f,  1.9f,   1.9f,   3.9f};
   // v_Constrinf->setCollisionHull(CollisionHull::BVHTriangleMesh);
   // v_Constrinf->setRestitution(0.0f);
    //v_Constrinf->setFriction(0.0f);

    for(int i= 0; i < iAnzahl; i++){
        enemies_obj[i] = new Drawable(enemy_geo->getGeometry());
        enemiesNode->addChild(new Node(enemies_obj[i]));

        enemies_obj[i]->getProperty<ModelTransformation>()->translate(xPositionen[i], yPositionen[i], 0.f);
        enemiesChar[i] = v_PhysicEngine->createNewDynamicCharacter(enemies_obj[i]);
        enemiesPhys[i] = v_PhysicEngine->createNewPhysicObject(enemies_obj[i]);

        enemies_obj[i]->setStaticGeometry(true); // Der Oberfläche ein statisches verhalten zuweisen

        ConstrinfEnemy[i] = new PhysicObjectConstructionInfo();
        ConstrinfEnemy[i]->setCollisionHull(CollisionHull::BoxAABB);
        enemiesPhys[i]->setConstructionInfo(ConstrinfEnemy[i]);

        //enemiesChar[i]->lockLinearAxis(true, true, true); geht nicht
        enemiesPhys[i]->setPhysicType(2); //kinematic geht!
        enemiesPhys[i]->setPhysicState(0); // ist jetzt static
        enemiesPhys[i]->registerPhysicObject();
        //enemiesPhys[i]->setCollisionMask(12); //hä?

        enemiesPhys[i]->addResponseObject(v_CallbackReceiver3);
    }
    return enemiesNode;
}
Node* CreateGUI(){
    Node* GUIHolderNode = new Node();

    GUIHolderNode->addChild(interf->addGiftCounter());
    GUIHolderNode->addChild(interf->addLifeCounter());
    return GUIHolderNode;
}
Node* CreateSnow(){
    /*srand((unsigned)time(NULL));

    ObjTicker* snowTicker=new ObjTicker();

    Node* snowHolderNode=new Node;

    int anzahl=50;
    Drawable* snow[anzahl]={0};
    for(int i=0;i<anzahl;i++){
        snow[i]=new Drawable(new SimpleCube(1.,1.,1.));
        snow[i]->getProperty<ModelTransformation>()->translate(rand()%300, 50, 0);
        snowHolderNode->addChild(new Node(snow[i]));

        snowTicker->AddObj(snow[i]);
    }

    return snowHolderNode;*/
    srand((unsigned)time(NULL));

    //ObjTicker* snowTicker = new ObjTicker();

    Node* snowHolderNode = new Node;

    int iAnzahl = 500;
    Drawable* snow[iAnzahl] ={0};

   // Geometry* snow_geo = new Geometry();
    Drawable* snow_geo = new Drawable(new TriangleMesh(path + QString("/zeug/Schnee.obj")));
    for(int i= 0; i < iAnzahl; i++){

        snow[i] = new Drawable();
        snow[i]->setGeometry(snow_geo->getGeometry());
        //snow[i] = new Drawable(new TriangleMesh(path + QString("/zeug/Schnee.obj")));
        snow[i]->getProperty<ModelTransformation>()->translate(rand()%300, rand()%150+10, -rand()%5);
        snowHolderNode->addChild(new Node(snow[i]));

        objTicker->AddSnow(snow[i]);
    }
    return snowHolderNode;
}
Node* CreateLights(){
 Node* lightHolderNode = new Node();
 SunLight* sunLight = new SunLight;

 //sunLight->mViewDirection=QVector3D(0,-1,0);
 sunLight->setDiffuse(0.7, 0.7, 0.7);
 sunLight->setSpecular(0.6, 0.6, 0.6);
 sunLight->setAmbient(0.6, 0.6, 0.6);
 sunLight->turnOn();
 Node* sunLightNode = new Node(sunLight);

 lightHolderNode->addChild(sunLightNode);

    qInfo()<<"HIERSUCEHN"<<gameOverScene;

 return lightHolderNode;

}

Node* CreateSchlitten(){
    //ObjTicker* giftTicker = new ObjTicker();

    Node* SchlittenHolderNode = new Node;
    SpecificResponseObject<TryCallback>* v_CallbackReceiver =
    new SpecificResponseObject<TryCallback>(new TryCallback(playerAttributes), &TryCallback::reachedGoal);
    // Dem Trigger den Callback hinzufügen welcher bei einer Collision ausgeführt wird
    // Der Callback wird außerdem nur für das Object aufgerufen an das es angehangen wurde
    // Zuerst Drawable erzeugen und platzieren, dort wird auch der Trigger platziert

    Drawable* schlitten = new Drawable(new TriangleMesh(path + QString("/zeug/Schlitten.obj")));
    Trigger* schlittenTriggers= new Trigger(v_PhysicEngine, schlitten);
    PhysicObject *schlittenPhys=v_PhysicEngine->createNewPhysicObject(schlitten);
    //DynamicCharacter* schlittenChar=v_PhysicEngine->createNewDynamicCharacter(schlitten);
    PhysicObjectConstructionInfo* ConstrinfSchlitten= new PhysicObjectConstructionInfo();

    ConstrinfSchlitten->setCollisionHull(CollisionHull::BoxAABB);
    schlittenPhys->setConstructionInfo(ConstrinfSchlitten);

    schlitten->getProperty<ModelTransformation>()->translate(10, 2, 0.f);

    SchlittenHolderNode->addChild(new Node(schlitten));

    schlittenTriggers->registerTrigger();

    //schlittenPhys->setPhysicType(2); //kinematic geht!
    schlittenPhys->setPhysicState(0); // ist jetzt static
    schlittenPhys->registerPhysicObject();

    schlittenTriggers->addResponseObject(v_CallbackReceiver);

    return SchlittenHolderNode;
}




