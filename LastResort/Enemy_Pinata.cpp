#include "Application.h"
#include "Enemy_Pinata.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"

#define MAX_PINATA_SPEED 1.5f

Enemy_Pinata::Enemy_Pinata(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Position--------------------------------------
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	speed = { -1.0f, 0.0f };
	aceleration = { 0.1f, 0.1f };
	//Movement--------------------------------------
	pinataMov.originPoint = { 0,0 };
	pinataMov.PushBack({ 0,90 }, 150);
	pinataMov.PushBack({ -10 ,85 }, 15);
	//Animations------------------------------------
	moveAnim.PushBack({ 263, 62,40,38 });   //1
	moveAnim.PushBack({ 223, 100,40,38 });  //2
	moveAnim.PushBack({ 263, 100,40,38 });  //3
	moveAnim.speed = 0.3f;

	rotateAnim.PushBack({ 223, 176,40,38 }); //1
	rotateAnim.PushBack({ 263, 138,40,38 }); //2
	rotateAnim.PushBack({ 223, 138,40,38 }); //3
	rotateAnim.speed = 0.1f;

	initAnim.PushBack({ 223, 62,40,38 });   //1
	initAnim.PushBack({ 223, 138,40,38 });  //2
	initAnim.speed = 0.1f;
	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x-14 , y-14, 28, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


//Check target player------------------------------------------------

void Enemy_Pinata:: CheckTarget() {

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

void Enemy_Pinata::CheckDirection() {

	if (float_position.x  < currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDir = RIGHT;
	}
	else if (float_position.x >= currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDir = LEFT;
	}

	if (lastDir == NONE) {
		lastDir = currentDir;
	}
	else if (lastDir != currentDir && currentState != IDLE) {
		currentState = ROTATE;
		lastDir = currentDir; 
	}
}

//Movement-------------------------------------------------------------

void Enemy_Pinata::Move()
{
	fPoint vectorIncrease;
	fPoint PlayerPos;

	switch (currentState)
	{
	case IDLE:
		if (pinataMov.currentMov == 1) {
			CheckTarget();
			CheckDirection();
		}

		if (pinataMov.movFinished)
		{
			renderLayer = 2;
			currentState = FOLLOW;
			break;
		}

		pinataMov.GetCurrentPosition();
		float_position.y = App->stage05->spawnPos.y + fixedPos.y + pinataMov.GetPosition().y;

		if (currentDir == RIGHT)
			float_position.x = App->stage05->spawnPos.x + fixedPos.x - pinataMov.GetPosition().x;
		else
			float_position.x = App->stage05->spawnPos.x + fixedPos.x + pinataMov.GetPosition().x;

		break;

	case FOLLOW:


		CheckTarget();
		CheckDirection();


		PlayerPos.x = (float)currentTarget->position.x + currentTarget->playerCenter.x;
		PlayerPos.y = (float)currentTarget->position.y + currentTarget->playerCenter.y;

		vectorIncrease.UnitVector(PlayerPos, float_position);

		speed.x += vectorIncrease.x * aceleration.x;

		speed.y += vectorIncrease.y * aceleration.y;


		if (speed.x > MAX_PINATA_SPEED) {
			speed.x = MAX_PINATA_SPEED;
		}
		else if (speed.x < -MAX_PINATA_SPEED) {
			speed.x = -MAX_PINATA_SPEED;
		}

		if (speed.y > MAX_PINATA_SPEED) {
			speed.y = MAX_PINATA_SPEED;
		}
		else if (speed.y < -MAX_PINATA_SPEED) {
			speed.y = -MAX_PINATA_SPEED;
		}
		//Update position----------------------------------------------

		float_position.x += speed.x;
		float_position.y += speed.y;

		position = { (int)float_position.x, (int)float_position.y };

		break;
	case ROTATE:
		//Not move
		break;
	}
	position = { (int)float_position.x, (int)float_position.y };

	//Set the collider position
	if (collider != nullptr)
		collider->SetPos(position.x - 14, position.y - 14);
}

void Enemy_Pinata::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;
	blitEx = false;

	switch (currentState)
	{
	case IDLE:

		if (pinataMov.currentMov == 0) {
			currentAnim = initAnim.frames[0];
		}
		else {
			currentAnim = initAnim.frames[1];
		}
		break;

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
	if (currentDir == RIGHT)
		blitEx = true;
	else
		blitEx = false;

	//Draw------------------------------------------------------------------
	if (!blitEx) {
		App->render->Blit(sprites, position.x - 20, position.y - 19, &currentAnim);
	}
	else {
		App->render->BlitEx(sprites, position.x- 20, position.y - 19, &currentAnim, SDL_FLIP_HORIZONTAL);
	}
		

}