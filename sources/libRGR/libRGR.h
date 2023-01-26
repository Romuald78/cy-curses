//
// Created by cytech on 06/12/22.
//

#ifndef CY_CURSES_LIBRGR_H
#define CY_CURSES_LIBRGR_H

#include "keys.h"
#include "../errors/errors.h"

// Key code
typedef long KeyCode;
// Event structure
typedef struct {
    KeyCode  code;
} Event;

// Canvas Structure
typedef struct {
    int width;      // number of characters along X-axis
    int height;     // number of characters along Y-axis
} Screen;

// User Callback Functions
typedef void (*InitCallback  )(void* pUSerData, Screen* pScreen);
typedef void (*EventCallback )(void* pUserData, Screen* pScreen, Event* pEvt);
typedef int  (*UpdateCallback)(void* pUserData, Screen* pScreen, unsigned long deltaTime);
typedef void (*DrawCallback  )(void* pUSerData, Screen* pScreen);
typedef void (*FinishCallback)(void* pUserData);

// Callback structure
typedef struct{
    InitCallback   cbInit;
    EventCallback  cbEvent;
    UpdateCallback cbUpdate;
    DrawCallback   cbDraw;
    FinishCallback cbFinish;
} Callbacks;

// Full game structure
typedef struct{
    Screen*    pScreen;
    void*      pUserData;
    Callbacks* pUserCallbacks;
    int        displayFPS;
} GameData;

//=========== GAME FUNCTIONS ===========//
GameData* createGame(int nbCharX, int nbCharY, void* pUserData, Callbacks* pCb, int fps);
void      gameLoop  (GameData* pGame);

//=========== DRAW FUNCTIONS ===========//
void setColor    (unsigned char id, unsigned char r, unsigned char g, unsigned char b);
void setColorPair(unsigned char id, unsigned char txtId, unsigned char backId);
void drawText    (Screen* pScr, int x, int y, char* pText   , int clrId);
void drawLine    (Screen* pScr, int x, int y, int w, char ch, int clrId);

#endif //CY_CURSES_LIBRGR_H
