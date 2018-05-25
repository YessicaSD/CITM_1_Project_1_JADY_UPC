#include "Enemy_Indoor_turret.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleCollision.h"
Enemy_indoorTurret::Enemy_indoorTurret(int x, int  y, float hp, int scoreValue, POWERUP_TYPE powerupDrop, iPoint speed) : Enemy( x, y, hp, scoreValue,powerupDrop)
{
	indoorTurretAnim.PushBack({ 128,196,24,16 });
	animation = &indoorTurretAnim;
	collider = App->collision->AddCollider({ x, y, 24, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	/*App->render->BlitEx();*/
}