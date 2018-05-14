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
	KEY_STATE Controller1[MAX_BUTTON];
	KEY_STATE Controller2[MAX_BUTTON];
	SDL_GameControllerButton stringbutton[MAX_BUTTON];
	SDL_GameController *controller[MAX_CONTROLLERS];
	SDL_Event event;
	


	
	
};

#endif // __ModuleInput_H__
