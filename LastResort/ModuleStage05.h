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
#include "ModuleAudio.h"

#define SHIP_COLLIDERS_NUM 48//The number of colliders the ship is made of (see Docs>shipColliders.psd)
#define FINAL_COLLIDERS_NUM 13//The number of colliders the final part is made of (see Docs>finalPartColliders.psd)
#define CHECKPOIN_NUMBER 25

struct  Music;

class Module5lvlScene : public Module
{
public:
	Module5lvlScene();
	~Module5lvlScene() {

	};

	bool Start();
	update_status LogicUpdate();
	update_status RenderUpdate0();
	update_status RenderUpdate1();
	bool CleanUp();

	//Other functions

	void AddShipColliders();
	void UpdateShipColliders();
	void DeleteShipColliders();

	void AddFinalColliders();
	void UpdateFinalColliders();
	void DeleteFinalColliders();

	void RenderShipPart();
	void FireballFrontShip();
	void FirebarsRearShip();
	void ShipRear();
	void RenderShip();
	void ResetValues();

public:
	//CheckPoint-----------------------------
	int current_time= 0;
	int start_time = 0;
	int currentCheckPoint = 0;
	int currentMov = 0;
	bool reachedCheckpoint[CHECKPOIN_NUMBER];

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
	bool addedShipColliders = false;
	bool deletedShipColliders = false;
	//Final part colliders
	Collider* finalCollidersCol[FINAL_COLLIDERS_NUM];
	SDL_Rect finalCollidersRect[FINAL_COLLIDERS_NUM];
	bool addedFinalColliders = false;
	bool deletedFinalColliders = false;
	//Textures---------------------------------
	SDL_Texture * starsTx = nullptr;
	SDL_Texture * shipTx = nullptr;
	SDL_Texture * shipPartTx = nullptr;
	SDL_Texture * tilemapTx = nullptr;
	SDL_Texture * bossTx = nullptr;
	
	//Animations------------------------------
	Animation bossAnim;

	//Music-----------------------------------
	Music* lvl5Music = nullptr;
	Sfx * fallShipPartSFX;
	Sfx * fireballSFX;

	//Ship part front-------------------------
	SDL_Rect shipPartRect = { 2, 0, 251, 96 };
	iPoint shipPartPos;
	const int fallSpeed = 1;

	//Fireball front-------------------------
	int fireballFrameCounter;

	//Firebars rear--------------------------
	int firebarsFrameCounter;

	//Ship part rear-------------------------
	SDL_Rect shipRearRect = { 0, 96, 128, 64};

	//Enemies--------------------------------
	Enemy* e_FrontShipTurret = nullptr;
	int redBatsKilled;
	int rotatingTurretsKilled;
};

#endif
