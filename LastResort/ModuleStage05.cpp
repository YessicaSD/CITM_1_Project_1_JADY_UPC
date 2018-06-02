#include "ModuleStage05.h"
#include "SDL\include\SDL.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleContinue.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleStage01.h"
#include "ModuleStage02.h"
#include "ModuleStageFunctionality.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleUnit.h"
#include "ModuleInput.h"

Module5lvlScene::Module5lvlScene()
{
	shipRect = { 0,0 , 1423,288 };
	tunnelRect = { 0,0 ,875 ,224 };

	cameraMovement.originPoint = { -444, 240 };     //-1      //0
	cameraMovement.PushBack({ -167, 144 }, 700);    //0       //1
	cameraMovement.PushBack({ 10,144 }, 468);       //1       //2 
	cameraMovement.PushBack(720);                   //Pause   //3  
	cameraMovement.PushBack({ -244,-33 }, 492);     //2       //4  
	cameraMovement.PushBack({ 99,-112 }, 300);      //3       //5 
	cameraMovement.PushBack(480);                   //Pause   //6  
	cameraMovement.PushBack({ 371,-159 }, 780);     //4       //7
	cameraMovement.PushBack({ 371, 0 }, 342);       //5       //8 
	cameraMovement.PushBack({ 578, 0 }, 432);       //6       //9
	cameraMovement.PushBack(900);                   //Pause   //10 
	cameraMovement.PushBack({ 371, 0 }, 418);       //6.5     //11 
	cameraMovement.PushBack({ 371, -128 }, 268);    //7       //12 
	cameraMovement.PushBack({ 874, -128 }, 1500);   //8       //13 
	cameraMovement.PushBack(300);                   //Pause   //14  
	cameraMovement.PushBack({ 1236, -33 }, 588);    //9       //15 
	cameraMovement.PushBack({ 1312, -62 }, 288);    //10      //16
	cameraMovement.PushBack({ 1133, 80 }, 615);     //11      //17 
	cameraMovement.PushBack({ 915, 80 }, 780);      //12      //18  
	cameraMovement.PushBack(900);                   //Pause   //19 
	cameraMovement.PushBack({ 946, 64 }, 72);       //13      //20
	cameraMovement.PushBack(1200);                  //Pause   //21
	cameraMovement.PushBack({ 1108, 182 }, 240);    //14      //22 
	cameraMovement.PushBack(2160);                  //Pause   //23
	cameraMovement.PushBack({ 2151, 182 }, 2160);   //15      //24

	//Animations--------------------------------------------------------------------------------------------------

	bossAnim.PushBack({ 0,0,168, 224 });
	bossAnim.PushBack({ 168,0,168, 224 });
	bossAnim.PushBack({ 168*2,0,168, 224 });
	bossAnim.speed = 0.3f;
	
	//Colliders--------------------------------------------------------------------------------------------------
	shipCollidersRect[ 0] = {  304, 208, 750,  16 };
	shipCollidersRect[ 1] = {  239, 188,  65,  20 };
	shipCollidersRect[ 2] = {  175, 174, 129,  14 };
	shipCollidersRect[ 3] = {  125, 160, 179,  14 };
	shipCollidersRect[ 4] = {   31, 110, 273,  50 };
	shipCollidersRect[ 5] = {    0,  99, 304,  11 };
	shipCollidersRect[ 6] = {   20,  82, 284,  17 };
	shipCollidersRect[ 7] = {   69,  64, 235,  18 };
	shipCollidersRect[ 8] = {  107,  53,  71,  11 };
	shipCollidersRect[ 9] = {  141,  29,  37,  24 };
	shipCollidersRect[10] = {  178,  19, 207,  13 };
	shipCollidersRect[11] = {  178,  32, 285,  13 };
	shipCollidersRect[12] = {  178,  45, 269,  19 };
	shipCollidersRect[13] = {  304,  64, 108,  52 };
	shipCollidersRect[14] = {  304, 116,  95,  76 };
	shipCollidersRect[15] = {  399, 140,  13,  24 };
	shipCollidersRect[16] = {  304, 192, 211,  16 };
	shipCollidersRect[17] = {  539, 192,  72,  16 };
	shipCollidersRect[18] = {  635, 192,  24,  16 };
	shipCollidersRect[19] = {  683, 192, 103,  16 };
	shipCollidersRect[20] = {  811, 192,  52,  16 };
	shipCollidersRect[21] = {  847, 124,  16,  68 };
	shipCollidersRect[22] = {  847,  64,  16,  36 };
	shipCollidersRect[23] = {  543,  47, 320,  17 };
	shipCollidersRect[24] = {  587,  64,  20,  60 };
	shipCollidersRect[25] = {  607,  80,  15,  20 };
	shipCollidersRect[26] = {  587, 124,  35,  20 };
	shipCollidersRect[27] = {  563, 116,  24,  12 };
	shipCollidersRect[28] = {  527, 116,  36,  28 };
	shipCollidersRect[29] = {  511,  96,  76,  20 };
	shipCollidersRect[30] = {  543,  64,  44,  32 };
	shipCollidersRect[31] = {  593,  32, 270,  15 };
	shipCollidersRect[32] = {  836,  17,  27,  15 };
	shipCollidersRect[33] = {  863,   2, 165, 206 };
	shipCollidersRect[34] = { 1028,  16,  44, 141 };
	shipCollidersRect[35] = { 1072,  32, 128,  47 };
	shipCollidersRect[36] = { 1200,  47, 110,  32 };
	shipCollidersRect[37] = { 1310,  63,  80,  16 };
	shipCollidersRect[38] = { 1359,  79,  64,  78 };
	shipCollidersRect[39] = { 1167,  79, 192,  63 }; 
	shipCollidersRect[40] = { 1231, 142,  64,  15 };
	shipCollidersRect[41] = { 1072,  79,  95,  78 };
	shipCollidersRect[42] = { 1028, 157,  90,  18 };
	shipCollidersRect[43] = { 1028, 175,  26,  33 };
	shipCollidersRect[44] = {  863, 224,  51,  32 };
	shipCollidersRect[45] = {  863, 256, 175,  21 };
	shipCollidersRect[46] = {  863, 277, 158,  10 };
	shipCollidersRect[47] = { 1257,  34, 105,  29 };

	finalCollidersRect[0]  = { 1414, 182,  95, 44 };
	finalCollidersRect[1]  = { 1414, 362,  95, 44 };
	finalCollidersRect[2]  = { 1446, 226,  49, 33 };
	finalCollidersRect[3]  = { 1446, 329,  49, 33 };
	finalCollidersRect[4]  = { 1509, 182, 946, 30 };
	finalCollidersRect[5]  = { 1509, 376, 946, 30 };
	finalCollidersRect[6]  = { 2112, 212,  61, 49 };
	finalCollidersRect[7]  = { 2112, 327,  61, 49 };
	finalCollidersRect[8]  = { 2320, 250, 135, 12 };
	finalCollidersRect[9]  = { 2320, 326, 135, 12 };
	finalCollidersRect[10] = { 2350, 212, 105, 38 };
	finalCollidersRect[11] = { 2350, 338, 105, 38 };
	finalCollidersRect[12] = { 2365, 262,  90, 64 };
}

