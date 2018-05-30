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
	SpeedAnimation.PushBack({ 0, 0,32,31 });
	SpeedAnimation.PushBack({ 32, 0,32,32 });
	SpeedAnimation.PushBack({ 64, 0,32,32 });
	SpeedAnimation.PushBack({ 96, 0,32,32 });
	SpeedAnimation.PushBack({ 0,32,32,32 });
	SpeedAnimation.PushBack({ 32,32,32,32 });
	SpeedAnimation.PushBack({ 64,32,32,32 });
	SpeedAnimation.PushBack({ 96,54,32,32 });
	SpeedAnimation.PushBack({ 32,54,32,32 });
	SpeedAnimation.PushBack({ 0, 0, 0, 0 });
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
	shoot = false;
	canMove = false;
	isDying = false;
	isInvincible = true;
	invincibilityFrames = INVINCIBILITY_FRAMES;
	//collider-----------------------------------------------------------------------
	if (playerCol != nullptr)
	{
		playerCol->type = COLLIDER_TYPE::COLLIDER_GOD;
	}
	else
	{
		playerCol = App->collision->AddCollider({ position.x, position.y + 2, 24, 8 }, COLLIDER_TYPE::COLLIDER_GOD, this);
	}
}

bool ModulePlayer::CleanUp()
{
	powerupUpgrades = 0;
	currentPowerUp = POWERUP_TYPE::NOPOWERUP;
	LOG("Unloading player assets");
	return true;
}



