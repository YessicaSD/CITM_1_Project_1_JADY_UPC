#include "Application.h"
#include "Enemy_RotatingTurret.h"
#include "ModuleCollision.h"
#include <math.h>
#include "Player1.h"
#include "Player2.h"

Enemy_RotatingTurret::Enemy_RotatingTurret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//Position

	//Animation
	//animation = &rotatingTurretAnim;
	//collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
}

void Enemy_RotatingTurret::Move()
{
	//Movement-------------------------------------------------------------------
	//- Lock position



	//Shoot----------------------------------------------------------------------
	//- Select which player we need to follow
	//if()
	//{

	//}
	//If(sqrt((pow(App->player1->position.x – position.x, 2) + pow(App->player2->position.y – position.y))<)
	//			//Checkejar que estigui enabled
	//		{
	//			playerToFollow = App->player2;
	//		}
	//		Else
	//		{
	//			playerToFollow = App->player1;
	//		}

	//Move()
	//{
	//	//Select which player we need to follow
	//	
	//		//Then check rotation from that player to the turret
	//		//Render
	//		//Shoot every x time? Or when it fixes the position?
	//}

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

	//ModulePlayer playerToFollow;
}