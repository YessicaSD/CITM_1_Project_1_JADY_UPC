#include "Application.h"
#include "Enemy_RotatingTurret.h"
#include "ModuleCollision.h"
#include <math.h>
#include "Player1.h"
#include "Player2.h"

Enemy_RotatingTurret::Enemy_RotatingTurret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//animation = &basicenemy;
	//collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_RotatingTurret::Move()
{
	//Calculate the rotation as if it was a triangle
	//int adjacentSide;
	//int oppositeSide;
	//adjacentSide = App->player1->position.y - position.y;
	//oppositeSide = App->player1->position.x - position.x;
	//rotation = atan(abs(oppositeSide)/abs(adjacentSide));
	////Then add a rotation depending on which triangle it is
	//if( position.y < App->player1->position.y && position.x >)
	//{

	//}
}