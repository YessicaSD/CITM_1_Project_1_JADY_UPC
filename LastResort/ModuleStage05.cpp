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


Module5lvlScene::Module5lvlScene()
{
	shipRect = { 0,0 , SCREEN_WIDTH,SCREEN_HEIGHT };
}

bool Module5lvlScene::Start()
{
	bool ret = true;

	//App->render->camera.x = -134;
	//App->render->camera.y = 80;

	//Background ------------------------------------------------------------------
	ScrollState = SCROLL_HORIZONTAL;


	//Enable ---------------------------------------------------------------------
	App->stageFunctionality->Enable();
	App->stageFunctionality->currentStage = this;

	//"Reset ship position when fadetoblackends"----------------------------------
	App->player1->Reset_Positions();
	App->player2->Reset_Positions();

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

	//Background stars scroll ----------------------------------------------------------------
	switch (ScrollState)
	{
	case SCROLL_HORIZONTAL:
		scroll.x -= 5;
		if (scroll.x <= -SCREEN_WIDTH)
			scroll.x = 0;

		if (scroll.x <= -SCREEN_WIDTH)
			scroll.x = 0;

		StarsRect = { scroll.x,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect);
		StarsRect.x += SCREEN_WIDTH;
		SDL_RenderCopy(App->render->renderer, StarsTexture, nullptr, &StarsRect);
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
	//App->render->camera.x += 1;
	//shipRect.x = App->render->camera.x;
	//shipRect.y = App->render->camera.y;

	App->render->Blit(shipTex, 0, 0, &shipRect);
	
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
