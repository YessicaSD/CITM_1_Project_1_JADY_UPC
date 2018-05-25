#include "Application.h"
#include "Enemy_RearTurret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "Rotation.h"
#include "ModuleParticles.h"

Enemy_RearTurret::Enemy_RearTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animation
	rearTurretRect = { 223, 213, 32, 32 };

	//Position
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;

	//Collider
	collider = App->collision->AddCollider({ x, y, rearTurretRect.w, rearTurretRect.h }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
}

void Enemy_RearTurret::Move()
{
	//MOVEMENT----------------------------------------------
	switch(rearTurretMov)
	{
	case move_static:
		//- Set the position
		position = App->stage05->spawnPos + fixedPos;
		//- Check if it needs to change state
		if (frameCounter >= frameLimitStatic) { rearTurretMov = move_forward; frameCounter = 0; }
		else { frameCounter++; }

		break;
	case move_forward:
		//- Move forward
		fixedPos.x++;
		//- Set the position
		position = App->stage05->spawnPos + fixedPos;
		//- Shoot
		if(frameCounter == 3)//It shoots at the third frame it is advancing
		{
			if(timesMovedForward > 2)//It shoots every 2 times it moves forward
			{
				rearTurretShoot();
				timesMovedForward = 0;
			}
			else
			{
				timesMovedForward++;
			}
		}
		//- Check if it needs to change state
		if (frameCounter >= frameLimitMove) { rearTurretMov = move_backward; frameCounter = 0; }
		else { frameCounter++; }

		break;
	case move_backward:
		//- Move backward
		fixedPos.x--;
		//- Set the position
		position = App->stage05->spawnPos + fixedPos;
		//- Check if it needs to change state
		if (frameCounter >= frameLimitMove) { rearTurretMov = move_static; frameCounter = 0; }
		else { frameCounter++; }

		break;

	}

	LOG("Rear turret position x: %f y %f", position.x, position.y);

	//- Update the collider
	collider->SetPos(position.x - rearTurretRect.w / 2, position.y - rearTurretRect.h / 2);
}

void Enemy_RearTurret::Draw(SDL_Texture * sprites)
{
	//RENDER------------------------------------------------
	App->render->Blit(sprites, position.x - rearTurretRect.w / 2, position.y - rearTurretRect.h / 2, &rearTurretRect);
}

void Enemy_RearTurret::rearTurretShoot()
{
	App->particles->AddParticle(App->particles->orangeBall, { (float)(position.x + rearTurretRect.w / 2), (float)position.y }, { cosf(angleValue[N])   * shootSpeed, sinf(angleValue[N])   * shootSpeed }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);
	App->particles->AddParticle(App->particles->orangeBall, { (float)(position.x + rearTurretRect.w / 2), (float)position.y }, { cosf(angleValue[NNE]) * shootSpeed, sinf(angleValue[NNE]) * shootSpeed }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);
	App->particles->AddParticle(App->particles->orangeBall, { (float)(position.x + rearTurretRect.w / 2), (float)position.y }, { cosf(angleValue[NE])  * shootSpeed, sinf(angleValue[NE])  * shootSpeed }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);
	App->particles->AddParticle(App->particles->orangeBall, { (float)(position.x + rearTurretRect.w / 2), (float)position.y }, { cosf(angleValue[ENE]) * shootSpeed, sinf(angleValue[ENE]) * shootSpeed }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);
	App->particles->AddParticle(App->particles->orangeBall, { (float)(position.x + rearTurretRect.w / 2), (float)position.y }, { cosf(angleValue[E])   * shootSpeed, sinf(angleValue[E])   * shootSpeed }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);
}