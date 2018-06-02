#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadetoBlack.h"
#include "ModuleUnit.h"
#include "ModuleStageFunctionality.h"
#include "ModuleContinue.h"
#include "ModuleReady.h"
#include "Rotation.h"


Player1::Player1() {
	//Initial values------------------------------------------
	initPosition = { 40,74 };
	shot_colType = COLLIDER_PLAYER_1_SHOT;
	
	//Movement animation----------------------------------------
	//----Normal-------------------------------
	shipAnim.PushBack({ 0, 3, 32, 12 });	//0 = UpShip
	shipAnim.PushBack({ 32, 3, 32, 12 });	//1 = MiddleUpShip
	shipAnim.PushBack({ 64, 3, 32, 12 });	//2 = idle
	shipAnim.PushBack({ 96, 3, 32, 12 });	//3 = MiddleDownShip
	shipAnim.PushBack({ 128, 3, 32, 12 });	//4 = DownShip
	//----Black-------------------------------
	shipAnimBlack.PushBack({ 0, 3 - 384, 32, 12 });	    //0 = UpShip
	shipAnimBlack.PushBack({ 32, 3 - 384, 32, 12 });	//1 = MiddleUpShip
	shipAnimBlack.PushBack({ 64, 3 - 384, 32, 12 });	//2 = idle
	shipAnimBlack.PushBack({ 96, 3 - 384, 32, 12 });	//3 = MiddleDownShip
	shipAnimBlack.PushBack({ 128, 3 - 384, 32, 12 });	//4 = DownShip

	//Initial animation-----------------------------------------
	initAnim.PushBack({ 0, 122, 111, 2 });
	initAnim.PushBack({ 0, 124, 117, 3 });
	initAnim.PushBack({ 0, 127, 88, 4 });
	initAnim.PushBack({ 0, 131, 86, 8 });
	//---------------------------------------------------------
	initAnim.PushBack({ 0, 139, 64, 25 });
	initAnim.PushBack({ 0, 164, 64, 25 });
	initAnim.PushBack({ 0, 189, 64, 25 });
	initAnim.PushBack({ 0, 214, 64, 25 });
	initAnim.PushBack({ 64, 139, 64, 25 });
	initAnim.PushBack({ 64, 164, 64, 25 });
	initAnim.PushBack({ 64, 189, 64, 25 });
	initAnim.PushBack({ 64, 214, 64, 25 });
	initAnim.PushBack({ 128, 139, 64, 25 });
	initAnim.PushBack({ 128, 164, 64, 25 });
	initAnim.speed = 0.2f;
	//Death animation-------------------------------------------
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 6; ++j) {
			deathAnim.PushBack({ 55 * i,19 + 17 * j ,55,17 });
		}
	}
	deathAnim.speed = 0.3f;
	//Shot Fire Animation----------------------------------------
	shotFire.PushBack({ 125, 247, 10,9 });
	shotFire.PushBack({ 137, 247, 10,9 });
	shotFire.PushBack({ 125, 258, 13,12 });
	shotFire.speed = 0.2f;
	shotFire.loop = true;
	//Shot fire laser---------------------------------------------
	ShotLaserBasic.PushBack({ 32,288,13,13 });
	ShotLaserBasic.PushBack({ 47,288,15,15 });
	ShotLaserBasic.PushBack({ 64,288,27,9 });
	ShotLaserBasic.PushBack({ 64,305,30,7 });
	ShotLaserBasic.PushBack({ 32,314,31,5 });
	ShotLaserBasic.PushBack({ 32,326,32,3 });
	ShotLaserBasic.PushBack({ 32,321,32,3 });
	ShotLaserBasic.PushBack({ 32,305,30,3 });
	ShotLaserBasic.speed = 0.2f;
	ShotLaserBasic.loop = true;
	
}

void Player1::PlayerDies() {

	if (App->player2->isActive == true) {
		if (lives > 0) {
			--lives;
			Reappear();
		}
		else {
			isActive = false;
		}
	}
	else if (App->ui->uiP2 == uiState::CONTINUE) {

		if (lives > 0) {
			--lives;
			Reappear();
		}
		else {
			isActive = false;
			//Continue
			App->fade->FadeToBlack(App->stageFunctionality->currentStage, App->continueScene, 0.0f);
		}
	}
	else if (App->player2->isActive == false) {

		if (lives > 0) {
			--lives;
			//Ready
			App->fade->FadeToBlack(App->stageFunctionality->currentStage, App->readyScene, 0.0f);
		}
		else {
			isActive = false;
			//Continue
			App->fade->FadeToBlack(App->stageFunctionality->currentStage, App->continueScene, 0.0f);
		}
	}
}

//MOVEMENT INPTUT
bool Player1::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller[0].controller,
		SDL_CONTROLLER_AXIS_LEFTX)<-10000) ;
}

bool Player1::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && MoveLeft()== false || SDL_GameControllerGetAxis(App->input->controller[0].controller,
		SDL_CONTROLLER_AXIS_LEFTX)>10000 && MoveLeft() == false);
}
//We limit MoveRight because if MoveRight and Moveleft are pressed, it goes left

bool Player1::MoveDown()
{
	
	return (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller[0].controller, SDL_CONTROLLER_AXIS_LEFTY)>10000);
}

bool Player1::MoveUp()
{
	
	return (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && MoveDown() == false || SDL_GameControllerGetAxis(App->input->controller[0].controller,
		SDL_CONTROLLER_AXIS_LEFTY)<-10000 && MoveDown() == false);
}
//We limit MoveUp because if MoveUp and MoveDown are pressed, it goes down

//SHOOT INPUT
bool Player1::Shoot()
{
	
	return (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||  App->input->Controller1[SDL_CONTROLLER_BUTTON_B] == KEY_STATE::KEY_DOWN );
}

bool Player1::Charge()
{
	return (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT || App->input->Controller1[SDL_CONTROLLER_BUTTON_B] == KEY_STATE::KEY_REPEAT);
}

bool Player1::ReleaseCharge()
{
	return (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP || App->input->Controller1[SDL_CONTROLLER_BUTTON_B] == KEY_STATE::KEY_UP);
}

bool Player1::Lock()
{
	return (App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN || App->input->Controller1[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_UP);
}


void Player1::Winposition()
{
	if (position.x < 70)
	{
		position.x += SCREEN_SIZE;
	}
	if (position.x > 70)
	{
		position.x -= SCREEN_SIZE;
	}
	if (position.y < 120)
	{
		position.y += SCREEN_SIZE;
	}
	if (position.y > 120)
	{
		position.y -= SCREEN_SIZE;
	}

}

void Player1::KillUnit()
{
	if(App->unit1->IsEnabled())
	{
		App->particles->AddParticle(App->particles->g_explosion02,{App->unit1->position.x, App->unit1->position.y}, { 0 , 0 }, App->particles->g_explosion02.texture, COLLIDER_IGNORE_HIT, 0);//Explosion type REMEMBER: Improve it for 1.0
	}
	App->unit1->currentOrbit = App->unit1->currentTurnAround = angleValue[E];
	App->unit1->Disable();
}