bool Module5lvlScene::Start()
{
	bool ret = true;

	//provisional-----------------------------
	current_time = 0;
	start_time = SDL_GetTicks();

	//Enable ---------------------------------------------------------------------
	App->stageFunctionality->Enable();
	App->stageFunctionality->currentStage = this;
	

	//Positions--------------------------------------------------------------------------------------------------
	if (currentCheckPoint == 0) {
		cameraMovement.SetMovement(0);
	}
	else 
		cameraMovement.SetMovement(22);

	shipPos = shipOffset - cameraMovement.GetPosition();
	spawnPos.x = (int)shipPos.x;
	spawnPos.y = (int)shipPos.y;

	//Reset values that have changed from in last run------------------------------------------------------------
	ResetValues();

	//Texture ---------------------------------------------------------------------------------------------------
	starsTx    = App->textures->Load("Assets/Scenes/lvl5/background/backgroundstars.png");
	shipTx     = App->textures->Load("Assets/Scenes/lvl5/background/ship.png");
	tilemapTx  = App->textures->Load("Assets/Scenes/lvl5/background/final.png");
	shipPartTx = App->textures->Load("Assets/Scenes/lvl5/background/ShipPart.png");
	bossTx     = App->textures->Load("Assets/Scenes/lvl5/background/boss.png");

	//Music -----------------------------------------------------------------------------------------------------
	lvl5Music       = App->audio->LoadMUS("Assets/Scenes/lvl5/07-DON-T-TOUCH-ME-BABY-STAGE-5-1-_-FEAR-STAGE-5-2-_-LEGE.ogg");
	fallShipPartSFX = App->audio->LoadSFX("Assets/Scenes/lvl5/background/shipPartFalling.wav");
	fireballSFX     = App->audio->LoadSFX("Assets/Scenes/lvl5/background/Fireball.wav");

	App->audio->ControlAudio(lvl5Music, PLAY_AUDIO);


	//Enemies ---------------------------------------------------------------------------------------------------
	//INFO: We'll calculate the x and y positions based on the position of the ship in Docs>ship.psd
	//- TEST ENEMIES

	//App->enemies->AddEnemy(PINATA, 140, 140);
	//App->enemies->AddEnemy(PINATA, 150, 150);
	//App->enemies->AddEnemy(PINATA, 130, 130);
	//App->enemies->AddEnemy(OSCILATOR, 500, 0);

	App->enemies->AddEnemy(BOSS_05, 0, 300);
	

	//- FINAL POSITION ENEMIES (in order of appearance on the level)
	App->enemies->AddEnemy(POWERDROPPER, -88, 260, 0, POWERUP_TYPE::LASER); //homing
	App->enemies->AddEnemy(POWERDROPPER, 180, 280, 0, POWERUP_TYPE::LASER);
	
	App->enemies->AddEnemy(REDBATS, 250, 270);
	App->enemies->AddEnemy(REDBATS, 275, 270);
	App->enemies->AddEnemy(REDBATS, 300, 270);
	App->enemies->AddEnemy(REDBATS, 325, 270);
	App->enemies->AddEnemy(REDBATS, 325, 270,750);

	App->enemies->AddEnemy(ROTATING_TURRET, 111, 176);
	App->enemies->AddEnemy(ROTATING_TURRET, 159, 192);
	App->enemies->AddEnemy(ROTATING_TURRET, 207, 209);
	App->enemies->AddEnemy(ROTATING_TURRET, 255, 225);
	App->enemies->AddEnemy(ROTATING_TURRET, 302, 241);

	App->enemies->AddEnemy(FRONT_TURRET, 47, 64);

	App->enemies->AddEnemy(REDBATS, 325, -25);
	App->enemies->AddEnemy(REDBATS, 400, -25);
	App->enemies->AddEnemy(REDBATS, 400, -25,800);
	App->enemies->AddEnemy(REDBATS, 400, -25, 1400);
	App->enemies->AddEnemy(REDBATS, 404, -25, 1900);

	App->enemies->AddEnemy(REDBATS, 404, -80, 4000);
	App->enemies->AddEnemy(REDBATS, 430, -80,0 );
	App->enemies->AddEnemy(REDBATS, 455, -80, 0);
	App->enemies->AddEnemy(REDBATS, 480, -80, 0);
	App->enemies->AddEnemy(REDBATS, 500, -80, 0);
	App->enemies->AddEnemy(REDBATS, 525, -80, 0);

	App->enemies->AddEnemy(OUTDOOR_TURRET, 208, 13);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 248, 13);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 288, 13);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 328, 13);

	App->enemies->AddEnemy(OUTDOOR_TURRET, 1087, 29);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 1119, 29);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 1151, 29);
	App->enemies->AddEnemy(MECH_SPAWNER, 738, 192);

	//This enemy use speed as a parameter of rotation
	App->enemies->AddEnemy(INDOOR_TURRET, 575, 145); //up ->{0,0}
	App->enemies->AddEnemy(INDOOR_TURRET, 527, 193, 0, NOPOWERUP, { 1,0 }); //down
	App->enemies->AddEnemy(INDOOR_TURRET, 624, 193, 0, NOPOWERUP, { 1,0 });
	App->enemies->AddEnemy(INDOOR_TURRET, 672, 193, 0, NOPOWERUP, { 1,0 });
	App->enemies->AddEnemy(INDOOR_TURRET, 800, 193, 0, NOPOWERUP, { 1,0 });
	App->enemies->AddEnemy(INDOOR_TURRET, 511, 128, 0, NOPOWERUP, { 2,0 }); //RIGHT
	App->enemies->AddEnemy(INDOOR_TURRET, 527, 80, 0, NOPOWERUP, { 2,0 }); 
	App->enemies->AddEnemy(INDOOR_TURRET, 431, 81, 0, NOPOWERUP, { 3,0 });//LEFT
	App->enemies->AddEnemy(INDOOR_TURRET, 415, 127, 0, NOPOWERUP, { 3,0 });
	App->enemies->AddEnemy(INDOOR_TURRET, 416, 176, 0, NOPOWERUP, { 3,0 });

	App->enemies->AddEnemy(INDOOR_TURRET_LASER, 616, 112, 0, NOPOWERUP, {3,0});
	App->enemies->AddEnemy(INDOOR_TURRET_LASER, 856, 112, 0, NOPOWERUP, { -3,0 });
	App->enemies->AddEnemy(MISSILE_TURRET, 607, 29);
	App->enemies->AddEnemy(MISSILE_TURRET, 639, 29);

	App->enemies->AddEnemy(MISSILE_TURRET, 911, -3);
	App->enemies->AddEnemy(MISSILE_TURRET, 943, -3);
	App->enemies->AddEnemy(MISSILE_TURRET, 975, -3);

	App->enemies->AddEnemy(IF_SPAWNER, 735, 31);

	App->enemies->AddEnemy(REAR_TURRET, 1357, 41);

	App->enemies->AddEnemy(REDBATS,1616 , 30);
	App->enemies->AddEnemy(REDBATS, 1616, 30,500);
	App->enemies->AddEnemy(REDBATS, 1616, 30, 1000);
	App->enemies->AddEnemy(REDBATS, 1616, 30, 1500);
	App->enemies->AddEnemy(REDBATS, 1616, 30, 2000);

	App->enemies->AddEnemy(PINATA_SPAWNER, 1167, 144);
	App->enemies->AddEnemy(PINATA_SPAWNER, 1295, 144);

	App->enemies->AddEnemy(SHIP_MOTOR, 1119, 225);

	

	//Ship colliders-----------------------------------------------------------------------------------------
	for(int i = 0; i < SHIP_COLLIDERS_NUM - 1; ++i)
	{
		shipCollidersCol[i] = App->collision->AddCollider(
		   {shipCollidersRect[i].x + (int)shipPos.x,
			shipCollidersRect[i].y + (int)shipPos.y,
			shipCollidersRect[i].w,
			shipCollidersRect[i].h },
			COLLIDER_TYPE::COLLIDER_WALL);
	}
	//Different case (it is an enemy heavy type collider)
	shipCollidersCol[47] = App->collision->AddCollider(
	{ shipCollidersRect[47].x + (int)shipPos.x,
		shipCollidersRect[47].y + (int)shipPos.y,
		shipCollidersRect[47].w,
		shipCollidersRect[47].h },
		COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY);

	return ret;
}

