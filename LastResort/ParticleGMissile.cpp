#include "Application.h"
#include "ParticleGMissile.h"
#include "ModuleParticles.h"
#include "Particle.h"
#include "ModuleStage05.h"
#include "ModuleUnit.h"



Particle_G_Missile::Particle_G_Missile(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) :Particle(p, position, speed, delay, colType, tex)
{

	collider->damage = 0;
	aceleration = { 0.04f , 0.15f };

	wallDetectorUp    = App->collision->AddCollider({ (int)position.x - centerOffset, (int)position.y - centerOffset - 7 , 16,  7 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
	wallDetectorDown  = App->collision->AddCollider({ (int)position.x - centerOffset, (int)position.y + centerOffset   , 16,  7 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
	wallDetectorLeft  = App->collision->AddCollider({ (int)position.x - centerOffset - 7 ,(int)position.y - centerOffset , 7, 16 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
	wallDetectorRight = App->collision->AddCollider({ (int)position.x + centerOffset,  (int)position.y - centerOffset ,  7  ,16 }, COLLIDER_HIT_DETECTION_WALL, (Module*)App->particles);
}

void Particle_G_Missile::UpdateColliders()
{

	if (collider != nullptr)
		collider->SetPos(position.x - 8, position.y - 8);
	if (wallDetectorUp    != nullptr)
		wallDetectorUp->SetPos(position.x - centerOffset, position.y - centerOffset - 7);
	if (wallDetectorDown  != nullptr)
		wallDetectorDown->SetPos(position.x - centerOffset, position.y + centerOffset);
	if (wallDetectorLeft  != nullptr)
		wallDetectorLeft->SetPos(position.x - centerOffset - 7, position.y - centerOffset);
	if (wallDetectorRight != nullptr)
		wallDetectorRight->SetPos(position.x + centerOffset, position.y - centerOffset);
}

void Particle_G_Missile::Move() {

	UpdateColliders();

	switch (moveState)
	{
	case air_State:
		AirMovement();
		break;
	case ft_State:
		FtMovement();
		break;
	}
};

void Particle_G_Missile::AirMovement()
{
	speed.x -= aceleration.x;

	if (speed.x < 0.0f) {
		speed.x = 0.0f;
	}

	if (flipY == false) {

		speed.y += aceleration.y;

		if (speed.y > 3.9f) {
			speed.y = 3.9f;
		}

	}
	else {
		speed.y -= aceleration.y;

		if (speed.y < -3.9f) {
			speed.y = -3.9f;
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
	switch (moveState)
	{
	case air_State:
		AirOnCollision(c1, c2);
		break;
	case ft_State:
		FtOnCollision(c1, c2);
		break;
	}
}

void Particle_G_Missile::AirOnCollision(Collider* c1, Collider* c2) {

	if (c1 == wallDetectorUp)
	{
		moveState = ft_State;
		followTerrainDir = FollowingTerrainDirection::FTD_right;
		colliderToFollow = c2;
	}
	if (c1 == wallDetectorLeft)
	{
		moveState = ft_State;
		followTerrainDir = FollowingTerrainDirection::FTD_down;
		colliderToFollow = c2;
	}
	if (c1 == wallDetectorDown)
	{
		moveState = ft_State;
		followTerrainDir = FollowingTerrainDirection::FTD_right;
		colliderToFollow = c2;
	}
	if (c1 == wallDetectorRight)
	{
		moveState = ft_State;
		followTerrainDir = FollowingTerrainDirection::FTD_down;
		colliderToFollow = c2;
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
