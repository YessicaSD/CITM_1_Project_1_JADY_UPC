#include "Application.h"
#include "ParticleGMissile.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "Particle.h"
#include "ModuleStage05.h"
#include "ModuleUnit.h"

#define FRAMES_BTW_EXPLOSION 10;

Particle_G_Missile::Particle_G_Missile(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex)
{
	this->position = position;
	this->anim = p.anim;
	this->speed = speed;
	this->texture = tex;

	aceleration = { 0.04f , 0.15f };
	//Add and update colliders----------------------------------------------------

	collider = App->collision->AddCollider({ (int)position.x - 18, (int)position.y - 18 , 36  , 36 }, colType, (Module*)App->particles);
	wallDetectorUp = App->collision->AddCollider({ (int)position.x - centerOffset, (int)position.y - centerOffset - 7 , 16,  7 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
	wallDetectorDown = App->collision->AddCollider({ (int)position.x - centerOffset, (int)position.y + centerOffset   , 16,  7 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
	wallDetectorLeft = App->collision->AddCollider({ (int)position.x - centerOffset - 7 ,(int)position.y - centerOffset , 7, 16 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
	wallDetectorRight = App->collision->AddCollider({ (int)position.x + centerOffset,  (int)position.y - centerOffset ,  7  ,16 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);

	if (collider != nullptr) {
		collider->damage = 0;
	}

	//Select player target--------------------------------------------------------

	if (colType == COLLIDER_PLAYER_1_SHOT) {

		playerTarget = App->player1;
	}

	else if (colType == COLLIDER_PLAYER_2_SHOT) {
		playerTarget = App->player2;
	}

	//Check powerup upgrade------------------------------------------------------

	switch (playerTarget->powerupUpgrades)
	{
	case 2:
		explosions = 1;
		break;
	case 3:
		explosions = 3;
		break;
	case 4:
		explosions = 5;
		break;
	}

}

void Particle_G_Missile::ExplosionOn() {

	collider->type = playerTarget->shot_colType;
	collider->damage = 20;

}
void Particle_G_Missile::ExplosionOff() {

	collider->type = COLLIDER_IGNORE_HIT;
	collider->damage = 0;
}


void Particle_G_Missile::UpdateColliders()
{

	if (collider != nullptr)
		collider->SetPos((int)position.x - 18, (int)position.y -18);
	if (wallDetectorUp    != nullptr)
		wallDetectorUp->SetPos((int)position.x - centerOffset, (int)position.y - centerOffset - 7);
	if (wallDetectorDown  != nullptr)
		wallDetectorDown->SetPos((int)position.x - centerOffset, (int)position.y + centerOffset);
	if (wallDetectorLeft  != nullptr)
		wallDetectorLeft->SetPos((int)position.x - centerOffset - 7, (int)position.y - centerOffset);
	if (wallDetectorRight != nullptr)
		wallDetectorRight->SetPos((int)position.x + centerOffset, (int)position.y - centerOffset);
}

void Particle_G_Missile::Move() {



	switch (state)
	{
	case thrown_State:
		AirMovement();
		break;
	case terrainExplosions_State:
		FtMovement();
		break;
	case airExplosions_State:
		AireExplosions();
		break;
	}

	UpdateColliders();

};

void  Particle_G_Missile::AireExplosions() {


	if (flipY == false) {
		position.y += 2;
	}
	else {
		position.y -= 2;
	}

	ExplosionOff();

	if (explosionFrames == 0 && explosions != 0) {

		App->particles->AddParticle(App->particles->gM_explosion, { position.x -16, position.y-16}, { 0,0 }, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 0, PARTICLE_FOLLOW_WORLD);
		ExplosionOn();
		explosions -= 1;
		explosionFrames = FRAMES_BTW_EXPLOSION;
	}

	explosionFrames -= 1;

}




void Particle_G_Missile::AirMovement()
{
	speed.x -= aceleration.x;

	if (speed.x < 0.0f) {
		speed.x = 0.0f;
	}

	if (flipY == false) {

		speed.y += aceleration.y;

		if (speed.y > 4.5f) {
			speed.y = 4.5f;
		}

	}
	else {
		speed.y -= aceleration.y;

		if (speed.y < -4.5f) {
			speed.y = -4.5f;
		}
	}

	position += speed;
}

void Particle_G_Missile::FtMovement() {

	switch (followTerrainDir)
	{
		case FTD_up:
			//Set the position
			position.y -= followTerrainSpeed;
			if (ColliderIsOnRight()) { position.x = colliderToFollow->rect.x - centerOffset; }
			else if (ColliderIsOnLeft()) { position.x = colliderToFollow->rect.x + colliderToFollow->rect.w + centerOffset; }
			//Check if it runs out of collider
			if (position.y + centerOffset < colliderToFollow->rect.y)
			{
				if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_right; }
				else if (ColliderIsOnLeft()) { followTerrainDir = FollowingTerrainDirection::FTD_left; }
			}
			break;
		case FTD_down:
			//Set the position
			position.y += followTerrainSpeed;
			if (ColliderIsOnRight()) { position.x = colliderToFollow->rect.x - centerOffset; }
			else if (ColliderIsOnLeft()) { position.x = colliderToFollow->rect.x + colliderToFollow->rect.w + centerOffset; }
			//Check if it runs out of collider
			if (position.y - centerOffset > colliderToFollow->rect.y + colliderToFollow->rect.h)
			{
				if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_right; }
				else if (ColliderIsOnLeft()) { followTerrainDir = FollowingTerrainDirection::FTD_left; }
			}
			break;
		case FTD_left:
			//Set the position
			position.x -= followTerrainSpeed;
			if (ColliderIsAbove()) { position.y = colliderToFollow->rect.y + colliderToFollow->rect.h + centerOffset; }
			else if (ColliderIsBellow()) { position.y = colliderToFollow->rect.y - centerOffset; }
			//Check if it runs out of collider
			if (position.x + centerOffset < colliderToFollow->rect.x)
			{
				if (ColliderIsAbove()) { followTerrainDir = FollowingTerrainDirection::FTD_up; }
				else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_down; }
			}
			break;
		case FTD_right:
			//Set the position
			position.x += followTerrainSpeed;
			if (ColliderIsAbove()) { position.y = colliderToFollow->rect.y + colliderToFollow->rect.h + centerOffset; }
			else if (ColliderIsBellow()) { position.y = colliderToFollow->rect.y - centerOffset; }
			//Check if it runs out of collider
			if (position.x - centerOffset > colliderToFollow->rect.x + colliderToFollow->rect.w)
			{
				if (ColliderIsAbove()) { followTerrainDir = FollowingTerrainDirection::FTD_up; }
				else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_down; }
			}
			break;
		}

	ExplosionOff();

	if (explosionFrames == 0 && explosions != 0) {

		App->particles->AddParticle(App->particles->gM_explosion, position, {0,0}, App->particles->explosionTx, COLLIDER_IGNORE_HIT, 0, PARTICLE_FOLLOW_BACKGROUND);
		ExplosionOn();
		explosions -= 1;
		explosionFrames = FRAMES_BTW_EXPLOSION;
	}

	explosionFrames -= 1;


}


void Particle_G_Missile::Draw()
{
	if (anim.finished) {
		currentAnim = &anim.frames[4];
	}
	else {
		currentAnim = &anim.GetFrameEx();
	}
	
	if (flipY == false)
		App->render->Blit(texture, (int)position.x - 8, (int)position.y - 8, currentAnim);
	else 
		App->render->BlitEx(texture, (int)position.x - 8, (int)position.y - 8, currentAnim, SDL_FLIP_VERTICAL);
}

void Particle_G_Missile::OnCollision(Collider* c1, Collider* c2)
{
	switch (state)
	{
	case thrown_State:
		AirOnCollision(c1, c2);
		break;
	case terrainExplosions_State:
		FtOnCollision(c1, c2);
		break;
	}
}

void Particle_G_Missile::AirOnCollision(Collider* c1, Collider* c2) {



	if (c1 == wallDetectorUp)
	{
		state = terrainExplosions_State;
		followTerrainDir = FollowingTerrainDirection::FTD_right;
		colliderToFollow = c2;
		

	}
	if (c1 == wallDetectorLeft)
	{
		state = terrainExplosions_State;
		followTerrainDir = FollowingTerrainDirection::FTD_down;
		colliderToFollow = c2;
	}
	if (c1 == wallDetectorDown)
	{
		state = terrainExplosions_State;
		followTerrainDir = FollowingTerrainDirection::FTD_right;
		colliderToFollow = c2;
	}
	if (c1 == wallDetectorRight)
	{
		state = terrainExplosions_State;
		followTerrainDir = FollowingTerrainDirection::FTD_down;
		colliderToFollow = c2;
	}

	if (c1 == collider && (c2->type == COLLIDER_ENEMY_HEAVY || c2->type == COLLIDER_ENEMY_LIGHT)) {
		state = airExplosions_State;
		collider->type = COLLIDER_IGNORE_HIT;
		position.x = c2->rect.x;
		position.y = c2->rect.y;
	}

}


void  Particle_G_Missile::FtOnCollision(Collider* c1, Collider* c2) {

	if (c1 == wallDetectorUp)
	{
		//If it was moving up
		if (followTerrainDir == FollowingTerrainDirection::FTD_up && c2 != colliderToFollow)
		{
			if (ColliderIsOnLeft()) { followTerrainDir = FollowingTerrainDirection::FTD_right; }
			else if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_left; }
			colliderToFollow = c2;
		}
	}
	if (c1 == wallDetectorLeft)
	{
		//If it was moving left
		if (followTerrainDir == FollowingTerrainDirection::FTD_left && c2 != colliderToFollow)
		{
			if (ColliderIsAbove()) { followTerrainDir = FollowingTerrainDirection::FTD_down; }
			else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_up; }
			colliderToFollow = c2;
		}
	}
	if (c1 == wallDetectorDown)
	{
		//If it was moving down
		if (followTerrainDir == FollowingTerrainDirection::FTD_down && c2 != colliderToFollow)
		{
			if (ColliderIsOnLeft()) { followTerrainDir = FollowingTerrainDirection::FTD_right; }
			else if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_left; }
			colliderToFollow = c2;
		}
	}
	if (c1 == wallDetectorRight)
	{
		//If it was moving right
		if (followTerrainDir == FollowingTerrainDirection::FTD_right && c2 != colliderToFollow)
		{
			if (ColliderIsAbove()) { followTerrainDir = FollowingTerrainDirection::FTD_down; }
			else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_up; }
			colliderToFollow = c2;
		}
	}
}

