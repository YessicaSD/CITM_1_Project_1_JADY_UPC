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

#define INVINCIBILITY_FRAMES  140

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

	//position-----------------------------------------------------------------------
	position = initPosition;//We set the position (before adding the collider) (note that the intial positions are set in Player1.h and Player2.h)
	//variables----------------------------------------------------------------------
	playerAnimState = PlayerAnimationState::None;
	godMode = false;
	//audios-------------------------------------------------------------------------
	init_sfx = App->audio->LoadSFX("Assets/initial_sfx.wav");
	//collider-----------------------------------------------------------------------
	if (isActive)
	playerCol = App->collision->AddCollider({ position.x, position.y + 2, 24, 8 }, COLLIDER_TYPE::COLLIDER_IGNORE_HIT, this);

	return ret;
}

void ModulePlayer::Reappear() {
	//position-----------------------------------------------------------------------
	position = initPosition;
	//variables----------------------------------------------------------------------
	playerAnimState = PlayerAnimationState::Initial;
	powerupUpgrades = 0;
	currentPowerUp = POWERUP_TYPE::NOPOWERUP;
	isShooting = false;
	shoot = false;
	canMove = false;
	isDying = false;
	isInvincible = true;
	invincibilityFrames = INVINCIBILITY_FRAMES;
	//collider-----------------------------------------------------------------------
	if(playerCol!=nullptr)
	playerCol->type = COLLIDER_TYPE::COLLIDER_GOD;

	else
	playerCol = App->collision->AddCollider({ position.x, position.y + 2, 24, 8 }, COLLIDER_TYPE::COLLIDER_GOD, this);

}

bool ModulePlayer::CleanUp()
{
	powerupUpgrades = 0;
	currentPowerUp = POWERUP_TYPE::NOPOWERUP;
	LOG("Unloading player assets");
	////textures------------------------------------------------------------------
	//App->textures->Unload(PlayerTexture);
	//App->textures->Unload(SpeedAnimationTex);
	//audios-------------------------------------------------------------------------
	App->audio->UnloadSFX(init_sfx);
	return true;
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
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)
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
			if (playerCol != nullptr)
			{
				playerCol->type = COLLIDER_GOD;
				SDL_SetTextureColorMod(PlayerTexture, 255, 255, 150);
				godMode = true;
			}
			
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
	if (playerCol != nullptr) {
		playerCol->SetPos(position.x, position.y + 2); //We update the collider position
	}

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

	switch (playerAnimState)
	{
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.current_frame == 0)
		{
			App->audio->ControlSFX(init_sfx, PLAY_AUDIO);
		}

		if (initAnim.finished == true)
		{
			playerAnimState = PlayerAnimationState::Movement;
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
		if (isInvincible == true) {
			if ((invincibilityFrames/2) % 2 == 0) {
				current_animation = &shipAnimBlack.frames[currentFrame];
			}
			else {
				current_animation = &shipAnim.frames[currentFrame];
			}
			--invincibilityFrames;

			if (invincibilityFrames < 0) {
				isInvincible = false;
				//We change the collider type when spawning if god mode is not active
				if (godMode == false) { playerCol->type = COLLIDER_PLAYER; }
			}
		}
		else {
			current_animation = &shipAnim.frames[currentFrame]; //It set the animation frame 
		}
	
		App->render->Blit(PlayerTexture, position.x, position.y, current_animation);

		break;

	case Death:
		if (deathAnim.finished == true)
		{
			isDying = false;
			deathAnim.Reset();
			playerAnimState = None;
			PlayerDies();
		}
		else if (isDying)
		{
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
	//Particles---------------------------------------------------------------------
	App->particles->AddParticle(App->particles->death_explosion, { (float)position.x, (float)position.y }, { 0 ,0 }, PlayerTexture);

	//Player variables--------------------------------------------------------------
	playerCol->type = COLLIDER_GOD;
	isDying = true;
	canMove = false;
	playerAnimState = PlayerAnimationState::Death;
	//Kill the unit
	currentPowerUp = POWERUP_TYPE::NOPOWERUP;

	if (SDL_GetTicks() % 2)	//Sfx REMEMBER: Improve it for 1.0
		App->audio->ControlSFX(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	else
		App->audio->ControlSFX(App->particles->g_explosion02_1sfx, PLAY_AUDIO);

	KillUnit();
	//Delete player collider--------------------------------------------------------
	
}

void  ModulePlayer::ShotInput()
{
	if (Shoot())
	{
		//- All of them shoot a basic shot
		shoot = true;
		App->particles->AddParticle(App->particles->basicShot, { (float)(position.x + 32), (float)(position.y + 6) }, { 12, 0 }, PlayerTexture, shot_colType, 0);
		//- They have additional shots for some upgrades
		if (currentPowerUp == POWERUP_TYPE::LASER)
		{
			switch (powerupUpgrades)
			{
			case 2:
				//Basic laser
				App->particles->AddParticle(App->particles->Basic_Laser, { (float)(position.x + 32), (float)(position.y + 6)}, {10, 0 }, PlayerTexture, shot_colType, 0);
				break;
			case 3:
				//Laser rings
				App->particles->AddParticle(App->particles->Basic_Laser, { (float)(position.x + 32), (float)(position.y + 6) }, { 10, 0 }, PlayerTexture, shot_colType, 0);
				break;
			}
		}
		if (currentPowerUp == POWERUP_TYPE::HOMING)
		{
			switch (powerupUpgrades)
			{
			case 2:
				//2 missiles on the sides
				break;
			case 3:
				//6 missiles on the sides
				break;
			}
		}
		if (currentPowerUp == POWERUP_TYPE::GROUND)
		{
			switch (powerupUpgrades)
			{
			case 2:
				//Missiles up and down
				break;
			case 3:
				//Missiles up and down that destoy the ground
				break;
			}
		}
		/*	if (isShooting == false) { shoot = true; }
		if (Controllshoot == true) {
		Controllshoot = false;

		}*/
	}

	//Ship fire animation (in front of the ship)
	if (shoot == true)
	{
		//- Laser ship fire. The laser powerup is the only one which has a different animation for the ship fire
		if (currentPowerUp == POWERUP_TYPE::LASER && powerupUpgrades > 1)
		{
			if (ShotLaserBasic.finished == false)
			{
				isShooting = true;
				App->render->Blit(PlayerTexture, position.x + 32, position.y + 3-ShotLaserBasic.GetFrame().h/2, &ShotLaserBasic.GetFrameEx());
			}
			else
			{
				ShotLaserBasic.finished = false;
				isShooting = false;
				shoot = false;
			}
		}

		//- Basic ship fire
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

void ModulePlayer::MovementInput()
{

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
		playerCol->type = COLLIDER_IGNORE_HIT;
		godMode = true;
	}

	
	canMove = false;
	Winposition();
}
