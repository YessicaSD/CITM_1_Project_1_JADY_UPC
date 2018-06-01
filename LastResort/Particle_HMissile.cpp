#include "Application.h"
#include "Particle.h"
#include "Particle_HMissile.h"
#include "ModuleStage05.h"

Particle_HMissile::Particle_HMissile() : Particle()
{
	
}

Particle_HMissile::Particle_HMissile(Particle& p, fPoint position, fPoint speed, Uint32 delay, COLLIDER_TYPE colType, SDL_Texture* tex) : Particle(p, position, speed, delay, colType, tex)
{
	//Set up variables
	hmissilePhase = steppingOut;
	frameCounter = 0;

	//Calculate variables
	largestPossibleDistance = sqrt(pow(SCREEN_HEIGHT, 2) + pow(SCREEN_WIDTH, 2));
	missilePartRect = { 0, 0, 14, 6 };
	hitDetectionRect = { 0, 0, SCREEN_WIDTH, 100};


	//Animation
	steppingOutAnim.PushBack({ 408, 247, 23,  6 });
	steppingOutAnim.PushBack({ 424, 254, 27,  8 });
	steppingOutAnim.PushBack({ 332, 263, 29, 10 });
	steppingOutAnim.PushBack({ 363, 264, 30, 14 });
	steppingOutAnim.speed = 0.5f;
	steppingOutAnim.loop = true;

	movingAnim.PushBack({ 332, 255, 44,  8 });
	movingAnim.PushBack({ 378, 254, 44,  8 });
	movingAnim.PushBack({ 332, 247, 74,  6 });
	movingAnim.PushBack({ 395, 264, 30, 16 });
	movingAnim.speed = 0.5f;
	movingAnim.loop = true;

	anim = steppingOutAnim;
	currentFrame = anim.GetCurrentFrame();

	//Colliders
	collider = App->collision->AddCollider({ (int)position.x - missilePartRect.w, (int)position.y - missilePartRect.h / 2,  missilePartRect.w, missilePartRect.h }, colType, (Module*)App->particles);
}

//PHASE 1: Moving to position (stepping out)
//PHASE 2: Go forward

void Particle_HMissile::Move()
{
	//In this way we don't calculate the steppingOutSpeed every frame (it's unnecessary)
	//We would ideally do this in the constructor, but we don't have the information about the playerDistance there yet (it is associated later)
	if(firstFrame)
	{
		if (position.y < position.y + distanceToPlayer) { steppingOutSpeed = 1; }
		else { steppingOutSpeed = -1; }
		firstFrame = false;
	}

	//Get the current frame (we need it to adjust the position)
	currentFrame = anim.GetCurrentFrame();

	switch(hmissilePhase)
	{
	case steppingOut:
		//Moves out from the player
		position.y += steppingOutSpeed;

		//Change when it has stopped stepping out
		if(frameCounter >= distanceToPlayer / steppingOutSpeed)//Frames it will take to get to that position
		{
			hmissilePhase = movingForward;
			enemyDetectionCol = App->collision->AddCollider({ (int)position.x, (int)position.y - hitDetectionRect.h / 2, hitDetectionRect.w, hitDetectionRect.h }, COLLIDER_HIT_DETECTION_ENEMY, (Module*)App->particles);
			anim = movingAnim;
			frameCounter = 0;
		}
		else
		{
			frameCounter++;
		}

		break;
	case movingForward:
		//Moves straight
		position.x += speed.x;

		//Checks if there is an enemy in range
		if (distanceToTarget < largestPossibleDistance)
		{
			//Moves there
			if (position.y < targetPos.y)
			{
				//Move up
				if (position.y - speed.y < targetPos.y) { position.y -= speed.y; }
				else { position.y = targetPos.y; }

			}
			else if (position.y > targetPos.y)
			{
				//Move down
				if (position.y + speed.y > targetPos.y) { position.y += speed.y; }
				else { position.y = targetPos.y; }
			}
			//else if (position.y == targetPos.y) { Do nothing }
		}

		//Set up the distance for the next frame
		distanceToTarget = largestPossibleDistance;

		//Update enemy hit detection collider
		if(enemyDetectionCol != nullptr)
		{
			enemyDetectionCol->SetPos((int)position.x, (int)position.y - hitDetectionRect.h / 2);
		}
		break;
	}

	//Update missile collider
	if(collider != nullptr)
	{
		collider->SetPos((int)position.x - missilePartRect.w, (int)position.y - missilePartRect.h / 2);
	}
};

void Particle_HMissile::Draw()
{
	//Render
	App->render->Blit(texture, position.x - currentFrame.w, position.y - currentFrame.h / 2, &currentFrame);
}

void Particle_HMissile::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == enemyDetectionCol)
	{
		OnCollisionHitDetection(c1, c2);
	}
	else if (c1 == collider)
	{
		OnCollisionParticle(c1, c2);
	}
}

bool Particle_HMissile::CheckParticleDeath()
{
	//If it collides with something
	if(destroyMissile)
	{
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

void Particle_HMissile::OnCollisionHitDetection(Collider* c1, Collider* c2)
{
	//Calculate the distance from the current point to the collider
	float distanceToEnemy;
	
	distanceToEnemy = sqrt(pow(position.x - (c2->rect.x + c2->rect.w / 2), 2) + pow(position.y - (c2->rect.y + c2->rect.h / 2), 2));

	if (distanceToEnemy < distanceToTarget)
	{
		distanceToTarget = distanceToEnemy;
	}
}

void Particle_HMissile::OnCollisionParticle(Collider* c1, Collider* c2)
{
	// Add the collision particle where it collided
	if (collision_fx != nullptr)
	{
		App->particles->AddParticle(*collision_fx, { position.x, position.y }, { 0 , 0 }, App->particles->particlesTx);
	}

	destroyMissile = true;
}

Particle_HMissile::~Particle_HMissile()
{
	if(collider != nullptr){
		collider->to_delete = true;
	}

	if(enemyDetectionCol != nullptr){
		enemyDetectionCol->to_delete = true;
	}
}