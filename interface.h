
#ifndef INTERFACE_H
#define INTERFACE_H
#include "drawable.h"
#include "shader.h"
#include "shadermanager.h"
#include "trianglemesh.h"
#include "sceneholder.h"

class Interface
{
public:
    Interface(QString path);
    Node* addGiftCounter();
    Node* addLifeCounter();
    void erhoehen(int anzahlGeschenke);
    void erniedrigen(int leben);
    void Reset(int anzahlLeben);
    void ResetLeben(int anzahlLeben);
    void ResetGeschenke();


private:
    Drawable* giftCounterEiner[10];
    Drawable* giftCounterZehner[10];
    Drawable* lebenCounter[4];
    Drawable* herz;
    QString path;
    Node* giftHolderNode;
    Node* lifeHolderNode;
    int aktEinser;
    int aktZehner;
    //int aktLeben;
};

#endif // INTERFACE_H
