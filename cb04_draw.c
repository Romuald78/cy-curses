#include "./main.h"

void draw(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        exit(40);
    }
    if(pScreen==NULL){
        exit(41);
    }
    pDat = (UserData*)pUserData;

    // user code here
    for(int y=0; y<(pScreen->height); y++){
        drawLine(pScreen, 0, y, pScreen->width, '.', 2);
    }
    drawText(pScreen, (int)(pDat->x), (int)(pDat->y),   "🐇"  , 2);
}