update_status Module5lvlScene::LogicUpdate()
{
	//provisional-----------------------------
	current_time = SDL_GetTicks() - start_time ;

	//Stop path debugging
	if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_DOWN)
	{
		if (pauseCamera == false) { pauseCamera = true; }
		else { pauseCamera = false; }
	}
	
	//Updates----------------------------------------------------------------------------------------------------
	//----------Update Points--------------------------------------------

	if (pauseCamera == false)
		backgroundPoint = cameraMovement.GetCurrentPosition();
	else
		backgroundPoint = cameraMovement.GetPosition();

	shipPos = shipOffset - backgroundPoint;
	tunnelPos = tunnelOffset - backgroundPoint;
	bossPos = bossOffSet - backgroundPoint;

	spawnPos.x = (int)shipPos.x;
	spawnPos.y = (int)shipPos.y;

	//- Update game checkpoints (there are only 2, one at the start of the game and the other at the beggining of the asteroids section)
	if (cameraMovement.currentMov  > 21) 
		currentCheckPoint = 1;
	else 
		currentCheckPoint = 0;

	//- The mega checkpoint switch--------------------------------------
	//LOG("Current check point %i", cameraMovement.currentMov);
	switch(cameraMovement.currentMov)
	{
	case 0:
		if(reachedCheckpoint[0] == false)
		{
			reachedCheckpoint[0] = true;
		}
		UpdateShipColliders();

		break;
	case 1:
		if (reachedCheckpoint[1] == false)
		{
			reachedCheckpoint[1] = true;
		}
		UpdateShipColliders();

		break;
	case 2:
		if (reachedCheckpoint[2] == false)
		{
			reachedCheckpoint[2] = true;
		}
		UpdateShipColliders();

		break;
	case 3:
		if (reachedCheckpoint[3] == false)
		{
			reachedCheckpoint[3] = true;
		}
		UpdateShipColliders();
		FireballFrontShip();

		break;
	case 4:
		if (reachedCheckpoint[4] == false)
		{
			redBatsKilled = 0;
			reachedCheckpoint[4] = true;
		}
		UpdateShipColliders();
		FireballFrontShip();

		break;
	case 5:
		if (reachedCheckpoint[5] == false)
		{
			reachedCheckpoint[5] = true;
		}
		UpdateShipColliders();

		break;
	case 6:
		if (reachedCheckpoint[6] == false)
		{
			reachedCheckpoint[6] = true;
		}
		UpdateShipColliders();

		break;
	case 7:
		if (reachedCheckpoint[7] == false)
		{
			reachedCheckpoint[7] = true;
		}
		UpdateShipColliders();

		break;
	case 8:
		if (reachedCheckpoint[8] == false)
		{
			reachedCheckpoint[8] = true;
		}
		UpdateShipColliders();

		break;
	case 9:
		if (reachedCheckpoint[9] == false)
		{
			reachedCheckpoint[9] = true;
		}
		UpdateShipColliders();

		break;
	case 10:
		if (reachedCheckpoint[10] == false)
		{
			reachedCheckpoint[10] = true;
		}
		UpdateShipColliders();

		break;
	case 11:
		if (reachedCheckpoint[11] == false)
		{
			
			reachedCheckpoint[11] = true;
		}
		UpdateShipColliders();

		break;
	case 12:
		if (reachedCheckpoint[12] == false)
		{
			App->enemies->AddEnemy(MISSILE_TURRET, 879, -3);
			
			reachedCheckpoint[12] = true;
		}
		
		UpdateShipColliders();

		break;
	case 13:
		if (reachedCheckpoint[13] == false)
		{
			reachedCheckpoint[13] = true;
		}
		UpdateShipColliders();

		break;
	case 14:
		if (reachedCheckpoint[14] == false)
		{
			redBatsKilled = 0;
			reachedCheckpoint[14] = true;
		}
		UpdateShipColliders();
		FirebarsRearShip();

		break;
	case 15:
		if (reachedCheckpoint[15] == false)
		{
			reachedCheckpoint[15] = true;
		}
		UpdateShipColliders();
		FirebarsRearShip();

		break;
	case 16:
		if (reachedCheckpoint[16] == false)
		{
			
			reachedCheckpoint[16] = true;
		}
		UpdateShipColliders();
		FirebarsRearShip();

		break;
	case 17:
		if (reachedCheckpoint[17] == false)
		{
			redBatsKilled = 0;
			reachedCheckpoint[17] = true;
		}
		UpdateShipColliders();
		FirebarsRearShip();

		break;
	case 18:
		if (reachedCheckpoint[18] == false)
		{
			reachedCheckpoint[18] = true;
		}
		UpdateShipColliders();

		break;
	case 19:
		if (reachedCheckpoint[19] == false)
		{
			reachedCheckpoint[19] = true;
		}
		UpdateShipColliders();

		break;
	case 20:
		if (reachedCheckpoint[20] == false)
		{
			redBatsKilled = 0;
			reachedCheckpoint[20] = true;
		}
		UpdateShipColliders();

		break;
	case 21:
		if (reachedCheckpoint[21] == false)
		{
			reachedCheckpoint[21] = true;
		}
		UpdateShipColliders();

		break;
	case 22:
		if (reachedCheckpoint[22] == false)
		{
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 4000, NOPOWERUP, { -1,1 });
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 4500, NOPOWERUP, { -1.5f,0.5f });

			App->enemies->AddEnemy(REDBATS, 1412, 320, 4500);
			App->enemies->AddEnemy(REDBATS, 1412, 320, 5000);
			App->enemies->AddEnemy(REDBATS, 1412, 320, 5500);
			App->enemies->AddEnemy(REDBATS, 1412, 320, 6000);
			App->enemies->AddEnemy(REDBATS, 1412, 320, 6500);

			App->enemies->AddEnemy(MIDDLE_ASTEROID, 1415, 320, 5500, NOPOWERUP, { -1.5f,0.5f });
			App->enemies->AddEnemy(BIG_ASTEROID, 1415, 294, 7500, NOPOWERUP, { -1.5f,0.5f });

			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 8000, NOPOWERUP, { -1.5f,0.5f });
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 11000, NOPOWERUP, { -1,1 });
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 13000, NOPOWERUP, { -1.5f,0.5f });
			App->enemies->AddEnemy(MIDDLE_ASTEROID, 1400, 275, 13000);
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 13500, NOPOWERUP, { 0.5f,1.5f });
			App->enemies->AddEnemy(POWERDROPPER, 1412, 350, 14000, SPEED, { 0.5f,1.5f });
			App->enemies->AddEnemy(OSCILATOR, 1412, 350, 14000, NOPOWERUP);

			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 15000, NOPOWERUP, { -1.5f,0.5f });
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 15500, NOPOWERUP, { -1,1 });
			App->enemies->AddEnemy(MIDDLE_ASTEROID, 1400, 350, 16000, NOPOWERUP);
			App->enemies->AddEnemy(BIG_ASTEROID, 1400, 260, 17000, NOPOWERUP);
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1350, 182, 17500, NOPOWERUP, { -1.5f,0.5f });
			App->enemies->AddEnemy(OSCILATOR, 1412, 350, 18000, NOPOWERUP);
			App->enemies->AddEnemy(BIG_ASTEROID, 1400, 350, 18000);
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 18000, NOPOWERUP, { -1.0f,1.0f });
			App->enemies->AddEnemy(MIDDLE_ASTEROID, 1400, 220, 18000);
			App->enemies->AddEnemy(POWERDROPPER, 1412, 350, 19000, SPEED);
			App->enemies->AddEnemy(BIG_ASTEROID, 1400, 360, 19000);
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1400, 182, 19000, NOPOWERUP, { -1.0f,1.0f });
			App->enemies->AddEnemy(MIDDLE_ASTEROID, 1400, 220, 20000);
			App->enemies->AddEnemy(BIG_ASTEROID, 1400, 260, 21000);
			App->enemies->AddEnemy(MIDDLE_ASTEROID, 1400, 350, 21000);
			App->enemies->AddEnemy(LITTLE_ASTEROID, 1110, 182, 21000, NOPOWERUP, { 1.5f,0.5f });
			App->enemies->AddEnemy(POWERDROPPER, 1412, 350, 21000, SPEED); 
			//Delete ship colliders
			for(int i = 0; i < SHIP_COLLIDERS_NUM; ++i)
			{
				shipCollidersCol[i]->to_delete = true;
			}
			//Add final part colliders
			for (int i = 0; i < FINAL_COLLIDERS_NUM; ++i)
			{
				finalCollidersCol[i] = App->collision->AddCollider(
				{ finalCollidersRect[i].x + (int)shipPos.x,
					finalCollidersRect[i].y + (int)shipPos.y,
					finalCollidersRect[i].w,
					finalCollidersRect[i].h },
					COLLIDER_TYPE::COLLIDER_WALL);
			}
			reachedCheckpoint[22] = true;
		}

		break;
	case 23:
		if (reachedCheckpoint[23] == false)
		{
			reachedCheckpoint[23] = true;
		}
		UpdateFinalColliders();

		break;
	case 24:
		if (reachedCheckpoint[24] == false)
		{
			reachedCheckpoint[24] = true;
		}
		//Update final part colliders
		UpdateFinalColliders();

		break;
	}
	return UPDATE_CONTINUE;
}

