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
    // Draw background (grass)
    for(int y=0; y<(pScreen->height); y++){
        drawLine(pScreen, 0, y, pScreen->width, ' ', GRASS);
    }
    // Draw random rocks
    setColorPair(GRASS, 0, GRASS);
    setColorPair(ROCK, 0, ROCK);
    setColorPair(WATER, 0, WATER);
    for(int x=0; x<(pScreen->width); x++){
        for(int y=0; y<(pScreen->height); y++){
            // Random cell type
            int value = 0;
            int clrId = GRASS;
            srand((x+1)*(y+2)*(x+y+3) );
            value = rand() % 100;
            if(value < 10){
                clrId = ROCK;
            }
            else if(value < 30){
                clrId = WATER;
            }
            // Draw either character or empty cell
            if(x == (int)(pDat->x) && y == (int)(pDat->y)){
                drawText(pScreen, x, y, "@", clrId);
            }
            else{
                drawText(pScreen, x, y, " ", clrId);
            }
        }
    }


}

