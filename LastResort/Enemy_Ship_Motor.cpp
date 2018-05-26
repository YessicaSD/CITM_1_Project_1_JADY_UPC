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
	Ship_Motor.speed = 0.2f;
	animation = &Ship_Motor;

}

void Enemy_Ship_Motor::Move()
{
	position = fixedPos + App->stage05->spawnPos;

}