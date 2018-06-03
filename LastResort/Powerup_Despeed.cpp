#include "Application.h"
#include "Powerup_Despeed.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleAudio.h"

Powerup_SlowDown::Powerup_SlowDown(int x, int y) : Powerup(x, y)
{
	//Push backs
	DespeedAnim.PushBack({ 0, 85, 18, 21 });

	//We set the animation of the base class to be this animation
	animation = &DespeedAnim;

	collider = App->collision->AddCollider({ 0, 0, 18, 21 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_SlowDown::OnCollision(Collider* col, ModulePlayer* playerTarget)
{
	App->audio->ControlAudio(App->powerups->despeedSFX, PLAY_AUDIO);


	playerTarget->speedPowerup = true;
	//We give it this powerup
	if (playerTarget->movementSpeed > 2.0f)
		playerTarget->movementSpeed -= 0.3f;


}