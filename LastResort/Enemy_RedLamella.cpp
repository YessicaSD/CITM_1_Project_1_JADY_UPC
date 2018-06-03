#include "Application.h"
#include "Enemy_RedLamella.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"

#define MAX_LAMELA_SPEED 1.6f
#define LAMELLA_ROTATION_FRAMES 5
#define LAMELLA_RUNAWAY_FRAMES 1500


Enemy_RedLamella::Enemy_RedLamella(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animations------------------------------------
	float_position.x += x;
	float_position.y += y;

	for (int i = 0; i < 3; ++i) {
		moveAnim.PushBack({ 868 + i* 31, 0,31,31 });
	}
	moveAnim.speed = 0.3f;

	rotateAnim.PushBack({ 961, 0, 31, 31 }); 
	rotateAnim.speed = 0.0f;

	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x - 12 , y - 12, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);

	speed = { -1.0f, 0.0f };
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

bool Enemy_RedLamella::CheckDirection() {

	//	Check X direction----------------------
	if (runAway == true) {

		if (float_position.x  < -400) {
			currentDirX = RIGHT;
		}
		else if (float_position.x > -400) {
			currentDirX = LEFT;
		}

		if (lastDirX != currentDirX) {
			currentState = ROTATE;
			lastDirX = currentDirX;
		}
		return true;
	}


	if (float_position.x  < currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDirX = RIGHT;
	}
	else if (float_position.x >= currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDirX = LEFT;
	}

	 if (lastDirX != currentDirX ) {
		currentState =ROTATE;
		lastDirX = currentDirX;
	}



}

//Movement-------------------------------------------------------------

void Enemy_RedLamella::Move()
{
	fPoint vectorIncrease;
	fPoint PlayerPos;

	// Update player position---------------------------------------
	if (currentState != ROTATE) {
		CheckTarget();
		CheckDirection();
	}
	if (runAway == true) {

		PlayerPos.x = -400.0f;
		PlayerPos.y = 112.0f;
	}
	else {
		PlayerPos.x = (float)currentTarget->position.x + currentTarget->playerCenter.x;
		PlayerPos.y = (float)currentTarget->position.y + currentTarget->playerCenter.y;
	}

	if (runAwayFrames > LAMELLA_RUNAWAY_FRAMES)
		runAway = true;
	else 
	++runAwayFrames;


	vectorIncrease.UnitVector(PlayerPos, float_position);

	speed.x += vectorIncrease.x * aceleration.x;

	speed.y += vectorIncrease.y * aceleration.y;


	if (speed.x > MAX_LAMELA_SPEED) {
		speed.x = MAX_LAMELA_SPEED;
	}
	else if (speed.x < -MAX_LAMELA_SPEED) {
		speed.x = -MAX_LAMELA_SPEED;
	}

	if (speed.y > MAX_LAMELA_SPEED) {
		speed.y = MAX_LAMELA_SPEED;
	}
	else if (speed.y < -MAX_LAMELA_SPEED) {
		speed.y = -MAX_LAMELA_SPEED;
	}

	//Update position----------------------------------------------

	float_position.x += speed.x ;
	float_position.y += speed.y;

	position = { (int)float_position.x, (int)float_position.y };

	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 12, position.y - 12);
	}
		
}

void Enemy_RedLamella::Draw1(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;
	blitEx = false;

	switch (currentState)
	{

	case FOLLOW:
		currentAnim = moveAnim.LoopAnimation();

		break;
	case ROTATE:

		currentAnim = rotateAnim.frames[0];
		++currentFrames;
		if (currentFrames > LAMELLA_ROTATION_FRAMES) {
			moveAnim.Reset();
			currentFrames = 0;
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
		App->render->Blit(sprites, position.x - 15, position.y - 15, &currentAnim);
	}
	else {
		App->render->BlitEx(sprites, position.x - 15, position.y - 15, &currentAnim, SDL_FLIP_HORIZONTAL);
	}

}