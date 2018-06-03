#include "Powerup_despeed.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "Player2.h"

Powerup_despeed::Powerup_despeed(int x, int y) : Powerup(x, y)
{
	//Push backs
	despeedanim.PushBack({ 0, 85, 18, 21 });

	//We set the animation of the base class to be this animation
	animation = &despeedanim;

	collider = App->collision->AddCollider({ 0, 0, 18, 21 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}
void Powerup_despeed::OnCollision(Collider* col, ModulePlayer* playerTarget)
{
	App->audio->ControlAudio(App->powerups->despeedSFX, PLAY_AUDIO);


	playerTarget->speedPowerup = true;
	//We give it this powerup
	if (playerTarget->movementSpeed > 2.0f)
		playerTarget->movementSpeed -= 0.3f;
}