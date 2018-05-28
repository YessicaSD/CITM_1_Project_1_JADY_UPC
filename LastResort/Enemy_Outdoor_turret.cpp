#include "Application.h"
#include "Enemy_Outdoor_turret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

Enemy_Outdoor_turret::Enemy_Outdoor_turret(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	OutdoorTurretAnim.PushBack({152,156,24,20});
	OutdoorTurretAnim.loop = true;
	animation = &OutdoorTurretAnim;
	initalPosition.x = x-App->stage05->spawnPos.x;
	initalPosition.y = y-App->stage05->spawnPos.y;
	collider = App->collision->AddCollider({ x, y+3, 24, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	StartTime = SDL_GetTicks();
	//Particle ------------------------------------------------------------------------
}

Enemy_Outdoor_turret:: ~Enemy_Outdoor_turret()
{

}

void Enemy_Outdoor_turret::Move()
{
	position.x = App->stage05->spawnPos.x+ initalPosition.x;
	position.y = App->stage05->spawnPos.y+ initalPosition.y;
	if (SDL_GetTicks() - StartTime > 3000 && position.x>0 && position.y>0)
	{
		/*App->enemies->AddEnemy(OUTDOOR_LASER, position_x, position_y);*/
		App->particles->AddParticle(App->particles->LaserEnemyShot, { (float)(position.x + 7), (float)(position.y - 10) }, { 3 , 3 }, App->particles->laserTx, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, 0, PARTICLE_LASER);
		StartTime = SDL_GetTicks();
	}

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}