#include "Player1.h"
#include "Player2.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameTitle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL\include\SDL.h"
#include "ModuleContinue.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleStage02.h"
#include "ModuleStage01.h"
#include "ModuleStage05.h"
#include "ModuleStageFunctionality.h"

Module2lvlScene::Module2lvlScene()
{
	BckSpamRect.x = 0;
	BckSpamRect.y = 35;
	BckSpamRect.w = 80;
	BckSpamRect.h = 68;

	BckSpamRect2.x = 0;
	BckSpamRect2.y = 0;
	BckSpamRect2.w = 80;
	BckSpamRect2.h = 35;
}

bool Module2lvlScene::Start()
{
	
	bool ret = true;
	//Enable
	App->stageFunctionality->Enable();
	App->stageFunctionality->currentStage = this;

	//"Reset ship position when fadetoblackends"----------------------------------
	App->player1->Reset_Positions();
	App->player2->Reset_Positions();

	lvl2Text = App->textures->Load("Assets/lvl2/Background_2.png");
	lvl2ground = App->textures->Load("Assets/lvl2/Foreground_2.png");
	BckSpam= App->textures->Load("Assets/lvl2/Backgroundlvl2Spritesheet.png");
	//audios------------------------------------------------------------------------
	lvl2Music = App->audio->LoadMUS("Assets/lvl2/04-THE-RUINS-OF-METRO-STAGE-2-_-TYRANNICAL-BOSS-2-.ogg");
	App->audio->ControlMUS(lvl2Music, PLAY_AUDIO);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}
update_status Module2lvlScene::Update() {
	int speedcamera = 5;
	float backgroundspeed=0.2f;
	float groundspeed = 0.3f;

	App->render->Blit(lvl2Text, 0, 0, NULL);
	App->render->Blit(lvl2ground, 2000, 0, NULL);

	App->render->Blit(BckSpam, 390, SCREEN_HEIGHT-BckSpamRect.h, &BckSpamRect);
	App->render->Blit(BckSpam, 1450, SCREEN_HEIGHT - BckSpamRect.h, &BckSpamRect);
	App->render->Blit(BckSpam, 1800, SCREEN_HEIGHT - BckSpamRect.h, &BckSpamRect);
	App->render->Blit(BckSpam, 1600, 0, &BckSpamRect2);

	return UPDATE_CONTINUE;
}

bool Module2lvlScene::CleanUp() {

	LOG("Unloading ready scene");
	App->render->camera.x = 0;
	App->player1->Disable();
	App->player2->Disable();

	App->textures->Unload(lvl2Text);
	App->textures->Unload(lvl2ground);
	App->textures->Unload(BckSpam);
	//audios------------------------------------------------------------------------
	App->audio->ControlMUS(lvl2Music, STOP_AUDIO);
	App->audio->UnloadMUS(lvl2Music);

	//Modules-----------------------------------------------------------------------
	App->stageFunctionality->Disable();

	return true;
}