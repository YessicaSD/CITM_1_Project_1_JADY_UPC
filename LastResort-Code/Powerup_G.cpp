#include "Globals.h"
#include "Application.h"
#include "Powerup_G.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModulePowerups.h"


Powerup_G::Powerup_G(int x, int y) : Powerup(x, y)
{
	//Push backs
	gAnim.PushBack({ 18, 96, 31, 16 });
	gAnim.PushBack({ 49, 96, 31, 16 });
	gAnim.speed = 0.01f;
	gAnim.loop = true;
	//We set the animation of the base class to be this animation
	animation = &gAnim;

	collider = App->collision->AddCollider({ 0, 0, 31, 16 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_G::OnCollision(Collider* col, ModulePlayer* targetPlayer)
{
	//Change powerup type---------------------------------------------------
	targetPlayer->currentPowerUp = POWERUP_TYPE::GROUND;
}