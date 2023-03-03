#include "./main.h"


void init(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        exit(10);
    }
    if(pScreen==NULL){
        exit(11);
    }
    pDat = (UserData*)pUserData;

    // User code here


    // init position
    pDat->x = 10.0f;
    pDat->y = 10.0f;
    pDat->dx = 0.0f;
    pDat->dy = 0.0f;
    // set cell colors
    setColor(GRASS, 64,140,64);
    setColor(ROCK, 128,128,128);
    setColor(WATER, 64,64,255);
    // Set player color
    setColor(CHARACTER, 128, 128, 255);
    setColorPair(CHARACTER, CHARACTER, GRASS);
}
