#include "./main.h"

int  update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(30, "Game user data pointer NULL !\n");
    }
    if(pScreen==NULL){
        RAGE_QUIT(31, "Game screen pointer NULL !\n");
    }
    pDat = (UserData*)pUserData;

    // User code here

    // update position
    pDat->x += pDat->dx;
    pDat->y += pDat->dy;
    // apply friction on speed vector
    pDat->dx *= FRICTION;
    pDat->dy *= FRICTION;

    // We return 0 to tell to continue, else the program will stop
    return 0;
}


