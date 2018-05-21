#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL\include\SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Configuration -----------------------------
//----------Screen-------------------
#define SCREEN_SIZE 4
#define SCREEN_WIDTH 304
#define SCREEN_HEIGHT 224
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0 // Change this to one for full screen 
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define REN_VSYNC 1

//----------Music-------------------
#define GENERAL_MUSIC_VOLUME 15 //0 to 180 //Optimum 15
#define GENERAL_SFX_VOLUME 20 //0 to 100   //Optimum 20

//----------Spawning----------------
const int SPAWN_MARGIN_LEFT = 40;
const int SPAWN_MARGIN_RIGHT = 20;
const int SPAWN_MARGIN_UP = 40;
const int SPAWN_MARGIN_DOWN = 30;
const int DESPAWN_MARGIN_LEFT = 250;
const int DESPAWN_MARGIN_RIGHT = 200;
const int DESPAWN_MARGIN_UP = 200;
const int DESPAWN_MARGIN_DOWN = 200;// Despawn margin always needs to be bigger than spawn margin or otherwise enemies would be spawned and immmediately despawned

// Useful typedefs ---------------------------
typedef unsigned int uint;

#endif // __GLOBALS_H__