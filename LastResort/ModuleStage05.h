#ifndef __MODULE5LVLSCENE_H__
#define __MODULE5LVLSCENE_H__

#include "Application.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL\include\SDL.h"
#include "MovPath.h"
#include "SDL/include/SDL_timer.h"

#define SHIP_COLLIDERS_NUM 47//The number of colliders the ship is made of (see Docs>shipColliders.psd)


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
	//CheckPoint-----------------------------
	int current_time= 0;
	int start_time = 0;
	int currentCheckPoint = 0;
	int currentMov = 0;

	//Points----------------------------------
	dPoint backgroundPoint;//The position that we directly move with the path
	dPoint shipPos;//We'll use this position to instantiate enemies. Position at which we blit the ship (see Docs>ship.psd). 
	dPoint tunnelPos;
	MovePath cameraMovement;
	dPoint shipOffset = { 444, -240 };
	dPoint tunnelOffset = { 1856, -58 };
	dPoint scroll;
	iPoint spawnPos;//The position from which we spawn enemies, in this stage it's going to be the same as shipPos (because it's easy for us to get the positions from that psd)

	//Rectangles-------------------------------
	SDL_Rect shipRect;
	SDL_Rect tunnelRect;
	SDL_Rect StarsRect;
	SDL_Rect StarsRect2;

	//Spaceship colliders
	Collider* shipCollidersCol[SHIP_COLLIDERS_NUM];
	SDL_Rect shipCollidersRect[SHIP_COLLIDERS_NUM];

	//Colliders-------------------------------
	Collider* frontShipCol1;

	//Tetures---------------------------------
	SDL_Texture * StarsTexture = nullptr;
	SDL_Texture *shipTex = nullptr;
	SDL_Texture *tilemapTex = nullptr;
	
	//Music-----------------------------------
	Mix_Music* lvl5Music = nullptr;
};

#endif
