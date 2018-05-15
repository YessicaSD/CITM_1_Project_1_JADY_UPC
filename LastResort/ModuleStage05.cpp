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
#include "ModuleStage05.h"
#include "ModuleStage01.h"
#include "ModuleStage02.h"
#include "ModuleStageFunctionality.h"
#include "ModuleEnemies.h"
#include "ModuleUnit.h"
#include "ModuleInput.h"

Module5lvlScene::Module5lvlScene()
{
	shipRect = { 0,0 , 1423,288 };
	tunnelRect = { 0,0 ,875 ,224 };

	cameraMovement.originPoint = { -444, 240 };     //-1      //0
	cameraMovement.PushBack({ -167, 144 }, 330);    //0       //1
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
	
	//Colliders--------------------------------------------------------------------------------------------------
	shipCollidersRect[ 0] = {  304, 208, 507, 16 };
	shipCollidersRect[ 1] = {  239, 188,  65, 20 };
	shipCollidersRect[ 2] = {  175, 174,  64, 14 };
	shipCollidersRect[ 3] = {  125, 160,  50, 14 };
	shipCollidersRect[ 4] = {   31, 110,  94, 50 };
	shipCollidersRect[ 5] = {    0,  99,  31, 11 };
	shipCollidersRect[ 6] = {   20,  82,  49, 17 };
	shipCollidersRect[ 7] = {   69,  64,  38, 18 };
	shipCollidersRect[ 8] = {  107,  53,  34, 11 };
	shipCollidersRect[ 9] = {  141,  29,  37, 23 };
	shipCollidersRect[10] = {  178,  19, 207, 13 };
	shipCollidersRect[11] = {  385,  32,  78, 13 };
	shipCollidersRect[12] = {  412,  45,  35, 20 };
	shipCollidersRect[13] = {  399,  65,  13, 51 };
	shipCollidersRect[14] = {  383, 116,  16, 76 };
	shipCollidersRect[15] = {  399, 140,  13, 24 };
	shipCollidersRect[16] = {  399, 192, 116, 16 };
	shipCollidersRect[17] = {  539, 192,  72, 16 };
	shipCollidersRect[18] = {  635, 192,  24, 16 };
	shipCollidersRect[19] = {  683, 192, 103, 16 };
	shipCollidersRect[20] = {  811, 192,  36, 16 };
	shipCollidersRect[21] = {  847, 124,  16, 68 };
	shipCollidersRect[22] = {  863, 100,   8, 24 };
	shipCollidersRect[23] = {  847,  64,  16, 36 };
	shipCollidersRect[24] = {  543,  47, 304, 17 };
	shipCollidersRect[25] = {  587,  64,  20, 60 };
	shipCollidersRect[26] = {  607,  80,  15, 20 };
	shipCollidersRect[27] = {  587, 124,  35, 20 };
	shipCollidersRect[28] = {  563, 116,  24, 12 };
	shipCollidersRect[29] = {  527, 116,  36, 28 };
	shipCollidersRect[30] = {  511,  96,  32, 20 };
	shipCollidersRect[31] = {  543,  64,  21, 32 };
	shipCollidersRect[32] = {  593,  32, 243, 15 };
	shipCollidersRect[33] = {  836,  17,  30, 15 };
	shipCollidersRect[34] = {  866,   2, 162, 15 };
	shipCollidersRect[35] = { 1028,  16,  44, 16 };
	shipCollidersRect[36] = { 1072,  32, 128, 16 };
	shipCollidersRect[37] = { 1200,  47, 110, 16 };
	shipCollidersRect[38] = { 1310,  63,  80, 16 };
	shipCollidersRect[39] = { 1359,  79,  64, 78 };
	shipCollidersRect[40] = { 1167, 129, 192, 13 };
	shipCollidersRect[41] = { 1231, 142,  64, 15 };
	shipCollidersRect[42] = { 1118, 142,  49, 15 };
	shipCollidersRect[43] = { 1054, 157,  64, 18 };
	shipCollidersRect[44] = { 1040, 175,  14, 37 };
	shipCollidersRect[45] = {  914, 212, 140, 12 };
	shipCollidersRect[46] = {  904, 224,  10, 32 };
	shipCollidersRect[47] = {  914, 256, 124, 21 };
	shipCollidersRect[48] = {  914, 277, 107, 10 };
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

	//Set the spawn pos (if we don't do it, enemies will be inicialized in a incorrect position)----------------
	shipPos = shipOffset;
	spawnPos.x = (int)shipPos.x;
	spawnPos.y = (int)shipPos.y;

	//"Reset ship position when fadetoblackends"----------------------------------
	//App->player1->Reset_Positions();
	//App->player2->Reset_Positions();

	//Texture ---------------------------------------------------------------------------------------------------
	StarsTexture = App->textures->Load("Assets/lvl5/background/backgroundstars.png");
	shipTex = App->textures->Load("Assets/lvl5/background/ship.png");
	tilemapTex = App->textures->Load("Assets/lvl5/background/final.png");

	//Music -----------------------------------------------------------------------------------------------------
	lvl5Music = App->audio->LoadMUS("Assets/lvl5/07-DON-T-TOUCH-ME-BABY-STAGE-5-1-_-FEAR-STAGE-5-2-_-LEGE.ogg");
	App->audio->ControlMUS(lvl5Music, PLAY_AUDIO);

	//Enemies ---------------------------------------------------------------------------------------------------
	//INFO: We'll calculate the x and y positions based on the position of the ship in Docs>ship.psd
	/*App->enemies->AddEnemy(POWERDROPPER, 360, 470, HOMING);*/
	//App->enemies->AddEnemy(POWERDROPPER, 600, 30, LASER);
	//App->enemies->AddEnemy(REDBATS, 658, 25);
	//App->enemies->AddEnemy(REDBATS, 683, 25);
	//App->enemies->AddEnemy(REDBATS, 708, 25);
	//App->enemies->AddEnemy(REDBATS, 733, 25);
	//App->enemies->AddEnemy(REDBATS, 758, 25);
	//App->enemies->AddEnemy(OSCILATOR, 500, 0);
	
	//- FINAL POSITION ENEMIES
	App->enemies->AddEnemy(FRONT_TURRET, 47, 64, 5000, POWERUP_TYPE::NOPOWERUP);

	//- TEST ENEMIES
	//App->enemies->AddEnemy(BASIC, 250, 10, 1000);
	//App->enemies->AddEnemy(OSCILATOR, -47, 470);
	//App->enemies->InstaSpawn(PINATA, 150, 165, POWERUP_TYPE::NOPOWERUP);
	//App->enemies->AddEnemy(PINATA, 150, 140, 0, POWERUP_TYPE::NOPOWERUP);

	//Colliders--------------------------------------------------------------------------------------------------
	for(int i = 0; i < SHIP_COLLIDERS_NUM; ++i)
	{
		shipCollidersCol[i] = App->collision->AddCollider(
		   {shipCollidersRect[i].x + (int)shipPos.x,
			shipCollidersRect[i].y + (int)shipPos.y,
			shipCollidersRect[i].w,
			shipCollidersRect[i].h },
			COLLIDER_TYPE::COLLIDER_WALL);
	}

	return ret;
}

