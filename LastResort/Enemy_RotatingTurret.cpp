#include "Application.h"
#include "Enemy_RotatingTurret.h"
#include "ModuleCollision.h"
#include <math.h>
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"

Enemy_RotatingTurret::Enemy_RotatingTurret(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//Animation
	rotatingTurretAnim.PushBack({ 332,  0, 26, 27 });// 0 = E
	rotatingTurretAnim.PushBack({ 412, 27, 26, 27 });// 1 = ESE
	rotatingTurretAnim.PushBack({ 358,  0, 26, 27 });// 2 = SE
	rotatingTurretAnim.PushBack({ 384,  0, 26, 27 });// 3 = SSE
	rotatingTurretAnim.PushBack({ 410,  0, 26, 27 });// 4 = S
	rotatingTurretAnim.PushBack({ 359, 27, 26, 27 });// 5 = SSW
	rotatingTurretAnim.PushBack({ 436,  0, 26, 27 });// 6 = SW
	rotatingTurretAnim.PushBack({ 255, 27, 26, 27 });// 7 = WSW
	rotatingTurretAnim.PushBack({ 281, 27, 26, 27 });// 8 = W
	rotatingTurretAnim.PushBack({ 385, 27, 26, 27 });// 9 = WNW
	rotatingTurretAnim.PushBack({ 307, 27, 26, 27 });//10 = NW
	rotatingTurretAnim.PushBack({ 333, 27, 26, 27 });//11 = NNW
	rotatingTurretAnim.PushBack({ 254,  0, 26, 27 });//12 = N
	rotatingTurretAnim.PushBack({ 438, 27, 26, 27 });//13 = NNE
	rotatingTurretAnim.PushBack({ 280,  0, 26, 27 });//14 = NE
	rotatingTurretAnim.PushBack({ 305,  0, 26, 27 });//15 = ENE
	animation = &rotatingTurretAnim;
	//Position
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	//Collider
	collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);
}

void Enemy_RotatingTurret::Move()
{
	//Movement-------------------------------------------------------------------
	//- Lock position
	position = App->stage05->spawnPos + fixedPos;

	//- Select the player we need to aim to
	if(App->player1->isActive == true && App->player2->isActive == true)
	{
		//Check which one is at less distance
		if (sqrt(pow(position.x - App->player1->position.x, 2) + pow(position.y - App->player1->position.y, 2)) <=
			sqrt(pow(position.x - App->player2->position.x, 2) + pow(position.y - App->player2->position.y, 2)))
		{
			targetPlayerPos = App->player2->position;
		}
		else
		{
			targetPlayerPos = App->player1->position;
		}
	}

	else if (App->player1->isActive == true && App->player2->isActive == false)
	{
		targetPlayerPos = App->player1->position;
	}

	else if (App->player1->isActive == false && App->player2->isActive == true)
	{
		targetPlayerPos = App->player2->position;
	}



	//- Calculate rotation
	CalculateRotation();


	//Shoot----------------------------------------------------------------------
	//- Select which player we need to follow
	//if()
	//{

	//}


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

float Enemy_RotatingTurret::CalculateRotation()
{
	//1- Check where the player is
	//2- Calculate the rotation

	//Fist quadrant
	if(targetPlayerPos.x > this->position.x && targetPlayerPos.y > this->position.y)
	{

	}
	//Second quadrant
	else if (targetPlayerPos.x < this->position.x && targetPlayerPos.y > this->position.y)
	{

	}
	//Third quadrant
	else if (targetPlayerPos.x < this->position.x && targetPlayerPos.y < this->position.y)
	{

	}
	//Fourth quadrant
	else if (targetPlayerPos.x > this->position.x && targetPlayerPos.y < this->position.y)
	{

	}


	//- In line
	else if (targetPlayerPos.x == this->position.x && targetPlayerPos.y > this->position.y)
	{

	}
	else if (targetPlayerPos.x < this->position.x && targetPlayerPos.y == this->position.y)
	{

	}
	else if (targetPlayerPos.x == this->position.x && targetPlayerPos.y < this->position.y)
	{

	}
	else if (targetPlayerPos.x > this->position.x && targetPlayerPos.y == this->position.y)
	{

	}


	//Same position
	else if (targetPlayerPos.x == this->position.x && targetPlayerPos.y == this->position.y)
	{
		//Keep the same rotation as the frame before
		return rotation;
	}
}