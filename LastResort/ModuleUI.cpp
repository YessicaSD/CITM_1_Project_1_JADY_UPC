#include "Globals.h"
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
#include <stdio.h>
#include <string.h>


ModuleUI::ModuleUI() {
	lives_score_p1 = { 0,0,32,16};
	live_score_p2 = { 160,16,40,16};
	pow = { 0,16,96,8};
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
	uiTex = App->textures->Load("Assets/UI.png");
	coinsfx = App->audio->LoadSFX("Assets/General/Fx/001. Coin inserted.wav");
	return ret;
}

bool ModuleUI::CleanUp() {
 	LOG("Unloading Module UI assets");
	//Fonts-------------------------------------------------------------------------
	App->fonts->UnLoad(0);
	//textures----------------------------------------------------------------------
	App->textures->Unload(uiTex);
	//audios------------------------------------------------------------------------
	App->audio->UnloadSFX(coinsfx);
	//------------------------------------------------------------------------------
	return true;
}

update_status  ModuleUI::PreUpdate() { 

	return update_status::UPDATE_CONTINUE;
}


update_status ModuleUI::Update() {
	

	str_score_p1 = new char[MAX_NUMBERS_SCORE];
	str_score_p2 = new char[MAX_NUMBERS_SCORE];
	str_lives_p1 = new char[4];
	str_lives_p2 = new char[4];
	str_credits = new char[11];
	if (p1_isDead && player2 == false)
	{
		p1_isDead = false;
		player1 = false;
		lives_p1 = 2;
		App->fade->FadeToBlack(App->stageFunctionality->currentStage, App->continueScene, 0.1f);
		
	}
	if (p2_isDead && player1 == false)
	{
		p2_isDead = false;
		player2 = false;
		lives_p2 = 2;
		App->fade->FadeToBlack(App->stageFunctionality->currentStage, App->continueScene, 0.1f);

	}
	if (p1_isDead && p2_isDead) {
		p1_isDead = false;
		p2_isDead = false;
		player1 = false;
		player2 = false; 
		lives_p1 = 2;
		lives_p2 = 2;
		App->fade->FadeToBlack(App->stageFunctionality->currentStage, App->continueScene, 0.1f);
		
	}

	snprintf(str_lives_p1, 4 * sizeof(str_lives_p1), "%d", lives_p1);
	snprintf(str_lives_p2, 4 * sizeof(str_lives_p2), "%d", lives_p2);
	snprintf(str_score_p1, 4 * sizeof(str_score_p1), "%d", score_p1);
	snprintf(str_score_p2, 4 * sizeof(str_score_p2), "%d", score_p2);
	if(credits<10)
	snprintf(str_credits, 11, "CREDITS 0%i", credits);
	if(credits>=10)
		snprintf(str_credits, 11, "CREDITS %i", credits);


	if (showUI == true) {
		//Static UI-----------------------------------------------------
		App->render->Blit(uiTex, 16, 16, &lives_score_p1);
		App->render->Blit(uiTex, 256, 16, &live_score_p2);
		App->render->Blit(uiTex, 112, 16, &top);
		App->render->Blit(uiTex, 24, 208, &pow);
		App->render->Blit(uiTex, 184, 208, &pow);	/*App->render->Blit(uiTex, 192, 16, &push_p2, 0.0f);*/ //Remember 1.0

		//Variable UI----------------------------------------------------
		App->fonts->BlitText(48, 24, 0, str_lives_p1);  //lives player 1
		App->fonts->BlitText(264, 24, 0, str_lives_p2); //lives player 2
		//-------------score player 1------------------------------------
		if (score_p1 == 0) {
			App->fonts->BlitText( 72, 16, 0, "00"); 
		}
		else {
			App->fonts->BlitText(88- 8*strlen(str_score_p1) , 16, 0, str_score_p1);
		}
		//-------------score player 2------------------------------------
		if (score_p2 == 0) {
			App->fonts->BlitText(256, 16, 0, "00");
		}
		else {
			App->fonts->BlitText(272 - 8 * strlen(str_score_p2), 16, 0, str_score_p2);
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN )
	{
		App->audio->ControlSFX(coinsfx, PLAY_AUDIO);
		if(credits < 99)
		credits +=1;
	}
	if (App->input->keyboard[SDL_SCANCODE_1] &&
		App->input->keyboard[SDL_SCANCODE_F5] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F6] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F7] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F8] == KEY_IDLE)
	{
		if (player1 == false)
		{
			if (credits > 0)
			{
				player1 = true;
				credits -= 1;
			}
		}
		
	}
	//If we press 2 and we're not debugging
	if (App->input->keyboard[SDL_SCANCODE_2] &&
		App->input->keyboard[SDL_SCANCODE_F5] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F6] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F7] == KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_F8] == KEY_IDLE)
	{
		if (player2 == false)
		{
			if (credits >= 2 && player1==false && Continue==false)
			{
				player1 = true;
				player2 = true;
				credits -= 2;
			}
			else if (credits > 0 && player1 == true)
			{
				player2 = true;
				credits -= 1;
			}
			else if (Continue == true)
			{
				player2 = true;
				credits -= 1;
			}
		}
		
	}
	App->fonts->BlitText(208, 216, 0, str_credits);//credits

	delete[](str_score_p1);
	delete[](str_score_p2);
	delete[](str_lives_p1);
	delete[](str_lives_p2);
	str_score_p1 = nullptr;
	str_score_p2 = nullptr;
	str_lives_p1 = nullptr;
	str_lives_p2 = nullptr;

	return UPDATE_CONTINUE;
}

void ModuleUI::ShowUi() {
	if (showUI == false) {
		showUI = true;
	}
	
}
void ModuleUI::HideUi() {
	if (showUI == true) {
		showUI = false;
	}
}