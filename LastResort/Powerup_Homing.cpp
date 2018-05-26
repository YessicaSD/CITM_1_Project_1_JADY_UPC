#include "Globals.h"
#include "Application.h"
#include "Powerup_Homing.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModulePowerups.h"


Powerup_Homing::Powerup_Homing(int x, int y) : Powerup(x, y)
{
	//Push backs
	homingAnim.PushBack({ 18, 64, 31, 16 });
	homingAnim.PushBack({ 49, 64, 31, 16 });
	homingAnim.speed = 0.01f;
	homingAnim.loop = true;
	//We set the animation of the base class to be this animation
	animation = &homingAnim;

	collider = App->collision->AddCollider({ 0, 0, 31, 16 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_Homing::OnCollision(Collider* col, ModulePlayer* playerTarget)
{
	//Change powerup type---------------------------------------------------
	playerTarget->currentPowerUp = POWERUP_TYPE::HOMING;
}