#include "Application.h"
#include "Enemy_RedBats.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleStageFunctionality.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include <stdlib.h>

Enemy_RedBats::Enemy_RedBats(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	RedBats.PushBack({ 150,0,27,29 });
	RedBats.PushBack({ 176,0,25,30 });
	RedBats.PushBack({ 202,0,26,29 });
	RedBats.PushBack({ 228,0,26,29 });
	RedBats.PushBack({ 150,30,26,29 });
	RedBats.PushBack({ 176,29,26,29 });
	RedBats.PushBack({ 202,29,26,29 });
	RedBats.PushBack({ 228,29,26,29 });
	RedBats.speed = 0.09f;
	animation = &RedBats;
	collider = App->collision->AddCollider({ x, y, 27, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	original_y = y;
	if(App->stageFunctionality->redBatsSpawned == 5)
	{
		//We reset the red bats killed if it is the start of another group
		App->stageFunctionality->redBatsKilled  = 0;
		App->stageFunctionality->redBatsSpawned = 0;
	}
	App->stageFunctionality->redBatsSpawned++;
}

void Enemy_RedBats::Move()
{

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.08f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.08f;
	}

	position.y = int(float(original_y) + (18.0f * sinf(wave)));
	position.x -= 2;

	//Set the collider position
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy_RedBats::OnCollision(Collider* collider)
{
	//Spawn powerup if all the other red bats have been killed-----------
	//- Increase the killed bats counter
	App->stageFunctionality->redBatsKilled++;
	//- Check how many red bats have been killed
	if (App->stageFunctionality->redBatsKilled >= 5)
	{
		int droptype = rand() % 5;
		App->powerups->AddPowerup(position.x, position.y, (POWERUP_TYPE)droptype);
		App->stageFunctionality->redBatsKilled = 0;
	}

	//Explosion type REMEMBER: Improve it for 1.0-----------------------
	App->particles->AddParticle(App->particles->g_explosion02, { (float)position.x, (float)position.y }, { 0, 0 }, App->particles->g_explosion02.texture, COLLIDER_IGNORE_HIT, 0);

	//Sfx REMEMBER: Improve it for 1.0----------------------------------
	if (SDL_GetTicks() % 2)
	{
		App->audio->ControlAudio(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	}
	else
	{
		App->audio->ControlAudio(App->particles->g_explosion02_1sfx, PLAY_AUDIO);
	}
}

void Enemy_RedBats::Draw1(SDL_Texture * sprites)
{
	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}