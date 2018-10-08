#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleReady.h"
#include "ModuleUI.h"
#include "ModuleContinue.h"

#define MAX_ALPHA 255
#define MIN_ALPHA 0
#define BgAlphaSpeed 2.5f
#define FireAnimBaseSpeed 0.16f
#define FireAnimAddedSpeed 0.03f
#define NumberofFireAnimRects 14
#define NumberofFireSquares 8
#define FinalFireSquare 7

ModuleContinue::ModuleContinue() {
	//Background Rect--------------------------------------------------------------
	background_rect.x = 0;
	background_rect.y = 0;
	background_rect.w = SCREEN_WIDTH;
	background_rect.h = SCREEN_HEIGHT;
	//Continue Rect--------------------------------------------------------------
	continue_rect.x = 0;
	continue_rect.y = 64;
	continue_rect.w = 240;
	continue_rect.h = 32;
	//Number animation-------------------------------------------------------------
	for (int i = 0; i < 10; ++i) {
		if (i < 8)
			numbersAnim.PushBack({ 32 * i, 0, 32, 32 });
		else
			numbersAnim.PushBack({ 32 * (i - 8), 32, 32, 32 });
	}
	//Fire animations----------------------------------------------------------------
	for (int x = 0; x < 8; ++x) {
		for (int i = 0; i < NumberofFireAnimRects; ++i) {
			if (i < 8)
				fireAnim[x].PushBack({ 32 * i, 96, 32, 32 });
			else
				fireAnim[x].PushBack({ 32 * (i - 8), 128, 32, 32 });
		}
		fireAnim[x].speed = FireAnimBaseSpeed + FireAnimAddedSpeed * (7 - x);
	}
}

ModuleContinue:: ~ModuleContinue() {}

bool ModuleContinue::Start() {
	LOG("Loading ModuleContinue assets");
	bool ret = true;
	//variables---------------------------------------------------------------------
	number = 9;
	time_finished = false;
	bgAlpha = MAX_ALPHA;
	rest_bgAlpha = true;
	//-------------Reset players score-----------------------
	App->player1->score = 0;
	App->player2->score = 0;
	//textures-----------------------------------------------------------------------
	backgroundTex = App->textures->Load("Assets/Scenes/Continue/backgrounds.png");
	continueTex = App->textures->Load("Assets/Scenes/Continue/continue.png");
	//audios------------------------------------------------------------------------
	continue_and_go = App->audio->LoadMUS("Assets/Scenes/Continue/continue_and_go.ogg");
	App->audio->ControlAudio(continue_and_go, PLAY_AUDIO);
	//animations--------------------------------------------------------------------
	numbersAnim.current_frame = 9;
	for (int x = 0; x < 8; ++x) {
		fireAnim[x].Reset();
		fireAnim[x].finished = false;
	}
	//UI---------------------------------------------------------------------------
	App->ui->ShowUi();
	App->ui->currentScene = CONTINUE_SCENE;
	return ret;
}

bool ModuleContinue::CleanUp() {
	LOG("Unloading ModuleContinue assets");
	//textures----------------------------------------------------------------------
	App->textures->Unload(backgroundTex);
	App->textures->Unload(continueTex);
	//audios------------------------------------------------------------------------
	if (time_finished == false) {
		App->audio->ControlAudio(continue_and_go, STOP_AUDIO);
		App->audio->UnloadMUS(continue_and_go);
	}
	//UI----------------------------------------------------------------------------
	App->ui->currentScene = NONE;
	App->ui->HideUi();
	return true;
}

update_status ModuleContinue::LogicUpdate() {
	//Background--------------------------------------------------------------------
	if (rest_bgAlpha) {
		bgAlpha = bgAlpha - BgAlphaSpeed;
		if (bgAlpha < MIN_ALPHA) {
			bgAlpha = MIN_ALPHA;
			rest_bgAlpha = false;
		}
		SDL_SetTextureAlphaMod(backgroundTex, bgAlpha);
		App->render->Blit(backgroundTex, 0, 0, &background_rect);
		SDL_SetTextureAlphaMod(backgroundTex, 255);
	}
	else {
		bgAlpha = bgAlpha + BgAlphaSpeed;
		if (bgAlpha > MAX_ALPHA) {
			bgAlpha = MAX_ALPHA;
			rest_bgAlpha = true;
		}
		SDL_SetTextureAlphaMod(backgroundTex, bgAlpha);
		App->render->Blit(backgroundTex, 0, 0, &background_rect);
		SDL_SetTextureAlphaMod(backgroundTex, 255);
	}
	//Fire--------------------------------------------------------------------------
	for (int i = 0; i < NumberofFireSquares; ++i) {

		if (fireAnim[i].finished == false) 
		{
			if (i < NumberofFireSquares - 1)
				App->render->Blit(continueTex, 21 + 32 * i, 96, &fireAnim[i].GetFrameEx());
			else
				App->render->Blit(continueTex, 253, 96, &fireAnim[i].GetFrameEx());
		}

		else if (fireAnim[FinalFireSquare].finished == true )
		{
			fireAnim[i].Reset();
			if (i == FinalFireSquare ) {
				--number;
			}
		}
	}
	//Continue------------------------------------------------------------------------
	App->render->Blit(continueTex, 16, 96, &continue_rect);

	//Number-------------------------------------------------------------------------

	App->render->Blit(continueTex, 256, 96, &numbersAnim.frames[number]);

	//Game Over scene-----------------------------------------------------------------
	if (number < 0) {
		time_finished = true;
		App->fade->FadeToBlack(this, App->gameoverScene, 0.0f);
	}

	//Ready scene---------------------------------------------------------------------

	if (App->player1->isActive == true || App->player2->isActive == true)
	{
		App->fade->FadeToBlack(this, App->readyScene, 0.0f);
	}

	return UPDATE_CONTINUE;
}

