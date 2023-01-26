#include "./main.h"

void finish(void* pUserData){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        exit(50);
    }
    pDat = (UserData*)pUserData;
    // user code here
}
