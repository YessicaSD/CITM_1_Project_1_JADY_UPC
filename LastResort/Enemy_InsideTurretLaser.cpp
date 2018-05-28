#include "Enemy_InsideTurretLaserh.h"
#include "Application.h"
#include "ModuleStage05.h"
Enemy_Inside_Turret_Laser::Enemy_Inside_Turret_Laser(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop) :Enemy(x,y,hp,scoreValue,powerupDrop)
{
	turret.PushBack({ 250,310,16,24 });
	animation = &turret;
}
void Enemy_Inside_Turret_Laser::Move() {
	position = fixedPos + App->stage05->spawnPos;
}