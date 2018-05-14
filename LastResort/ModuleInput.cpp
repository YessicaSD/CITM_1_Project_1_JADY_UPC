#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

	for (uint i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		Controller1[i] = KEY_IDLE;

	for (uint i = 0; i <SDL_CONTROLLER_BUTTON_MAX; ++i)
		Controller2[i] = KEY_IDLE;

	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		controller[i] = nullptr;
	}
	int i = 0;
	stringbutton[0] = SDL_CONTROLLER_BUTTON_A; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_B; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_X; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_Y; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_BACK; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_GUIDE; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_START; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_LEFTSTICK; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_RIGHTSTICK; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_LEFTSHOULDER; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_DPAD_UP; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_DPAD_DOWN; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_DPAD_LEFT; ++i;
	stringbutton[0 + i] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT; ++i;


}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_INIT_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	

	
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	//Open the first available controller
	
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller[i] = SDL_GameControllerOpen(i);
			if (controller) {
				break;
			}
			else {
				LOG("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}


	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	//Controller 1 ---------------------------------------------------------------------------------
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (SDL_GameControllerGetButton(controller[0], stringbutton[i]))
		{
			if (Controller1[i] == KEY_IDLE)
				Controller1[i] = KEY_DOWN;
			else
				Controller1[i] = KEY_REPEAT;
		}
		else
		{
			if (Controller1[i] == KEY_REPEAT || Controller1[i] == KEY_DOWN)
				Controller1[i] = KEY_UP;
			else
				Controller1[i] = KEY_IDLE;
		}
	}

	//Controller 2----------------------------------------------------------------------------
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (SDL_GameControllerGetButton(controller[1], stringbutton[i]))
		{
			if (Controller2[i] == KEY_IDLE)
				Controller2[i] = KEY_DOWN;
			else
				Controller2[i] = KEY_REPEAT;
		}
		else
		{
			if (Controller2[i] == KEY_REPEAT || Controller2[i] == KEY_DOWN)
				Controller2[i] = KEY_UP;
			else
				Controller2[i] = KEY_IDLE;
		}
	}

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	        return update_status::UPDATE_STOP;
	
	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;
	

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			SDL_GameControllerClose(controller[i]);
			
		}
	}
	return true;
}
