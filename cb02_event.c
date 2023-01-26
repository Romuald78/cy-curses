#include "./main.h"

void event(void* pUserData, Screen* pScreen, Event* pEvt){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        exit(20);
    }
    if(pScreen==NULL){
        exit(21);
    }
    if(pEvt==NULL){
        exit(22);
    }
    pDat = (UserData*)pUserData;

    // User code here

    switch(pEvt->code){
        case KEY_ARROW_LEFT :
            pDat->dx = -SPEED;
            break;
        case KEY_ARROW_RIGHT :
            pDat->dx = SPEED;
            break;
        case KEY_ARROW_UP :
            pDat->dy = -SPEED;
            break;
        case KEY_ARROW_DOWN :
            pDat->dy = SPEED;
            break;
/*
        case KEY_TAB :
            debug("TAB\n");
            break;
        case KEY_RETURN :
            debug("RETURN\n");
            break;
        case KEY_DELETE :
            debug("DELETE\n");
            break;
        case KEY_SPACE :
            debug("SPACE\n");
            break;

        case KEY_F1 :
            debug("F1\n");
            break;
        case KEY_F2 :
            debug("F2\n");
            break;
        case KEY_F3 :
            debug("F3\n");
            break;
        case KEY_F4 :
            debug("F4\n");
            break;
        case KEY_F5 :
            debug("F5\n");
            break;
        case KEY_F6 :
            debug("F6\n");
            break;
        case KEY_F7 :
            debug("F7\n");
            break;
        case KEY_F8 :
            debug("F8\n");
            break;
        case KEY_F9 :
            debug("F9\n");
            break;
        case KEY_F11 :
            debug("F11\n");
            break;
        case KEY_F12 :
            debug("F12\n");
            break;
        default :
            if(pEvt->code < 127){
                debug("%c\n", pEvt->code);
            }
            break;
    //*/
    }
}
