//
// Created by cytech on 06/12/22.
//

#ifndef CY_CURSES_ERRORS_H
#define CY_CURSES_ERRORS_H

//============ ERRORS ============//
void rageQuit(const char* fname,
              const int   lineno,
              const char* fxname,
              const int   errorCode,
              const char* format, ...);
#define RAGE_QUIT(errCode, format, ...) rageQuit(__FILE__, __LINE__, __func__, errCode, format, ##__VA_ARGS__)

//============ DEBUG ============//
void debug(const char* format, ...);


#endif //CY_CURSES_ERRORS_H