update_status Module5lvlScene::RenderUpdate0()
{
	//----------Stars Scroll----------------------------------------------
	scroll.x -= 10;
	scroll.y += cameraMovement.GetPosition().VectU().y * 2;
	if (scroll.x <= -SCREEN_WIDTH)
		scroll.x = 0;
	if (scroll.y <= -SCREEN_HEIGHT)
	{
		scroll.y = 0;
	}

	App->render->Blit(starsTx, scroll.x, -scroll.y, NULL);
	App->render->Blit(starsTx, scroll.x + SCREEN_WIDTH, -scroll.y, NULL);
	App->render->Blit(starsTx, scroll.x, -scroll.y - SCREEN_HEIGHT, NULL);
	App->render->Blit(starsTx, scroll.x + SCREEN_WIDTH, -scroll.y - SCREEN_HEIGHT, NULL);

	return UPDATE_CONTINUE;
}

update_status Module5lvlScene::RenderUpdate1()
{
	//Background---------------------------------------------------------
	//----------SpaceShip------------------------------------------------
	//----------Ship part------------------------------------------------
	if (cameraMovement.currentMov <= 21)
	{
		RenderShip();
		RenderShipPart();
		ShipRear();
	}
	//----------Final Tilemap--------------------------------------------
	//----------Final Boss-----------------------------------------------
	if (cameraMovement.currentMov > 21)
	{
		App->render->Blit(tilemapTx, tunnelPos.x, tunnelPos.y, &tunnelRect);
		App->render->Blit(bossTx, bossPos.x, bossPos.y, &bossAnim.LoopAnimation());
	}
	return UPDATE_CONTINUE;
}

