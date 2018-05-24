#include "Application.h"
#include "Enemy_FrontTurret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleParticles.h"
#include "Rotation.h"

Enemy_FrontTurret::Enemy_FrontTurret(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animation-----------------------------------------------
	frontTurretAnim.PushBack({120, 458, 32, 24});
	frontTurretAnim.speed = 1;
	frontTurretAnim.loop = true;
	animation = &frontTurretAnim;
	//Collider------------------------------------------------
	collider = App->collision->AddCollider({ x, y, 32, 24}, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	//Positions-----------------------------------------------
	fixedX = x - App->stage05->spawnPos.x;//We get the x position
	fixedY = y - App->stage05->spawnPos.y;//We get the y position
}

void Enemy_FrontTurret::Move()
{
	//We move the turret with the background
	position.x = App->stage05->spawnPos.x + fixedX;
	position.y = App->stage05->spawnPos.y + fixedY;

	//Shoot
	if (frameCounter >= 88)//88 frames to spawn another row of projectiles
	{
		switch (shotStage)
		{
		case 0:
			LOG("Explosion 1");
			//TO DO: Add explosion
			ShootBall(position, { (int)(cos(angleValue[WNW] + angleSeparation * 0) * shootSpeed), (int)(sin(angleValue[WNW] + angleSeparation * 0) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[WNW] + angleSeparation * 1) * shootSpeed), (int)(sin(angleValue[WNW] + angleSeparation * 1) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[WNW] + angleSeparation * 2) * shootSpeed), (int)(sin(angleValue[WNW] + angleSeparation * 2) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[WNW] + angleSeparation * 3) * shootSpeed), (int)(sin(angleValue[WNW] + angleSeparation * 3) * shootSpeed) });
			shotStage++;
			break;
		case 1:
			LOG("Explosion 2");
			//Only explosion
			//TO DO: Add explosion
			shotStage++;
			break;
		case 2:
			LOG("Explosion 3");
			//TO DO: Add explosion
			ShootBall(position, { (int)(cos(angleValue[NNW] + angleSeparation * 0) * shootSpeed), (int)(sin(angleValue[NNW] + angleSeparation * 0) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[NNW] + angleSeparation * 1) * shootSpeed), (int)(sin(angleValue[NNW] + angleSeparation * 1) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[NNW] + angleSeparation * 2) * shootSpeed), (int)(sin(angleValue[NNW] + angleSeparation * 2) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[NNW] + angleSeparation * 3) * shootSpeed), (int)(sin(angleValue[NNW] + angleSeparation * 3) * shootSpeed) });
			shotStage++;
			break;
		case 3:
			LOG("Explosion 4");
			//TO DO: Add explosion
			ShootBall(position, { (int)(cos(angleValue[N] + angleSeparation * 0) * shootSpeed), (int)(sin(angleValue[N] + angleSeparation * 0) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[N] + angleSeparation * 1) * shootSpeed), (int)(sin(angleValue[N] + angleSeparation * 1) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[N] + angleSeparation * 2) * shootSpeed), (int)(sin(angleValue[N] + angleSeparation * 2) * shootSpeed) });
			ShootBall(position, { (int)(cos(angleValue[N] + angleSeparation * 3) * shootSpeed), (int)(sin(angleValue[N] + angleSeparation * 3) * shootSpeed) });
			shotStage = 0;
			break;
		}
		frameCounter = 0;
	}
	else
	{
		frameCounter++;
	}
}

void Enemy_FrontTurret::ShootBall(iPoint position, iPoint speed)
{
	//Shoot
	App->particles->AddParticle(
		App->particles->orangeBall,
		{ position },
		{ speed },
		App->particles->particlesTx,
		COLLIDER_TYPE::COLLIDER_ENEMY_SHOT,
		0,
		PARTICLE_TYPE::PARTICLE_FOLLOW_BACKGROUND);
}

