#include "Application.h"
#include "Enemy_Missile_turret.h"
#include "ModuleStage05.h"

Enemy_Missile_turret::Enemy_Missile_turret(int x,int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop):Enemy(x,y, hp, scoreValue,  powerupDrop)
{
	turret.PushBack({128,212,24,19});
	animation = &turret;
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
}
void Enemy_Missile_turret::Move()
{
	position = fixedPos + App->stage05->spawnPos;

}