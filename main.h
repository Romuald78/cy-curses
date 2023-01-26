#include <stdio.h>
#include <stdlib.h>

#include "./sources/libRGR/libRGR.h"

#define GRASS     1
#define CHARACTER 2

#define SPEED        1.0f
#define ACCELERATION 0.5f
#define FRICTION     0.0f
// User data for the game
typedef struct{
    float x;
    float y;
    float dx;
    float dy;
} UserData;

void init  (void* pUserData, Screen* pScreen);
void event (void* pUserData, Screen* pScreen, Event* pEvt);
int  update(void* pUserData, Screen* pScreen, unsigned long deltaTime);
void draw  (void* pUserData, Screen* pScreen);
void finish(void* pUserData);
