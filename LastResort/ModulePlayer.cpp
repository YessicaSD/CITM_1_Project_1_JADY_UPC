#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleStageFunctionality.h"
#include "ModuleStageClear.h"
#include "ModuleStage01.h"
#include "ModuleUnit.h"
#include "Player1.h"
#include "Player2.h"

ModulePlayer::ModulePlayer() //Constructor 
{
	SpeedAnimation.PushBack({  0, 0,32,31 });
	SpeedAnimation.PushBack({ 32, 0,32,32 });
	SpeedAnimation.PushBack({ 64, 0,32,32 });
	SpeedAnimation.PushBack({ 96, 0,32,32 });
	SpeedAnimation.PushBack({  0,32,32,32 });
	SpeedAnimation.PushBack({ 32,32,32,32 });
	SpeedAnimation.PushBack({ 64,32,32,32 });
	SpeedAnimation.PushBack({ 96,54,32,32 });
	SpeedAnimation.PushBack({ 32,54,32,32 });
	SpeedAnimation.PushBack({  0, 0, 0, 0 });
	SpeedAnimation.speed = 0.2f;
	SpeedAnimation.loop = false;
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start()
{
	bool ret = true;
	LOG("Loading player assets");
	//variables-----------------------------------------------------------------------
	godMode = false;
	isShooting = false;
	shoot = false;
	canMove = false;
	isDying = false;
	shipAnimations = ShipAnimations::Initial;

	//audios-------------------------------------------------------------------------
	init_sfx = App->audio->LoadSFX("Assets/initial_sfx.wav");
	//textures-----------------------------------------------------------------------
	//PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version		
	//SpeedAnimationTex = App->textures->Load("Assets/Powerups/speed.png");


	//colliders----------------------------------------------------------------------
	position = initPosition;//We set the position (before adding the collider) (note that the intial positions are set in Player1.h and Player2.h)
	playerCol = App->collision->AddCollider({ position.x, position.y + 2, 24, 8 }, COLLIDER_TYPE::COLLIDER_PLAYER, this);

	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player assets");
	////textures------------------------------------------------------------------
	//App->textures->Unload(PlayerTexture);
	//App->textures->Unload(SpeedAnimationTex);
	//audios-------------------------------------------------------------------------
	App->audio->UnloadSFX(init_sfx);
	return true;
}

void ModulePlayer::Reappear() {
	playerCol = App->collision->AddCollider({ position.x, position.y + 2, 24, 8 }, COLLIDER_TYPE::COLLIDER_PLAYER, this);
	position = initPosition;
	shipAnimations = ShipAnimations::Initial;
	isShooting = false;
	shoot = false;
	canMove = false;

}


update_status ModulePlayer::PreUpdate()
{
	//Movement-------------------------------------------------------------------------
	if (canMove == true)
		MovementInput();
	//If the movement is not on preupdate, the player will move after the unit, causing weird visual effects

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	PlayerTexture = App->stageFunctionality->PlayerTexture;
	SpeedAnimationTex = App->stageFunctionality->SpeedAnimationTex;
	//Debug Modes----------------------------------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		if (godMode == true)
		{
			//Go back to normal
			playerCol->type = COLLIDER_PLAYER;
			SDL_SetTextureColorMod(PlayerTexture, 255, 255, 255);
			godMode = false;
		}
		else
		{
			//Go to god mode
			playerCol->type = COLLIDER_GOD;
			SDL_SetTextureColorMod(PlayerTexture, 255, 255, 150);
			godMode = true;
		}
	}
	//Shots----------------------------------------------------------------------------
	if (canMove == true) {
		ShotInput();
	}
	//Lock the unit--------------------------------------------------------------------
	if (Lock())
	{
		if (unitLocked == true) { unitLocked = false; }
		else { unitLocked = true; }
	}
	//Collision------------------------------------------------------------------------
	playerCol->SetPos(position.x, position.y + 2); //We update the collider position

	//Ship Animation-------------------------------------------------------------------
	ShipAnimation();

	if (speedPowerup == true)
	{
		App->render->Blit(SpeedAnimationTex, position.x - 32, position.y-9 , &SpeedAnimation.GetCurrentFrame());
		if (SpeedAnimation.current_frame == 9)
		{
			SpeedAnimation.current_frame = 0;
			speedPowerup = false;
		}
	}

	//Winlvl
	if (winlvl)
	{
		Winlvl();
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::ShipAnimation() {

	switch (shipAnimations)
	{
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.current_frame == 0)
		{
			App->audio->ControlSFX(init_sfx, PLAY_AUDIO);
		}

		if (initAnim.finished == true)
		{
			shipAnimations = ShipAnimations::Movement;
			//We change the collider type when spawning if god mode is not active
			if (godMode == false) { playerCol->type = COLLIDER_PLAYER; }
			initAnim.Reset();
			canMove = true;
			break;
		}
		//Draw ship---------------------------------------------------
		if (initAnim.current_frame > 4)
		{
			App->render->Blit(PlayerTexture, position.x + 32 - (current_animation->w), position.y + 6 - (current_animation->h / 2), current_animation);
		}
		else
		{
			App->render->Blit(PlayerTexture, position.x - 40, position.y + 6 - (current_animation->h / 2), current_animation);
		}
		break;

	case Movement:
		//Idle--------------------------------------------------------
		if (yAxis > -transitionLimit && yAxis < transitionLimit)
		{
			currentFrame = Idle;
		}
		//Transitions-------------------------------------------------
		if (yAxis >= transitionLimit && yAxis < MaxLimit)
		{
			currentFrame = TransitionDown;
		}
		if (yAxis <= -transitionLimit && yAxis > -MaxLimit)
		{
			currentFrame = TransitionUp;
		}
		//Maximums---------------------------------------------------
		if (yAxis >= MaxLimit)
		{
			currentFrame = MaxDown;
		}
		if (yAxis <= -MaxLimit)
		{
			currentFrame = MaxUp;
		}
		//Draw ship--------------------------------------------------
		current_animation = &shipAnim.frames[currentFrame]; //It set the animation frame 
		App->render->Blit(PlayerTexture, position.x, position.y, current_animation);

		break;

	case Death:
		if (deathAnim.finished == true)
		{
			isDying = false;
			deathAnim.Reset();
			shipAnimations = None;
			lives -= 1;
			if (lives < 0) {
				isDead = true;
			}
			PlayerDies();
		}
		else if (isDying)
		{
			playerCol->type = COLLIDER_NONE;
			current_animation = &deathAnim.GetFrameEx();
			App->render->Blit(PlayerTexture, position.x + 32 - current_animation->w, position.y + 6 - current_animation->h / 2, current_animation);
		}
		break;

	case None:
		break;


	}
}


void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	//If it collides, it dies
	playerCol->to_delete = true;
	App->particles->AddParticle(App->particles->death_explosion, position.x , position.y , PlayerTexture);
	isDying = true;
	canMove = false;
	shipAnimations = ShipAnimations::Death;
	KillUnit();
}

