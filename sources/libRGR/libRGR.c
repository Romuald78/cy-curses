//
// Created by cytech on 06/12/22.
//

#include <locale.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "libRGR.h"
#include "keys.h"
#include "../errors/errors.h"

unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
}

void checkGame(GameData* pGame, int errCode){
    // Locals
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    // Check params
    if(pGame == NULL){
        RAGE_QUIT(errCode, "Game data pointer NULL !\n");
    }
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    // Check internal pointers
    if(pScr == NULL){
        RAGE_QUIT(errCode+1, "Game screen pointer NULL !\n");
    }
    if(pDat == NULL){
        RAGE_QUIT(errCode+2, "Game user data pointer NULL !\n");
    }
    if(pCb == NULL){
        RAGE_QUIT(errCode+3, "Game user callback pointer NULL !\n");
    }
}

int checkEvent(GameData* pGame){
    // Locals
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    Event      evt;
    int        ch = ERR+1;
    long       value = KEY_NONE;
    int        size  = 0;
    int        flag;
    // Check params
    checkGame(pGame, 3000);
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;

    // Get all key values from the stdin
    // Some keys generate several bytes
    while( (ch=getch()) != ERR ){
        value = (value<<8) | ch;
        flag  = 0;
        size++;
        // ASCII flag
        flag |= (((size==1) && (value!=EXT_ESC)) || ((size==2) && (value!=EXT_CSI))) && (value>=0) && (value<=127);
        // SPECIAL1 flag2
        flag |= (size==2) && ((value & 0xFF00      ) == EXT_SPEC1);
        flag |= (size==2) && ((value & 0xFF00      ) == EXT_SPEC2);
        // CSI flag
        flag |= (size==3) && ((value & 0xFFFF00    ) == EXT_CSI) && (value != HDR_FN1) && (value != HDR_FN2);
        // SS3 flag
        flag |= (size==3) && ((value & 0xFFFF00    ) == EXT_SS3);
        // FUNCTION flags
        flag |= (size==5) && ((value & 0xFFFFFF00FF) == EXT_FN1);
        flag |= (size==5) && ((value & 0xFFFFFF00FF) == EXT_FN2);
        flag |= (size==2) && ((value & 0xFF00      ) == EXT_FN3);
        /* // DEBUG ---------------------
        debug("|%3d| => [%0p]\n", ch, value);
        if( flag ){
            debug("===>>>\n");
        }
        // --------------------- END DEBUG */

        // Send event to user code
        if( flag ){
            evt.code = value;
            pCb->cbEvent(pDat, pScr, &evt);
            //value    = KEY_NONE;
            //size     = 0;
        }
    }
    // ESCAPE flag : exit request
    if( (size==1) && (value == EXT_ESC) ){
        return 1;
    }
    else{
        return 0;
    }
}

GameData* createGame(int        nbCharX,
                     int        nbCharY,
                     void*      pUserData,
                     Callbacks* pCb,
                     int        fps){
    // Local vars
    Screen*   pScreen = NULL;
    GameData* pGame   = NULL;

    // Check parameters
    if(nbCharX <= 0 || nbCharY <= 0){
        RAGE_QUIT(100, "Bad game dimensions : nbCharX=%d / nbCharY=%d\n", nbCharX, nbCharY);
    }
    // Check parameter pointers
    if(pUserData == NULL){
        RAGE_QUIT(110, "Empty user data pointer !\n");
    }
    if(pCb == NULL){
        RAGE_QUIT(120, "Empty callback pointer !\n");
    }
    // Check callbacks
    if( pCb->cbInit == NULL ){
        RAGE_QUIT(130, "Empty INIT callback pointer !\n");
    }
    if( pCb->cbEvent == NULL ){
        RAGE_QUIT(131, "Empty EVENT callback pointer !\n");
    }
    if( pCb->cbUpdate == NULL ){
        RAGE_QUIT(132, "Empty UPDATE callback pointer !\n");
    }
    if( pCb->cbDraw == NULL ){
        RAGE_QUIT(133, "Empty DRAW callback pointer !\n");
    }
    if( pCb->cbFinish == NULL ){
        RAGE_QUIT(134, "Empty FINISH callback pointer !\n");
    }
    // Allocate SCREEN structure
    pScreen = malloc( sizeof(Screen) );
    if(pScreen == NULL){
        RAGE_QUIT(140, "Screen malloc failed !\n");
    }
    // Allocate Game struct
    pGame = malloc( sizeof(GameData) );
    if( pGame==NULL ){
        RAGE_QUIT(150, "Screen malloc failed !\n");
    }
    // Fill game structure
    pScreen->width        = nbCharX;
    pScreen->height       = nbCharY;
    pGame->pScreen        = pScreen;
    pGame->pUserData      = pUserData;
    pGame->pUserCallbacks = pCb;
    pGame->displayFPS     = fps;
    // return game structure
    return pGame;
}