bool Module5lvlScene::CleanUp() {

	LOG("Unloading stage 05 scene");
	//delete collider if they haven't been deleted during the game------------------
	for (int i = 0; i < SHIP_COLLIDERS_NUM; ++i)
	{
		if(shipCollidersCol[i] != nullptr)
		{
			shipCollidersCol[i]->to_delete = true;
		}
	}
	//Add final part colliders
	for (int i = 0; i < FINAL_COLLIDERS_NUM; ++i)
	{
		if(finalCollidersCol[i] != nullptr)
		{
			finalCollidersCol[i]->to_delete = true;
		}
		
	}
	//audios------------------------------------------------------------------------
	App->audio->ControlAudio(lvl5Music, STOP_AUDIO);
	App->audio->UnloadMUS(lvl5Music);
	App->audio->UnloadSFX(fallShipPartSFX);
	App->audio->UnloadSFX(fireballSFX);
	//Texture -----------------------------------------------------------------------
	App->textures->Unload(starsTx);
	App->textures->Unload(shipTx);
	App->textures->Unload(tilemapTx);
	App->textures->Unload(shipPartTx);
	//Modules-----------------------------------------------------------------------
	App->stageFunctionality->Disable();
	App->ui->currentScene = NONE;
	return true;
}

void Module5lvlScene::ResetValues()
{
	shipPartPos = { 63, 160 };
	fireballFrameCounter = 0;
	redBatsKilled = 0;
	rotatingTurretsKilled = 0;

	for(int i = 0; i < CHECKPOIN_NUMBER; ++i)
	{
		reachedCheckpoint[i] = false;
	}
}

