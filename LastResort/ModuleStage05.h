#ifndef __MODULE5LVLSCENE_H__
#define __MODULE5LVLSCENE_H__

#include "Application.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL\include\SDL.h"
#include "MovPath.h"
#include "SDL/include/SDL_timer.h"
#include "Enemy_Middle_Asteroid.h"

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
	update_status PreUpdate();
	bool CleanUp();

	//Other functions
	void RenderShipPart();

	void ResetValues();

public:
	//CheckPoint-----------------------------
	int current_time= 0;
	int start_time = 0;
	int currentCheckPoint = 0;
	int currentMov = 0;

	//Points----------------------------------
	MovePath cameraMovement;
	bool pauseCamera = false;
	dPoint backgroundPoint;//The position that we directly move with the path
	dPoint shipPos;//We'll use this position to instantiate enemies. Position at which we blit the ship (see Docs>ship.psd). 
	dPoint tunnelPos;
	dPoint bossPos;
	iPoint spawnPos;//The position from which we spawn enemies, in this stage it's going to be the same as shipPos (because it's easy for us to get the positions from that psd)

	dPoint shipOffset = { 444, -240 };
	dPoint tunnelOffset = { 1856, -58 };
	dPoint bossOffSet = { 2731, -58 };

	dPoint scroll;

	//Rectangles-------------------------------
	SDL_Rect shipRect;
	SDL_Rect tunnelRect;
	SDL_Rect StarsRect;
	SDL_Rect StarsRect2;

	//Spaceship colliders
	Collider* shipCollidersCol[SHIP_COLLIDERS_NUM];
	SDL_Rect shipCollidersRect[SHIP_COLLIDERS_NUM];

	//Textures---------------------------------
	SDL_Texture * starsTx = nullptr;
	SDL_Texture * shipTx = nullptr;
	SDL_Texture * shipPartTx = nullptr;
	SDL_Texture * tilemapTx = nullptr;
	SDL_Texture * bossTx = nullptr;
	
	//Animations------------------------------
	Animation bossAnim;

	//Music-----------------------------------
	Mix_Music* lvl5Music = nullptr;

	//Ship part front-------------------------
	SDL_Rect shipPartRect = { 2, 0, 251, 96 };
	iPoint shipPartPos;
	const int fallSpeed = 1;

	//Fireball front-------------------------
	int fireballFrameCounter;

	//Ship part rear-------------------------
	SDL_Rect shipRearRect = { 0, 96, 128, 64};

	//Enemies--------------------------------
	int redBatsKilled;
	int rotatingTurretsKilled;
};

#endif
