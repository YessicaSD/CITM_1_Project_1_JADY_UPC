#include "Application.h"
#include "Enemy_Outdoor_turret.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

Enemy_Outdoor_turret::Enemy_Outdoor_turret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
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

void Enemy_Outdoor_turret::Move()
{
	position.x = App->stage05->spawnPos.x+ initalPosition.x;
	position.y = App->stage05->spawnPos.y+ initalPosition.y;
	if (SDL_GetTicks() - StartTime > 3000 && position.x>0 && position.y>0)
	{
		/*App->enemies->AddEnemy(OUTDOOR_LASER, position_x, position_y);*/
		App->particles->AddParticle(App->particles->LacerEnemyShot,position.x+7,position.y-10,App->particles->LaserTex,COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE,0, PARTICLE_LASER);
		StartTime = SDL_GetTicks();
	}
}
Enemy_Outdoor_turret:: ~Enemy_Outdoor_turret()
{
	
}

