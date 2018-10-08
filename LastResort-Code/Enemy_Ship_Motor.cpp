#include "Application.h"
#include "Enemy_Ship_Motor.h"
#include "ModuleStage05.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "SDL\include\SDL.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy_Ship_Motor::Enemy_Ship_Motor(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop):Enemy( x, y,  hp, scoreValue, powerupDrop)
{
	//row
	Ship_Motor.PushBack({ 303,53,57,47 });
	Ship_Motor.PushBack({ 360,53,57,47 });
	Ship_Motor.PushBack({ 417,53,54,47 });
	Ship_Motor.PushBack({ 471,53,54,47 });

	for (i = 100; i <= 401; i += 43)
	{
		for ( j=303;j<=406;j+=54)
		{
			Ship_Motor.PushBack({ j,i,54,43 });
		}
	}
	Ship_Motor.PushBack({ 303,444,54,47 });
	Ship_Motor.PushBack({ 357,444,57,47 });
	Ship_Motor.PushBack({ 303,53,57,47 });
	Ship_Motor.speed = 0.0f;
	Ship_Motor.loop = true;
	animation = &Ship_Motor;
	Ship_Part = {414,444,63,63};
	collider = App->collision->AddCollider({ x, y, 50, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
	stateMotor = CLOSE;
}

void Enemy_Ship_Motor::Move()
{
	if (spawn)
	{
		MissileLaunch = App->enemies->InstaSpawn(MISSILE_LAUNCHER, 913, 224);
		spawn = false;
	}
	
	position = fixedPos + App->stage05->spawnPos;

	if (stateMotor == CLOSE)
	{
		if (frameCount == 150)
		{
			animation->loop = 0;
			stateMotor = OPEN;
			Ship_Motor.speed = 0.2f;
			collider->type = COLLIDER_ENEMY_HEAVY;
		}
		frameCount += 1;
	}
	if (stateMotor == OPEN)
	{

		if(Ship_Motor.finished)
		{
			collider->type = COLLIDER_WALL;
			Ship_Motor.Reset();
			stateMotor = CLOSE;
			Ship_Motor.speed = 0.0f;
			frameCount = 0;
		}
	}

	if (collider != nullptr)
		collider->SetPos(position.x - Ship_Part.w, position.y + 15 - Ship_Part.h);

	//Check if missile launcher has died
	if(MissileLaunch != nullptr && MissileLaunch->isDead)
	{
		MissileLaunch = nullptr;
	}

}

Enemy_Ship_Motor::~Enemy_Ship_Motor()
{
	if (MissileLaunch != nullptr)
	{
		App->enemies->ManualDespawn(MissileLaunch);
	}
}

void Enemy_Ship_Motor::Draw1(SDL_Texture* sprites)
{
	if (animation != nullptr)
		App->render->Blit(sprites, position.x-Ship_Part.w, position.y +15 - Ship_Part.h, &(animation->GetFrameEx()));

	App->render->Blit(sprites, position.x-Ship_Part.w, position.y - Ship_Part.h, &Ship_Part);
}

void Enemy_Ship_Motor::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->g_explosion02, { (float)position.x, (float)position.y }, { 0 ,0 }, App->particles->g_explosion02.texture, COLLIDER_IGNORE_HIT, 0, PARTICLE_FOLLOW_BACKGROUND);

	if (SDL_GetTicks() % 2)
		App->audio->ControlAudio(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	else
		App->audio->ControlAudio(App->particles->g_explosion02_1sfx, PLAY_AUDIO);
	//It will destroy ship launcher in its destructior
}