void Module5lvlScene::RenderShipPart()
{
	App->render->Blit(shipPartTx, spawnPos.x + shipPartPos.x, spawnPos.y + shipPartPos.y, &shipPartRect);
	if (rotatingTurretsKilled >= 5)
	{
		//HERE
		//if (fallShipPartSFX.hasPlayed == false)
		//{
		//	App->audio->ControlAudio(fallShipPartSFX.sfx, PLAY_AUDIO);
		//	fallShipPartSFX.hasPlayed = true;
		//}
		shipPartPos.y += fallSpeed;
	}
}

void Module5lvlScene::RenderShip()
{
	App->render->Blit(shipTx, shipPos.x, shipPos.y, &shipRect);
}

void Module5lvlScene::UpdateShipColliders()
{
	for (int i = 0; i < SHIP_COLLIDERS_NUM; ++i)
	{
		shipCollidersCol[i]->SetPos(
			shipCollidersRect[i].x + (int)shipPos.x,
			shipCollidersRect[i].y + (int)shipPos.y);
	}
}

void Module5lvlScene::UpdateFinalColliders()
{
	for (int i = 0; i < FINAL_COLLIDERS_NUM; ++i)
	{
		finalCollidersCol[i]->SetPos(
			finalCollidersRect[i].x + (int)shipPos.x,
			finalCollidersRect[i].y + (int)shipPos.y);
	}
}

