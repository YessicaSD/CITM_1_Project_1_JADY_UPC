#include "Application.h"
#include "Enemy_FrontTurret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleParticles.h"
#include "Rotation.h"

Enemy_FrontTurret::Enemy_FrontTurret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
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
	if(SDL_GetTicks() >= lastShotTime + 3000)/*(60/88)*1000*///60 = 60FPS. 88 = frames to shoot again. 1000 = 1000 ms is 1 s
	{
		App->particles->orangeBall.speed.x = 1;
		App->particles->orangeBall.speed.y = 1;
		App->particles->AddParticle(App->particles->orangeBall, { position.x, position.y }, { 0 , 0 }, App->particles->ParticleTexture, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, 0, PARTICLE_TYPE::PARTICLE_FOLLOW_BACKGROUND);
		lastShotTime = SDL_GetTicks();
	}
}

