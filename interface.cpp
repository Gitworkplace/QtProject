#include "interface.h"
#include "qdebug.h"

Interface::Interface(QString path){
    this->path=path;
    giftHolderNode = new Node();
    lifeHolderNode=new Node();
    aktEinser=0;
    aktZehner=0;
    aktLeben=3;
}

Node* Interface::addGiftCounter(){
    Shader* s1 =ShaderManager::getShader( path + QString("/zeug/Shader/giftcountereiner.vert"),
                                                 path + QString("/zeug/Shader/player.frag"));

    Shader* s2 =ShaderManager::getShader( path + QString("/zeug/Shader/giftcounterzehner.vert"),
                                                 path + QString("/zeug/Shader/player.frag"));

    for(int i=0;i<10;i++){
        QString zahl=QString::number(i);
        qInfo()<<zahl;
        giftCounterEiner[i]=new Drawable(new TriangleMesh(path + QString("/zeug/Zahlen/") + zahl + QString(".obj")));
        giftHolderNode->addChild(new Node(giftCounterEiner[i]));
        giftCounterZehner[i]=new Drawable(new TriangleMesh(path + QString("/zeug/Zahlen/") + zahl + QString(".obj")));
        giftHolderNode->addChild(new Node(giftCounterZehner[i]));
        giftCounterEiner[i]->setShader(s1);
        giftCounterZehner[i]->setShader(s2);

        giftCounterEiner[i]->setEnabled(false);
        giftCounterZehner[i]->setEnabled(false);


    }



    giftCounterEiner[aktEinser]->setEnabled(true);
    giftCounterZehner[aktZehner]->setEnabled(true);


    return giftHolderNode;

}


Node* Interface::addLifeCounter(){
    Shader* s1 =ShaderManager::getShader( path + QString("/zeug/Shader/lebencounter.vert"),
                                                 path + QString("/zeug/Shader/player.frag"));

    Shader* s2 =ShaderManager::getShader( path + QString("/zeug/Shader/herzinterface.vert"),
                                                 path + QString("/zeug/Shader/player.frag"));

    for(int i=0;i<=3;i++){
        QString zahl=QString::number(i);
        qInfo()<<zahl;
        lebenCounter[i]=new Drawable(new TriangleMesh(path + QString("/zeug/Zahlen/") + zahl + QString(".obj")));
        lifeHolderNode->addChild(new Node(lebenCounter[i]));
        lebenCounter[i]->setShader(s1);

        lebenCounter[i]->setEnabled(false);


    }

    herz=new Drawable(new TriangleMesh(path + QString("/zeug/GUI/Herz.obj")));
    herz->setShader(s2);

    lebenCounter[3]->setEnabled(true);
    herz->setEnabled(true);

    lifeHolderNode->addChild(new Node(herz));

    return lifeHolderNode;

}


void Interface::erhoehen(){
    giftCounterEiner[aktEinser]->setEnabled(false);
    giftCounterZehner[aktZehner]->setEnabled(false);
    aktEinser++;
    if(aktEinser==10){
        aktEinser=0;
        aktZehner++;
    }
    giftCounterEiner[aktEinser]->setEnabled(true);
    giftCounterZehner[aktZehner]->setEnabled(true);

}

void Interface::erniedrigen(){


    if(aktLeben==0){
        return;
    }
    lebenCounter[aktLeben]->setEnabled(false);
    aktLeben--;

    lebenCounter[aktLeben]->setEnabled(true);


}




















