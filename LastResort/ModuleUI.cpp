
#include "Globals.h"
#include <string> 
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleFadetoBlack.h"
#include "ModuleContinue.h"
#include "ModuleStageFunctionality.h"
#include "ModuleStage05.h"
#include "ModuleReady.h"
#include "ModuleUnit.h"
#include "ModuleGameTitle.h"

using namespace std;

ModuleUI::ModuleUI() {
	lives_score_p1 = { 0,0,32,16};
	live_score_p2 = { 160,16,40,16};
	pow = { 0,16,96,8};
	powBar = { 96, 16, 64, 3 };
	push_p2= { 159,0,96,16 };
	top = { 96,0,63,16};

}
ModuleUI:: ~ModuleUI() {}

bool ModuleUI::Start() {
	LOG("Loading Module UI assets");
	bool ret = true;
	//Fonts-------------------------------------------------------------------------
	App->fonts->Load("Assets/Fonts/blue_chars.png", "0123456789[]ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.,&#", 1); //font id = 0
	//textures----------------------------------------------------------------------
	uiTex = App->textures->Load("Assets/UI/UI.png");
	//audios------------------------------------------------------------------------
	coinsSfx = App->audio->LoadSFX("Assets/Scenes/001. Coin inserted.wav");

	// stageclear------------------------------------------------------------------
	lvlComplitedMusic=App->audio->LoadMUS("Assets/Scenes/StageClear/Stage clear.ogg");

	return ret;
}

bool ModuleUI::CleanUp() {
 	LOG("Unloading Module UI assets");
	//Fonts-------------------------------------------------------------------------
	App->fonts->UnLoad(0);
	//textures----------------------------------------------------------------------
	App->textures->Unload(uiTex);
	//audios------------------------------------------------------------------------
	App->audio->UnloadSFX(coinsSfx);
	//------------------------------------------------------------------------------
	App->audio->UnloadMUS(lvlComplitedMusic);
	return true;
}

