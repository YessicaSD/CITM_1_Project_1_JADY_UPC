#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL.h"

#define MAX_KEYS 300
#define MAX_CONTROLLERS 2
#define MAX_BUTTON 16
enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};
enum BUTTON_STATE
{
	BUTTON_IDLE = 0,
	BUTTON_DOWN,
	BUTTON_REPEAT,
	BUTTON_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	BUTTON_STATE Controller1[MAX_BUTTON];
	BUTTON_STATE Controller2[MAX_BUTTON];
	SDL_GameControllerButton stringbutton[MAX_BUTTON];
	Uint8 button_state;
	SDL_Event event;
	SDL_GameController *controller[MAX_CONTROLLERS];


	
	
};

#endif // __ModuleInput_H__
