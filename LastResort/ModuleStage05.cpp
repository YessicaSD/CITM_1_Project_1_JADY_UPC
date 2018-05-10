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


#define SPACESHIP_WIDTH 1423
#define SPACESHIP_HEIGHT 288

Module5lvlScene::Module5lvlScene()
{
	shipRect = { 0,0 , SPACESHIP_WIDTH,SPACESHIP_HEIGHT };

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
	cameraMovement.PushBack(300);                   //Pause   //14  -
	cameraMovement.PushBack({ 1236, -33 }, 588);    //9       //15 
	cameraMovement.PushBack({ 1312, -62 }, 288);    //10      //16
	cameraMovement.PushBack({ 1133, 80 }, 615);     //11      //17 
	cameraMovement.PushBack({ 915, 80 }, 780);      //12      //18  
	cameraMovement.PushBack(900);                   //Pause   //19 
	cameraMovement.PushBack({ 946, 64 }, 72);       //13      //20
	cameraMovement.PushBack(1200);                  //Pause   //21
	cameraMovement.PushBack({ 1108, 182 }, 240);    //14      //22 
}

bool Module5lvlScene::Start()
{
	bool ret = true;

	//provisional-----------------------------
	current_time = 0;
	start_time = SDL_GetTicks();
	//Background ------------------------------------------------------------------
	ScrollState = SCROLL_HORIZONTAL;

	//Enable ---------------------------------------------------------------------
	App->stageFunctionality->Enable();
	App->stageFunctionality->currentStage = this;

	//"Reset ship position when fadetoblackends"----------------------------------
	//App->player1->Reset_Positions();
	//App->player2->Reset_Positions();

	//Texture ---------------------------------------------------------------------------------------------------
	StarsTexture = App->textures->Load("Assets/lvl5/background/backgroundstars.png");
	shipTex = App->textures->Load("Assets/lvl5/background/ship.png");
	//Music -----------------------------------------------------------------------------------------------------
	lvl5Music = App->audio->LoadMUS("Assets/lvl5/07-DON-T-TOUCH-ME-BABY-STAGE-5-1-_-FEAR-STAGE-5-2-_-LEGE.ogg");
	App->audio->ControlMUS(lvl5Music, PLAY_AUDIO);

	//Enemies -------------------------------------------------------------------------------------------------
	//App->enemies->AddEnemy(OSCILATOR, -200, 200);
	return ret;
}

update_status Module5lvlScene::Update()
{
	//provisional-----------------------------
	current_time = SDL_GetTicks() - start_time ;
	//Background stars scroll ----------------------------------------------------------------
	switch (ScrollState)
	{
	case SCROLL_HORIZONTAL:
		
		scroll.x -= 5;
		if (scroll.x <= -SCREEN_WIDTH)
			scroll.x = 0;

		if (scroll.x <= -SCREEN_WIDTH)
			scroll.x = 0;

		/*StarsRect = { scroll.x,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect);*/
		App->render->Blit(StarsTexture, scroll.x, 0, NULL);
		App->render->Blit(StarsTexture, scroll.x + SCREEN_WIDTH, 0, NULL);
		/*StarsRect.x += SCREEN_WIDTH;
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect);*/
		break;
	case SCROLL_UP:
		
		scroll.y += 3;
		scroll.x -= 5;
		if (scroll.x <= -SCREEN_WIDTH)
			scroll.x = 0;

		if (scroll.y >= SCREEN_HEIGHT)
			scroll.y = 0;

		StarsRect = { scroll.x,scroll.y,SCREEN_WIDTH,SCREEN_HEIGHT };
		StarsRect2 = { scroll.x,scroll.y,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect);
		StarsRect.y -= SCREEN_HEIGHT;
		StarsRect2.y -= SCREEN_HEIGHT;
		StarsRect2.x += SCREEN_WIDTH;
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect);
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect2);
			break;
	case SCROLL_DOWN:
		break;

	}
	
	//Spaceship background--------------------------------------------------------------------

	dPoint shipPos = shipOffset - cameraMovement.GetCurrentPosition();

	App->render->Blit(shipTex, shipPos.x, shipPos.y, &shipRect);
	
	if (cameraMovement.movFinished)
	{
		LOG("Move: %i Time: %i  ", cameraMovement.currentMov, current_time);
		start_time = SDL_GetTicks();
	}

	//LOG("ShipPos : x %i y %i", shipPos.x, shipPos.y);
	return UPDATE_CONTINUE;
}

bool Module5lvlScene::CleanUp() {

	LOG("Unloading stage 05 scene");
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(lvl5Music, STOP_AUDIO);
	App->audio->UnloadMUS(lvl5Music);
	//Modules-----------------------------------------------------------------------
	App->stageFunctionality->Disable();
	return true;
}
