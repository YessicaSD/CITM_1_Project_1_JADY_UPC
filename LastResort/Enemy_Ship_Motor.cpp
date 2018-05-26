#include "Application.h"
#include "Enemy_Ship_Motor.h"
#include "ModuleStage05.h"

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
	collider = App->collision->AddCollider({ x, y, 57, 47 }, COLLIDER_TYPE::COLLIDER_IGNORE_HIT, (Module*)App->enemies);
	stateMotor = CLOSE;

}

void Enemy_Ship_Motor::Move()
{
	position = fixedPos + App->stage05->spawnPos;

	LOG("Current_Frame:%f", animation->GetCurrentFrameNum());
	LOG("SPEED:%f", animation->GetCurrentFrameNum());
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
			collider->type = COLLIDER_IGNORE_HIT;
			Ship_Motor.Reset();
			stateMotor = CLOSE;
			Ship_Motor.speed = 0.0f;
			frameCount = 0;
		}
	}
	

}
void Enemy_Ship_Motor::Draw(SDL_Texture* sprites) {

	if (collider != nullptr)
		collider->SetPos(position.x, position.y +10);

	
	

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y +15  , &(animation->GetFrameEx()));


	App->render->Blit(sprites, position.x, position.y, &Ship_Part);

}