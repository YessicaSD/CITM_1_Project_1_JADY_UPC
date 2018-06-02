#include "Application.h"
#include "Enemy_RedLamella.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"


Enemy_RedLamella::Enemy_RedLamella(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animations------------------------------------

	for (int i = 0; i < 3; ++i) {
		moveAnim.PushBack({ 868 + i* 31, 0,31,31 });
	}
	moveAnim.speed = 0.3f;

	rotateAnim.PushBack({ 961, 0, 31, 31 }); //1
	rotateAnim.speed = 0.1f;

	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x - 14 , y - 14, 28, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);

	velocity = { 2.0f, 2.0f };
	aceleration = { 0.1f, 0.1f };
}


//Check target player------------------------------------------------

void Enemy_RedLamella::CheckTarget() {

	float DistancePlayer1 = float_position.DistanceTo({ (float)App->player1->position.x,(float)App->player1->position.y });
	float DistancePlayer2 = float_position.DistanceTo({ (float)App->player2->position.x,(float)App->player2->position.y });

	if (DistancePlayer1 <= DistancePlayer2) {
		if (App->player1->isActive)
			currentTarget = App->player1;
		else if (App->player2->isActive)
			currentTarget = App->player2;
	}
	else if (DistancePlayer2  < DistancePlayer1)
	{
		if (App->player2->isActive)
			currentTarget = App->player2;
		else if (App->player1->isActive)
			currentTarget = App->player1;
	}

	if (lastTarget == nullptr) {
		lastTarget = currentTarget;
	}
	else if (lastTarget != currentTarget) {
		CheckDirection();
		lastTarget = currentTarget;
	}

}

//Check enemy direction-----------------------------------------------

void Enemy_RedLamella::CheckDirection() {

	//	Check X direction----------------------

	if (float_position.x  < currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDirX = RIGHT;
	}
	else if (float_position.x >= currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDirX = LEFT;
	}
	else if (lastDirX != currentDirX ) {
		currentState = ROTATE;
		lastDirX = currentDirX;
	}
	//	Check Y direction--------------------

	if (float_position.y  < currentTarget->position.y  + currentTarget->playerCenter.y) {
		currentDirY = DOWN;
	}
	else if (float_position.y >= currentTarget->position.y + currentTarget->playerCenter.y) {
		currentDirY = UP;
	}


}

//Movement-------------------------------------------------------------

void Enemy_RedLamella::Move()
{
	fPoint vectorIncrease;
	fPoint PlayerPos;

	// Update player position---------------------------------------
	CheckTarget();
	CheckDirection();

	PlayerPos.x = (float)currentTarget->position.x + currentTarget->playerCenter.x;
	PlayerPos.y = (float)currentTarget->position.y + currentTarget->playerCenter.y;

	vectorIncrease.UnitVector(PlayerPos, float_position);

	velocity.x += vectorIncrease.x * aceleration.x;

	velocity.y += vectorIncrease.y * aceleration.y;


	if (velocity.x > 3) {
		velocity.x = 3;
	}
	else if (velocity.x < -3) {
		velocity.x = - 3;
	}

	if (velocity.y > 3) {
		velocity.y = 3;
	}
	else if (velocity.y < -3) {
		velocity.y = -3;
	}

	//Update position----------------------------------------------

	float_position.x += velocity.x ;
	float_position.y += velocity.y;

	position = { (int)float_position.x, (int)float_position.y };

	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 14, position.y - 14);
	}
		
}

void Enemy_RedLamella::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;
	blitEx = false;

	switch (currentState)
	{

	case FOLLOW:
		currentAnim = moveAnim.LoopAnimation();

		break;
	case ROTATE:
		currentAnim = rotateAnim.GetFrameEx();

		if (rotateAnim.finished == true) {
			moveAnim.Reset();
			rotateAnim.Reset();
			currentState = FOLLOW;
		}
		break;

	}

	//Check direction for flip blit or not----------------------------------
	if (currentDirX == RIGHT)
		blitEx = true;
	else
		blitEx = false;

	//Draw------------------------------------------------------------------
	if (!blitEx) {
		App->render->Blit(sprites, position.x - 16, position.y - 15, &currentAnim);
	}
	else {
		App->render->BlitEx(sprites, position.x - 16, position.y - 16, &currentAnim, SDL_FLIP_HORIZONTAL);
	}

}