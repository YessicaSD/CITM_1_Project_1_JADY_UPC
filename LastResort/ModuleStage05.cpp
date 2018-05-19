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
	App->ui->currentScene = STAGE_SCENE;

	//Positions--------------------------------------------------------------------------------------------------
	if (currentCheckPoint == 0) {
		cameraMovement.SetMovement(0);
	}
	else 
		cameraMovement.SetMovement(22);

	shipPos = shipOffset - cameraMovement.GetPosition();
	spawnPos.x = (int)shipPos.x;
	spawnPos.y = (int)shipPos.y;

	//Texture ---------------------------------------------------------------------------------------------------
	StarsTexture = App->textures->Load("Assets/lvl5/background/backgroundstars.png");
	shipTex = App->textures->Load("Assets/lvl5/background/ship.png");
	tilemapTex = App->textures->Load("Assets/lvl5/background/final.png");

	//Music -----------------------------------------------------------------------------------------------------
	lvl5Music = App->audio->LoadMUS("Assets/lvl5/07-DON-T-TOUCH-ME-BABY-STAGE-5-1-_-FEAR-STAGE-5-2-_-LEGE.ogg");
	App->audio->ControlMUS(lvl5Music, PLAY_AUDIO);

	//Enemies ---------------------------------------------------------------------------------------------------
	//INFO: We'll calculate the x and y positions based on the position of the ship in Docs>ship.psd
	//- FINAL POSITION ENEMIES
	App->enemies->AddEnemy(FRONT_TURRET, 47, 64);

	App->enemies->AddEnemy(POWERDROPPER, -88, 260, 0, POWERUP_TYPE::HOMING);
	App->enemies->AddEnemy(POWERDROPPER, 180, 280, 0, POWERUP_TYPE::LASER);

	App->enemies->AddEnemy(REDBATS, 250, 270);
	App->enemies->AddEnemy(REDBATS, 275, 270);
	App->enemies->AddEnemy(REDBATS, 300, 270);
	App->enemies->AddEnemy(REDBATS, 325, 270);
	App->enemies->AddEnemy(REDBATS, 325, 270,700,SPEED);

	App->enemies->AddEnemy(REDBATS, 325, -20);
	App->enemies->AddEnemy(REDBATS, 400, -25);
	App->enemies->AddEnemy(REDBATS, 404, -25,800);
	App->enemies->AddEnemy(REDBATS, 404, -25, 1400);
	App->enemies->AddEnemy(REDBATS, 404, -25, 1800);


	/*App->enemies->AddEnemy(REDBATS, 390, -5);*/

	App->enemies->AddEnemy(OUTDOOR_TURRET, 208, 13);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 248, 13);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 288, 13);
	App->enemies->AddEnemy(OUTDOOR_TURRET, 328, 13);
	

	//- TEST ENEMIES
	/*App->enemies->AddEnemy(PINATA, 150, 120);*/
	//App->enemies->AddEnemy(OSCILATOR, 500, 0);


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

	
	//Updates----------------------------------------------------------------------------------------------------//

	//----------Update Points--------------------------------------------

	backgroundPoint = cameraMovement.GetCurrentPosition();
	shipPos = shipOffset - backgroundPoint;
	tunnelPos = tunnelOffset - backgroundPoint;
	spawnPos.x = (int)shipPos.x;
	spawnPos.y = (int)shipPos.y;

	//----------Update CheckPoint----------------------------------------

	if (cameraMovement.currentMov  > 21) 
		currentCheckPoint = 1;
	else 
		currentCheckPoint = 0;

	//----------Update Colliders-----------------------------------------

	for (int i = 0; i < SHIP_COLLIDERS_NUM; ++i)
	{
		shipCollidersCol[i]->SetPos(
			shipCollidersRect[i].x + (int)shipPos.x,
			shipCollidersRect[i].y + (int)shipPos.y);
	}

	//Background----------------------------------------------------------------------------------------------------//

	//----------Stars Scroll----------------------------------------------

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
	
	//----------SpaceShip-------------------------------------------------

	if (cameraMovement.currentMov <= 21)
	{
		App->render->Blit(shipTex, shipPos.x, shipPos.y, &shipRect);
	}
	//----------Final Tilemap--------------------------------------------

	if (cameraMovement.currentMov > 21)
	{
		App->render->Blit(tilemapTex, tunnelPos.x, tunnelPos.y, &tunnelRect);
	}
	


	return UPDATE_CONTINUE;
}

bool Module5lvlScene::CleanUp() {

	LOG("Unloading stage 05 scene");
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(lvl5Music, STOP_AUDIO);
	App->audio->UnloadMUS(lvl5Music);
	//Texture -----------------------------------------------------------------------
	App->textures->Unload(StarsTexture);
	App->textures->Unload(shipTex);
	App->textures->Unload(tilemapTex);
	//Modules-----------------------------------------------------------------------
	App->stageFunctionality->Disable();
	App->ui->currentScene = NONE;
	return true;
}