update_status  ModuleUI::InputUpdate()
{
	
	//Credits functionality------------------------------------------------------------------------------//
	//-------Add credits-----------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN || App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_DOWN || App->input->Controller1[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN || App->input->Controller2[SDL_CONTROLLER_BUTTON_Y] == KEY_DOWN)
	{
		App->audio->ControlAudio(coinsSfx, PLAY_AUDIO);
		if (credits < 99)
			credits += 1;
	}

	//-------Spawn players--------------------------------------------

	//----------------------1 pressed---------------------
	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN &&
		App->input->keyboard[SDL_SCANCODE_F5] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F6] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F7] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F8] == KEY_IDLE ||
		App->input->Controller1[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN)
	{
		if (App->player1->isActive == false && credits > 0)
		{
			switch (currentScene)
			{
			case TITLE_SCENE:
				credits -= 1;
				HideUi();
				App->player1->isActive = true;
				App->player1->lives = 2;
				break;
			case STAGE_SCENE:
				credits -= 1;
				App->player1->isActive = true;
				App->player1->lives = 2;
				App->player1->Reappear();
				break;
			case CONTINUE_SCENE:
				credits -= 1;
				App->player1->isActive = true;
				HideUi();
				App->player1->lives = 2;
				App->stage05->currentCheckPoint = 0;
				break;
			default:
				LOG("1 default");
				break;
			}
		}
	}
	//----------------------2 pressed---------------------
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN &&
		(App->input->keyboard[SDL_SCANCODE_F5] == KEY_IDLE &&
			App->input->keyboard[SDL_SCANCODE_F6] == KEY_IDLE &&
			App->input->keyboard[SDL_SCANCODE_F7] == KEY_IDLE &&
			App->input->keyboard[SDL_SCANCODE_F8] == KEY_IDLE) ||
			App->input->Controller2[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN)
	{
		switch (currentScene)
		{
		case TITLE_SCENE:
			if (credits >= 2)
			{
				HideUi();
				App->player1->isActive = true;
				App->player2->isActive = true;
				App->player1->lives = 2;
				App->player2->lives = 2;
				credits -= 2;
			}
			break;
		case STAGE_SCENE:
			if (credits > 0 && App->player2->isActive == false)
			{
				App->player2->isActive = true;
				App->player2->lives = 2;
				App->player2->Reappear();

				credits -= 1;
			}
			break;
		case CONTINUE_SCENE:
			if (credits > 0)
			{
				credits -= 1;
				App->player2->isActive = true;
				App->stage05->currentCheckPoint = 0;
			}
			break;
		default:
			LOG("2 default");
			break;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_DOWN)
	{
		stageclear = true;
	}
	
	//-----------------------------------------------------------------------------------------------------------------------------------
	if (stageclear == true)
	{
		StageClearLogic();

		
		
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUI::LogicUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUI::RenderUpdate2()
{
	char const*str_score_p1 = nullptr;
	char const*str_score_p2 = nullptr;
	char const*str_lives_p1 = nullptr;
	char const*str_lives_p2 = nullptr;
	char const*str_credits = nullptr;
	char const *str_debug = nullptr;
	
	string lives_p1 = to_string(App->player1->lives);
	string lives_p2 = to_string(App->player2->lives);
	string score_p1 = to_string(App->player1->score);
	string score_p2 = to_string(App->player2->score);
	string credits_ = to_string(credits);
	string debug;
	
	str_score_p1 = lives_p1.c_str();
	str_score_p2 = lives_p2.c_str();
	str_lives_p1 = score_p1.c_str();
	str_lives_p2 = score_p2.c_str();
	str_credits = credits_.c_str();
	
	if(stageclear==true)
	{
		/*App->render->DrawQuad({ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, 0, 0, 0, currentAlfa);
		if (currentAlfa > 254)
		{
			
		}*/
		StageClearRender();
		

	}

	//Draw UI----------------------------------------------------------------------------------------//
	
	if (showUI)
	{
		//------Common--------------------------------------------------
		
		if (credits < 2) {

			App->fonts->BlitText(208, 216, 0, "CREDIT  0");
			App->fonts->BlitText(280, 216, 0, str_credits);
		}

		else if (credits < 10) {
			App->fonts->BlitText(208, 216, 0, "CREDITS 0");
			App->fonts->BlitText(280, 216, 0, str_credits);
		}

		else {
			App->fonts->BlitText(208, 216, 0, "CREDITS");
			App->fonts->BlitText(272, 216, 0, str_credits);

		}

		if (App->player1->isActive == true || App->player2->isActive == true)
		{
			App->render->Blit(uiTex, 112, 16, &top);
		}
		//------Player 1------------------------------------------------
		if (App->player1->isActive == true)
		{
			//-----------Static UI-----------------------
			App->render->Blit(uiTex, 16, 16, &lives_score_p1);
			App->render->Blit(uiTex, 24, 208, &pow);
			if (App->unit1->IsEnabled())
			{
				powBar.w = (int)(64 * App->unit1->power);
				App->render->Blit(uiTex, 48, 210, &powBar);
			}
			//-----------Variable UI--------------------
			App->fonts->BlitText(48, 24, 0, str_lives_p1);
			if (App->player1->score == 0) {
				App->fonts->BlitText(72, 16, 0, "00");
			}
			else {
				App->fonts->BlitText(88 - 8 * strlen(str_score_p1), 16, 0, str_score_p1);
			}
		}
		//------Player 2----------------------------------------------

		if (App->player2->isActive == true) {

			//-----------Static UI----------------------
			App->render->Blit(uiTex, 256, 16, &live_score_p2);
			App->render->Blit(uiTex, 184, 208, &pow);
			if (App->unit2->IsEnabled())
			{
				powBar.w = (int)(64 * App->unit2->power);
				App->render->Blit(uiTex, 208, 210, &powBar);
			}
			//-----------Variable UI--------------------
			App->fonts->BlitText(264, 24, 0, str_lives_p2); //lives player 2

			if (App->player2->score == 0) {
				App->fonts->BlitText(256, 16, 0, "00");
			}
			else {
				App->fonts->BlitText(272 - 8 * strlen(str_score_p2), 16, 0, str_score_p2);
			}
		}

	//	Debug-------------------------------------------------------
		switch (App->stageFunctionality->debugElem)
		{
		case NOTHING:
			break;
		case SCENES:
			debug = to_string(App->stageFunctionality->selectedScene);
			str_debug = debug.c_str();

			App->fonts->BlitText( SCREEN_WIDTH / 2 - 15 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 45,
				0, "SELECTING SCENE");//15 number of letters in SELECTING SCENE
			App->fonts->BlitText( SCREEN_WIDTH / 2 -  3 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 35,
				0, str_debug);
			break;
		case CHECKPOINTS:
			debug = to_string(App->stageFunctionality->selectedCheckpoint);
			str_debug = debug.c_str();
			App->fonts->BlitText( SCREEN_WIDTH / 2 - 20 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 45,
				0, "SELECTING CHECKPOINT");
			App->fonts->BlitText( SCREEN_WIDTH / 2 -  3 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 35,
				0, str_debug);
			break;
		case ENEMIES:
			debug = to_string(App->stageFunctionality->selectedEnemy);
			str_debug = debug.c_str();
			App->fonts->BlitText( SCREEN_WIDTH / 2 - 15 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 45,
				0, "SELECTING ENEMY");
			App->fonts->BlitText( SCREEN_WIDTH / 2 -  3 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 35,
				0, str_debug);
			break;
		case POWERUPS:
			debug = to_string(App->stageFunctionality->selectedPowerup);
			str_debug = debug.c_str();
			App->fonts->BlitText( SCREEN_WIDTH / 2 - 17 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 45,
				0, "SELECTING POWERUP");
			App->fonts->BlitText( SCREEN_WIDTH / 2 -  3 * App->fonts->GetCharWidth(0) / 2, SCREEN_HEIGHT - 35,
				0, str_debug);
			break;
		}
	}


	

	return UPDATE_CONTINUE;

}

void ModuleUI::ShowUi()
{
	if (showUI == false) { showUI = true; }
	
}
void ModuleUI::HideUi()
{
	if (showUI == true) { showUI = false; }
}



void ModuleUI::StageClearLogic()
{
	if(App->player1->isActive && App->player2->isActive)
		{
		App->player1->winlvl = true;
		App->player2->winlvl = true;
	}
	else
	{
		if(App->player1->isActive)
			App->player1->winlvlsingle = true;
		if (App->player2->isActive)
			App->player2->winlvlsingle = true;
	}
	if (frameCountStageClear >= 300)
	{
		stageclear = false;
		App->player1->winlvl = false;
		App->player2->winlvl = false;
		App->player1->winlvlsingle = false;
		App->player2->winlvlsingle = false;
		frameCountStageClear = 0;
		App->fade->FadeToBlack(App->stage05, App->titleScene, 0.0f);
	}

	if (currentAlfa < 255)
		currentAlfa += 1;
	if (currentAlfa == 253)
	{
		App->audio->ControlAudio(App->stage05->lvl5Music, STOP_AUDIO);
		App->audio->ControlAudio(lvlComplitedMusic, PLAY_AUDIO);
	}



	frameCountStageClear += 1;
}
void ModuleUI::StageClearRender()
{
	App->render->Blit(uiTex, 50, 60, &BGroundStageClear5);
}