void  ModulePlayer::ShotInput() {
	//Basic shoot-------------------------------------------------------------------
	if (Shoot())
	{
		if(currentPowerUp == POWERUP_TYPE::NOPOWERUP)
		{
			//Basic shoot
			App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
		}
		if (currentPowerUp == POWERUP_TYPE::LASER)
		{
			switch(powerupUpgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 2:
				//Laser shot
				App->particles->AddParticle(App->particles->Basic_Laser, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 3:
				//Laser shot
				App->particles->AddParticle(App->particles->Basic_Laser, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//Laser rings
				break;
			}
		}
		if (currentPowerUp == POWERUP_TYPE::HOMING)
		{
			switch (powerupUpgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 2:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//2 missiles on the sides
				break;
			case 3:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//6 missiles on the sides
				break;
			}
		}
		if (currentPowerUp == POWERUP_TYPE::GROUND)
		{
			switch (powerupUpgrades)
			{
			case 1:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position. y + 6, PlayerTexture, shot_colType, 0);
				break;
			case 2:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//Missiles up and down
				break;
			case 3:
				//Basic shoot
				App->particles->AddParticle(App->particles->basicShot, position.x + 32, position.y + 6, PlayerTexture, shot_colType, 0);
				//Missiles up and down that destoy the ground
				break;
			}
		}
	/*	if (isShooting == false) { shoot = true; }
		if (Controllshoot == true) {
			Controllshoot = false;

		}*/
	}
	//----------Ship Fire-------------------------------------------
	if (shoot == true) {
		if (currentPowerUp == POWERUP_TYPE::NOPOWERUP)
		{
			if (shotFire.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &shotFire.GetFrameEx());
			}
			else
			{
				shotFire.finished = false;
				isShooting = false;
				shoot = false;
			}
		}
		if (currentPowerUp == POWERUP_TYPE::LASER)
		{
			if (ShotLaserBasic.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &ShotLaserBasic.GetFrameEx());
			}
			else
			{
				shotFire.finished = false;
				isShooting = false;
				shoot = false;
			}
		}
		else
		{
			if (shotFire.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 1, &shotFire.GetFrameEx());
			}
			else
			{
				shotFire.finished = false;
				isShooting = false;
				shoot = false;
			}
		}
		
	}
}




void ModulePlayer::MovementInput() {

	if (MoveLeft() == true) {
		//---------Movement-----------------------------------------------------------
		position.x -= (int)movementSpeed;
		if (position.x < 0 + HORIZONTAL_MARGIN)
		{ position.x = 0 + HORIZONTAL_MARGIN; }
	}
	if (MoveRight() == true) {
		//---------Movement-----------------------------------------------------------
		position.x += (int)movementSpeed;
		if (position.x > SCREEN_WIDTH - playerwidth - HORIZONTAL_MARGIN)
		{ position.x = SCREEN_WIDTH - playerwidth - HORIZONTAL_MARGIN; }
	}
	if (MoveUp() == true) {
		//---------Movement-----------------------------------------------------------
		position.y -= (int)movementSpeed;
		if (position.y < 0 + VERTICAL_MARGIN)
		{ position.y = 0 + VERTICAL_MARGIN; }

		//---------Animation---------------------------------------------------------
		yAxis -= keyPressSpeed;
		//We check that the yAxis doesn't get bellow -1
		if (yAxis < -1) {
			yAxis = -1;
		}
	}

	if (MoveDown() == true) {
		//---------Movement-----------------------------------------------------------
		position.y += (int)movementSpeed;
		if (position.y > SCREEN_HEIGHT - playerheight - VERTICAL_MARGIN)
		{ position.y = SCREEN_HEIGHT - playerheight - VERTICAL_MARGIN; }
			
		//---------Animation---------------------------------------------------------
		yAxis += keyPressSpeed;
		//We check that the yAxis doesn't get above 1
		if (yAxis > 1)
		{
			yAxis = 1;
		}
	}
	//If there isn't any input on the y axis
	if (MoveDown() == false) {
		if (yAxis > 0.1) {
			yAxis -= keyReleaseSpeed;
		}
	}

	if (MoveUp() == false) {
		if (yAxis < -0.1) {
			yAxis += keyReleaseSpeed;
		}
	}
}

void ModulePlayer::Winlvl()
{
	if (godMode == false)
	{
		playerCol->type = COLLIDER_NONE;
		godMode = true;
	}

	
	canMove = false;
	Winposition();
}