bool Particle_G_Missile::ColliderIsOnLeft()
{
	return (colliderToFollow->rect.x + colliderToFollow->rect.w < position.x);
}

bool Particle_G_Missile::ColliderIsOnRight()
{
	return (colliderToFollow->rect.x > position.x);
}

bool Particle_G_Missile::ColliderIsAbove()
{
	return (colliderToFollow->rect.y + colliderToFollow->rect.h < position.y);
}

bool Particle_G_Missile::ColliderIsBellow()
{
	return (colliderToFollow->rect.y > position.y);
}


bool Particle_G_Missile::CheckParticleDeath() {

	

	if (explosions == 0) {
		return true;
	}

	//2- Check if it out of the screen margins
	if (position.x >  SCREEN_WIDTH + DESPAWN_MARGIN_RIGHT ||
		position.x < 0 - DESPAWN_MARGIN_LEFT ||
		position.y > SCREEN_HEIGHT + DESPAWN_MARGIN_DOWN ||
		position.y < 0 - DESPAWN_MARGIN_UP)
	{
		return true;
	}

	return false;
}




Particle_G_Missile::~Particle_G_Missile()
{
	if (collider != nullptr)
		collider->to_delete = true;

	if (wallDetectorUp != nullptr)
		wallDetectorUp->to_delete = true;

	if (wallDetectorDown != nullptr)
		wallDetectorDown->to_delete = true;

	if (wallDetectorLeft != nullptr)
		wallDetectorLeft->to_delete = true;

	if (wallDetectorRight != nullptr)
		wallDetectorRight->to_delete = true;
}
