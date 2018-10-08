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

Player2::Player2() {
	//Initial position------------------------------------------
	initPosition = { 40,138 };
	shot_colType = COLLIDER_PLAYER_2_SHOT;
	//Movement animation----------------------------------------
	//----Normal-------------------------------
	shipAnim.PushBack({ 198, 3, 32, 12 });	//0 = UpShip
	shipAnim.PushBack({ 230, 3, 32, 12 });	//1 = MiddleUpShip
	shipAnim.PushBack({ 262, 3, 32, 12 });	//2 = idle
	shipAnim.PushBack({ 294, 3, 32, 12 });	//3 = MiddleDownShip
	shipAnim.PushBack({ 326, 3, 32, 12 });	//4 = DownShip
	//----Black-------------------------------
	shipAnimBlack.PushBack({ 198, 3 - 384, 32, 12 });	    //0 = UpShip
	shipAnimBlack.PushBack({ 230, 3 - 384, 32, 12 });	//1 = MiddleUpShip
	shipAnimBlack.PushBack({ 262, 3 - 384, 32, 12 });	//2 = idle
	shipAnimBlack.PushBack({ 294, 3 - 384, 32, 12 });	//3 = MiddleDownShip
	shipAnimBlack.PushBack({ 326, 3 - 384, 32, 12 });	//4 = DownShip

	//Initial animation-----------------------------------------
	initAnim.PushBack({ 212, 223, 111, 1 });
	initAnim.PushBack({ 212, 226, 117, 3 });
	initAnim.PushBack({ 212, 228, 66, 4 });
	initAnim.PushBack({ 212, 233, 58, 8 });
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			initAnim.PushBack({ 212 + 64 * i, 159 + 25 * j ,64,25 });
		}
	}
	initAnim.speed = 0.15f;
	//Death animation-------------------------------------------
	deathAnim.PushBack({ 221 ,27,32,12 });
	deathAnim.PushBack({ 218 ,43,35,15 });
	deathAnim.PushBack({ 213,61,40,18 });
	deathAnim.PushBack({ 208 ,83 ,45,19 });
	deathAnim.PushBack({ 202 ,104,51,20 });
	//--------------------------------------
	deathAnim.PushBack({ 253 ,19,63,21 });
	deathAnim.PushBack({ 253 ,40,63,22 });
	deathAnim.PushBack({ 253 ,62,63,24 });
	deathAnim.PushBack({ 253 ,86,63,23 });
	deathAnim.PushBack({ 253 ,109,63,23 });
	//-------------------------------------
	deathAnim.PushBack({ 253 ,132,63,24 });
	deathAnim.PushBack({ 316 ,19,60,25 });
	deathAnim.PushBack({ 316 ,44,60,26 });
	deathAnim.PushBack({ 316 ,71,60,25 });
	deathAnim.PushBack({ 316 ,97,60,28 });
	//------------------------------------
	deathAnim.PushBack({ 316 ,125,60,28 });
	deathAnim.PushBack({ 376 ,19,55,17 });
	deathAnim.PushBack({ 376 ,47,55,28 });
	deathAnim.PushBack({ 376 ,75,55,20 });
	deathAnim.speed = 0.35f;
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

void Player2::PlayerDies() {

	if (App->player1->isActive == true) {
		if (lives > 0) {
			--lives;
			Reappear();
		}
		else {
			isActive = false;
		}
	}
	else if (App->ui->uiP1 == uiState::CONTINUE) {

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
	else if (App->player1->isActive == false) {

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

bool Player2::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller[1].controller,SDL_CONTROLLER_AXIS_LEFTX)<-10000);
}

bool Player2::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && MoveLeft()== false || SDL_GameControllerGetAxis(App->input->controller[1].controller, SDL_CONTROLLER_AXIS_LEFTX)>10000 && MoveLeft() == false);
}
//We limit MoveRight because if MoveRight and Moveleft are pressed, it goes left

bool Player2::MoveDown()
{
	return (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller[1].controller, SDL_CONTROLLER_AXIS_LEFTY)>10000);
}

bool Player2::MoveUp()
{
	return (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && MoveDown() == false || SDL_GameControllerGetAxis(App->input->controller[1].controller,SDL_CONTROLLER_AXIS_LEFTY)<-10000 && MoveDown() == false);
}
//We limit MoveUp because if MoveUp and MoveDown are pressed, it goes down

bool Player2::Shoot()
{
	

	return (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || App->input->Controller2[SDL_CONTROLLER_BUTTON_B] == KEY_STATE::KEY_DOWN);
}

bool Player2::Charge()
{
	return (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT || App->input->Controller2[SDL_CONTROLLER_BUTTON_B] == KEY_STATE::KEY_REPEAT);
}

bool Player2::ReleaseCharge()
{
	return (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP || App->input->Controller2[SDL_CONTROLLER_BUTTON_B] == KEY_STATE::KEY_UP);
}

bool Player2::Lock()
{
	return (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN || App->input->Controller2[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_UP);
}

void Player2::Winposition()
{
	if (position.x < 200)
	{
		position.x += SCREEN_SIZE;
	}
	if (position.x > 200)
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


void Player2::KillUnit()
{
	if (App->unit2->IsEnabled())
	{
		App->particles->AddParticle(
			App->particles->g_explosion02,
		    { App->unit2->position.x, App->unit2->position.y },
		    { 0 , 0 },
			App->particles->g_explosion02.texture,
			COLLIDER_IGNORE_HIT,
			0);//Explosion type REMEMBER: Improve it for 1.0
	}
	App->unit2->currentOrbit = App->unit2->currentTurnAround = angleValue[E];
	App->unit2->Disable();
}