void gameLoop(GameData* pGame){
    // Locals
    WINDOW*    pWin = NULL;
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    int       loop = 0;
    unsigned long startTime;
    unsigned long endTime;
    unsigned long frameTime = 0;
    // Check params
    checkGame(pGame, 200);
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    // Locales
    setlocale(LC_ALL, "");
    // Init of GFX (curses library)
    pWin = initscr();
    start_color();
    noecho();
    curs_set(0);
    nodelay(pWin, TRUE);
    // COLORS (TODO)
    init_pair(1, 7, 0);
    // Call init here
    pCb->cbInit(pDat, pScr);
    // First time measurement
    startTime = getTimeMicros();
    //=======================================
    // START of game loop
    //=======================================
    while(loop==0){
        //--------------------------
        // (call event if needed)
        //--------------------------
        loop |= checkEvent(pGame);
        //--------------------------
        // (call update)
        //--------------------------
        loop |= pCb->cbUpdate(pDat, pScr, frameTime);
        //--------------------------
        // (call draw + display FPS)
        //--------------------------
        // Clear must not be called to avoid flickering
        // BUT the user MUST ensure to redraw the whole part of the screen
        //clear();
        pCb->cbDraw(pDat, pScr);
        if(pGame->displayFPS != 0){
            move(0,0);
            printw("|FPS %ld|", (unsigned long)(0.99 + 1000000.0/(double)frameTime));
        }
        refresh();
        //--------------------------
        // Wait for next frame
        //--------------------------
        // Get frame time
        endTime   = getTimeMicros();
        frameTime = (endTime - startTime);
        startTime = endTime;
        // Wait to achieve 60FPS
        if(frameTime <= 16666){
            usleep(16666-frameTime);
        }
    }
    //=======================================
    // END of game loop
    //=======================================
    //--------------------------
    // Call finish here and exit
    //--------------------------
    pCb->cbFinish(pDat);
    // Finish curses
    echo();
    endwin();
}


//-----------------------------------------
// DRAW
//-----------------------------------------
void setColor(unsigned char id, unsigned char r, unsigned char g, unsigned char b){
    short rr = (short)((1000 * r) / 255);
    short gg = (short)((1000 * g) / 255);
    short bb = (short)((1000 * b) / 255);
    init_color(id, rr, gg, bb);
}
void setColorPair(unsigned char id, unsigned char txtId, unsigned char backId){
    init_pair(id, txtId, backId);
}
void drawText(Screen* pScr, int x, int y, char* pText, int clrId){
    // Local buffer to copy string
    char pWrite[256] = {0};
    if(pText == NULL){
        RAGE_QUIT(50, "Text pointer NULL !\n");
    }
    if(pScr == NULL){
        RAGE_QUIT(51, "Screen pointer NULL !\n");
    }
    // TODO issue when trying to print the trailing chars of a string started on the left edge of the screen !!
    // TODO issue when printing an emoji : when reaching the right border of the screen
    if(x>=0 && y>=0 && x<pScr->width && y<pScr->height){
        move(y, x);
        attron(COLOR_PAIR(clrId));
        // limit the size of the string in order to avoid printing outside the edges
        unsigned long sz  = pScr->width - x;
        unsigned long len = strlen(pText);
        if(sz > len+1){
            sz = len;
        }
        if(len > 255){
            RAGE_QUIT(52, "pText string exceeds 255 chars !\n");
        }
        strcpy(pWrite, pText);
        pWrite[sz] = '\0';
        printw(pWrite);
        //attroff(COLOR_PAIR(clrId));
    }
}
void drawLine(Screen* pScr, int x, int y, int w, char ch, int clrId){
    if(pScr == NULL){
        RAGE_QUIT(60, "Screen pointer NULL !\n");
    }
    move(y, x);
    attron(COLOR_PAIR(clrId));
    for(int dx=0; dx<w && (x+dx)<pScr->width; dx++){
        if(x+dx >= 0){
            mvaddch(y, x+dx, ch);
        }
    }
}
