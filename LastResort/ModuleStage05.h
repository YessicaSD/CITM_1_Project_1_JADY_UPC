#ifndef __MODULE5LVLSCENE_H__
#define __MODULE5LVLSCENE_H__

#include "Application.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL\include\SDL.h"
#include "MovPath.h"
#include "SDL/include/SDL_timer.h"

typedef struct _Mix_Music Mix_Music;

class Module5lvlScene : public Module
{
public:
	Module5lvlScene();
	~Module5lvlScene() {

	};

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//provisional-----------------------------
	int current_time= 0;
	int start_time = 0;
	//----------------------------------------

	MovePath cameraMovement;
	dPoint shipOffset = {444, -240};
	SDL_Texture * StarsTexture = nullptr;
	SDL_Texture *shipTex = nullptr;
	SDL_Rect shipRect;
	SDL_Rect StarsRect;
	SDL_Rect StarsRect2;


	dPoint scroll;
	dPoint stars;

	Mix_Music* lvl5Music = nullptr;

	//Spaceship colliders
	Collider* frontShipCol1;
};

#endif