update_status ModulePlayer::InputUpdate()
{
	//Movement-------------------------------------------------------------------------
	if (canMove == true)
	{
		PlayerMovement();
	}
	//INFO: If the movement is not on preupdate, the player will move after the unit, causing weird visual effects
	//Collision------------------------------------------------------------------------
	if (playerCol != nullptr)
	{
		playerCol->SetPos(position.x, position.y + 2); //We update the collider position
	}
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::LogicUpdate()
{

	if (canMove == true)
	{
		ShotInput();
	}

	//Winlvl
	if (winlvl)
	{
		Winlvl();
	}

	if (shootLaser)
	{
		if (ShotLaserBasic.finished == false)
		{
			if (ShotLaserBasic.current_frame == 0)
			{
				ShotPosition = position;
				App->particles->AddParticle(App->particles->basicLaser, { (float)(ShotPosition.x + 32), (float)(ShotPosition.y + 6) }, { 10, 0 }, App->stageFunctionality->PlayerTexture, shot_colType, 0);

			}

			if (powerupUpgrades == 3)
			{
				if (LaserCount == 3 || LaserCount == 6 || LaserCount == 9)
				{
					App->particles->AddParticle(App->particles->littleRings, { (float)(ShotPosition.x + 10), (float)(ShotPosition.y + 6) }, { 10, 0 }, App->stageFunctionality->PlayerTexture, shot_colType, 0);
				}

			}
			if (powerupUpgrades >= 4)
			{
				if (LaserCount == 3 || LaserCount == 6 || LaserCount == 9)
				{
					App->particles->AddParticle(App->particles->bigRings, { (float)(ShotPosition.x + 10), (float)(ShotPosition.y + 6) }, { 10, 0 }, App->stageFunctionality->PlayerTexture, shot_colType, 0);
				}
			}
		
			LaserCount += 1;
		}
		else
		{
			ShotLaserBasic.finished = false;
			ShotLaserBasic.current_frame = 0;
			shootLaser = false;
			LaserCount = 0;
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::RenderUpdate2()
{
	//Ship Animation-------------------------------------------------------------------
	ShipAnimation();

	//Speed animation------------------------------------------------------------------
	if (speedPowerup == true)
	{
		App->render->Blit(App->stageFunctionality->SpeedAnimationTex, position.x - 32, position.y - 9, &SpeedAnimation.GetCurrentFrame());
		if (SpeedAnimation.current_frame == 9)
		{
			SpeedAnimation.current_frame = 0;
			speedPowerup = false;
		}
	}

	//Ship fire animation (in front of the ship)---------------------------------------
	if (shoot == true)
	{
		if (shotFire.finished == false)
		{
			App->render->Blit(App->stageFunctionality->PlayerTexture, position.x + 32, position.y + 1, &shotFire.GetFrameEx());
		}
		else
		{
			shotFire.finished = false;
			shoot = false;
		}

	}

	//Laser PowerUp---------------------------------------------------------------------
	if (shootLaser)
	{
		if (ShotLaserBasic.finished == false)
		{
			
			App->render->Blit(App->stageFunctionality->PlayerTexture, position.x + 32, position.y + 5 - ShotLaserBasic.GetFrame().h / 2, &ShotLaserBasic.GetFrameEx());
		
		}
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::ShipAnimation()
{
	switch (playerAnimState)
	{
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.current_frame == 0)
		{
			App->audio->ControlAudio(App->stageFunctionality->init_sfx, PLAY_AUDIO);
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
			App->render->Blit(App->stageFunctionality->PlayerTexture, position.x + 32 - (current_animation->w), position.y + 6 - (current_animation->h / 2), current_animation);
		}
		else
		{
			App->render->Blit(App->stageFunctionality->PlayerTexture, position.x - 40, position.y + 6 - (current_animation->h / 2), current_animation);
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
			if ((invincibilityFrames / 2) % 2 == 0) {
				current_animation = &shipAnimBlack.frames[currentFrame];
			}
			else {
				current_animation = &shipAnim.frames[currentFrame];
			}
			--invincibilityFrames;

			if (invincibilityFrames < 0) {
				isInvincible = false;
				//We change the collider type when spawning if god mode is not active
				if (App->stageFunctionality->godMode == false) { playerCol->type = COLLIDER_PLAYER; }
			}
		}
		else {
			current_animation = &shipAnim.frames[currentFrame]; //It set the animation frame 
		}

		App->render->Blit(App->stageFunctionality->PlayerTexture, position.x, position.y, current_animation);

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
			playerCol->type = COLLIDER_IGNORE_HIT;
			current_animation = &deathAnim.GetFrameEx();
			App->render->Blit(App->stageFunctionality->PlayerTexture, position.x + 32 - current_animation->w, position.y + 6 - current_animation->h / 2, current_animation);
		}
		break;

	case None:
		break;
	}
}


void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	//Particles---------------------------------------------------------------------
	App->particles->AddParticle(App->particles->death_explosion, { (float)position.x, (float)position.y }, { 0 ,0 }, App->stageFunctionality->PlayerTexture);

	//Player variables--------------------------------------------------------------
	isDying = true;
	canMove = false;
	playerAnimState = PlayerAnimationState::Death;
	//Kill the unit
	currentPowerUp = POWERUP_TYPE::NOPOWERUP;

	if (SDL_GetTicks() % 2)	//Sfx REMEMBER: Improve it for 1.0
		App->audio->ControlAudio(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	else
		App->audio->ControlAudio(App->particles->g_explosion02_1sfx, PLAY_AUDIO);

	KillUnit();
	//Delete player collider--------------------------------------------------------

}

void  ModulePlayer::ShotInput()
{
	if (Shoot())
	{
		//- All of them shoot a basic shot
		shoot = true;
		App->particles->AddParticle(App->particles->basicShot, { (float)(position.x + 32), (float)(position.y + 6) }, { 12, 0 }, App->stageFunctionality->PlayerTexture, shot_colType, 0);
		//- They have additional shots for some upgrades
		if (currentPowerUp == POWERUP_TYPE::LASER)
		{
			if (powerupUpgrades>1)
				shootLaser = true;
		}
		if (currentPowerUp == POWERUP_TYPE::HOMING)
		{
			if(powerupUpgrades > 1)
			{
				Particle * p1;
				Particle * p2;
				p1 = App->particles->AddParticle(App->particles->hMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2, 1 }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_H_MISSILE);
				if (p1 != nullptr) { p1->distanceToPlayer = 16; }
				p2 = App->particles->AddParticle(App->particles->hMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2, 1 }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_H_MISSILE);
				if (p2 != nullptr) { p2->distanceToPlayer = -16; }
			}
			if(powerupUpgrades > 2)
			{
				Particle * p3;
				Particle * p4;
				p3 = App->particles->AddParticle(App->particles->hMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2, 1 }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_H_MISSILE);
				if (p3 != nullptr) { p3->distanceToPlayer = 24; }
				p4 = App->particles->AddParticle(App->particles->hMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2, 1 }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_H_MISSILE);
				if (p4 != nullptr) { p4->distanceToPlayer = -24; }
			}
			if(powerupUpgrades > 3)
			{
				Particle * p5;
				Particle * p6;
				p5 = App->particles->AddParticle(App->particles->hMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2, 1 }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_H_MISSILE);
				if (p5 != nullptr) { p5->distanceToPlayer = 32; }
				p6 = App->particles->AddParticle(App->particles->hMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2, 1 }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_H_MISSILE);
				if (p6 != nullptr) { p6->distanceToPlayer = -32; }
			}
		}
		if (currentPowerUp == POWERUP_TYPE::GROUND)
		{
			Particle* p = nullptr;

			
			App->particles->AddParticle(App->particles->groundMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2.8f, 0.0f }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_G_MISSILE);
			p = App->particles->AddParticle(App->particles->groundMissile, { (float)(position.x + 16), (float)(position.y + 6) }, { 2.8f, 0.0f }, App->stageFunctionality->PlayerTexture, shot_colType, 0, PARTICLE_G_MISSILE);

			if (p != nullptr) {
				p->flipY = true;
			}

			//switch (powerupUpgrades)
			//{
			//case 2:
			//	break;
			//case 3:
			//	break;
			//}

		}
	}
}

void ModulePlayer::PlayerMovement()
{

	if (MoveLeft() == true) {
		//---------Movement-----------------------------------------------------------
		position.x -= (int)movementSpeed;
		if (position.x < 0 + HORIZONTAL_MARGIN)
		{
			position.x = 0 + HORIZONTAL_MARGIN;
		}
	}
	if (MoveRight() == true) {
		//---------Movement-----------------------------------------------------------
		position.x += (int)movementSpeed;
		if (position.x > SCREEN_WIDTH - playerwidth - HORIZONTAL_MARGIN)
		{
			position.x = SCREEN_WIDTH - playerwidth - HORIZONTAL_MARGIN;
		}
	}
	if (MoveUp() == true) {
		//---------Movement-----------------------------------------------------------
		position.y -= (int)movementSpeed;
		if (position.y < 0 + VERTICAL_MARGIN)
		{
			position.y = 0 + VERTICAL_MARGIN;
		}

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
		{
			position.y = SCREEN_HEIGHT - playerheight - VERTICAL_MARGIN;
		}

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
	if (App->stageFunctionality->godMode == false)
	{
		playerCol->type = COLLIDER_IGNORE_HIT;
		App->stageFunctionality->godMode = true;
	}

	canMove = false;
	Winposition();
}