void Module5lvlScene::FireballFrontShip()
{
	if (fireballFrameCounter >= 72)
	{
		App->particles->AddParticle(App->particles->fireBall, { (float)spawnPos.x + 45, (float)spawnPos.y + 129 }, { -3, 0 }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, 0, PARTICLE_FIREBALL);
		App->audio->ControlAudio(fireballSFX, PLAY_AUDIO);
		fireballFrameCounter = 0;
	}
	else
	{
		fireballFrameCounter++;
	}
}

void Module5lvlScene::ShipRear()
{
	App->render->Blit(shipPartTx, spawnPos.x + 1246, spawnPos.y + 15, &shipRearRect);
}

void Module5lvlScene::FirebarsRearShip()
{
	if (firebarsFrameCounter >= 120)
	{
		App->particles->AddParticle(App->particles->fireBar, { (float)spawnPos.x + 1422, (float)spawnPos.y +  99 }, { 4, 0 }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, 0, PARTICLE_FOLLOW_BACKGROUND);
		App->particles->AddParticle(App->particles->fireBar, { (float)spawnPos.x + 1422, (float)spawnPos.y + 138 }, { 4, 0 }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, 0, PARTICLE_FOLLOW_BACKGROUND);
		//App->audio->ControlAudio(, PLAY_AUDIO);//PLAY FIREBARS AUDIO
		firebarsFrameCounter = 0;
	}
	else
	{
		firebarsFrameCounter++;
	}
}