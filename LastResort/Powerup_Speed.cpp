#include "Application.h"
#include "Powerup_Speed.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleAudio.h"

Powerup_Speed::Powerup_Speed(int x, int y) : Powerup(x, y)
{
	//Push backs
	speedAnim.PushBack({0, 64, 18, 21});

	//We set the animation of the base class to be this animation
	animation = &speedAnim;

	collider = App->collision->AddCollider({ 0, 0, 18, 21 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_Speed::OnCollision(Collider* col, ModulePlayer* playerTarget)
{
	App->audio->ControlAudio(App->powerups->speedSFX, PLAY_AUDIO);

	playerTarget->speedPowerup = true;
	//We give it this powerup
	if (playerTarget->movementSpeed < 3.0f)
		playerTarget->movementSpeed += 0.3f;//Test value. We should check what is the speed increase in the game.

}