update_status Module5lvlScene::Update()
{
	
	//provisional-----------------------------
	current_time = SDL_GetTicks() - start_time ;
	
	//Background blit-------------------------------------------------------------------------
	scroll.x -= 5;
	scroll.y += cameraMovement.GetCurrentPosition().VectU().y;
	if (scroll.x <= -SCREEN_WIDTH)
		scroll.x = 0;
	if (scroll.y <= -SCREEN_HEIGHT)
	{
		scroll.y = 0;
	}

	App->render->Blit(StarsTexture, scroll.x, -scroll.y, NULL);
	App->render->Blit(StarsTexture, scroll.x+SCREEN_WIDTH,- scroll.y, NULL);
	App->render->Blit(StarsTexture, scroll.x, -scroll.y-SCREEN_HEIGHT, NULL);
	App->render->Blit(StarsTexture, scroll.x + SCREEN_WIDTH,- scroll.y - SCREEN_HEIGHT, NULL);
	//Background--------------------------------------------------------------------
	//------------DebugMode------------------------------------ Change it 
	if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_DOWN) { 
		if (checkPoint > 0) {
			--checkPoint;
			cameraMovement.SetMovement(checkPoint);
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_F10] == KEY_DOWN) { 
		if (checkPoint < 24) {
			++checkPoint;
			cameraMovement.SetMovement(checkPoint);
		}
	}
	//------------Move------------------------------------------
	backgroundPoint = cameraMovement.GetCurrentPosition();
	shipPos = shipOffset - backgroundPoint;
	tunnelPos = tunnelOffset - backgroundPoint;
	//- We update the spawn position----------------------------
	spawnPos.x = (int)shipPos.x;
	spawnPos.y = (int)shipPos.y;

	//-----------Draw-------------------------------------------
	if (cameraMovement.currentMov <= 21)
	{
		App->render->Blit(shipTex, shipPos.x, shipPos.y, &shipRect);
	}
	if (cameraMovement.currentMov > 21)
	{
		App->render->Blit(tilemapTex, tunnelPos.x, tunnelPos.y, &tunnelRect);
	}
	
	//Update colliders (Important: after moving the ship!)------------------------------------
	for (int i = 0; i < SHIP_COLLIDERS_NUM; ++i)
	{
		shipCollidersCol[i] ->SetPos(
			shipCollidersRect[i].x + (int)shipPos.x,
			shipCollidersRect[i].y + (int)shipPos.y);
	}

	return UPDATE_CONTINUE;
}

bool Module5lvlScene::CleanUp() {

	LOG("Unloading stage 05 scene");
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(lvl5Music, STOP_AUDIO);
	App->audio->UnloadMUS(lvl5Music);
	//Texture ---------------------------------------------------------------------------------------------------
	App->textures->Unload(StarsTexture);
	App->textures->Unload(shipTex);
	App->textures->Unload(tilemapTex);
	//Modules-----------------------------------------------------------------------
	App->stageFunctionality->Disable();
	return true;
}
