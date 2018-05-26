#include "Enemy_Missile_Launcher.h"
#include "Application.h"
#include "ModuleStage05.h"
Enemy_Missile_Launcher::Enemy_Missile_Launcher(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop) :Enemy ( x,  y,  hp,  scoreValue, powerupDrop)
{
	Missile_Launcher.PushBack({ 250,278,29,32 });
	Missile_Launcher.speed = 0.0f;
	animation = &Missile_Launcher;
	collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	fixedPos2.x = x - App->stage05->spawnPos.x;
	fixedPos2.y = y - App->stage05->spawnPos.y;

}
void Enemy_Missile_Launcher::Move() {
	position = fixedPos + App->stage05->spawnPos;

}