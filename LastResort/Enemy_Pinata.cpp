#include "Application.h"
#include "Enemy_Pinata.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"


Enemy_Pinata::Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	//Position--------------------------------------
	initialX = x - App->stage05->spawnPos.x;//We get the x position
	initialY = y - App->stage05->spawnPos.y;//We get the y position
	//Movement--------------------------------------
	pinataMov.originPoint = { 0,0 };
	pinataMov.PushBack({ 0,90 }, 150);
	pinataMov.PushBack({ -15 ,80 }, 30);
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
	collider = App->collision->AddCollider({ initialX, initialY, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


//Check tarjet player------------------------------------------------

void Enemy_Pinata:: CheckTarget() {

	if (App->player2->position.DistanceNoSqrt(position) > App->player1->position.DistanceNoSqrt(position)) {
		currentTarget = App->player1;
	}
	else {
		currentTarget = App->player2;
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

	if (position.x  < currentTarget->position.x) {
		currentDir = RIGHT;
	}
	else {
		currentDir = LEFT;
	}

	if (lastDir == STILL) {
		lastDir = currentDir;
	}
	else if (lastDir != currentDir) {
		currentState = ROTATE;
		lastDir = currentDir;
	}
}

//Movement-------------------------------------------------------------

void Enemy_Pinata::Move()
{
	
	switch (currentState)
	{
	case INIT:

		if (pinataMov.currentMov == 0) {
			CheckTarget();
			CheckDirection();
		}

		if (pinataMov.movFinished) {
			currentState = FOLLOW;
			break;
		}

		pinataMov.GetCurrentPosition();
		position.y = initialY + pinataMov.GetPosition().y;

		if (currentDir == RIGHT)
			position.x = initialX + pinataMov.GetPosition().x;
		else
			position.x = initialX -  pinataMov.GetPosition().x;

		break;

	case FOLLOW:
		CheckTarget();
		CheckDirection();
		break;

	case ROTATE:

		//Not move
		break;

	}
}

void Enemy_Pinata::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;
	blitEx = false;

	if (collider != nullptr)
		collider->SetPos(position.x , position.y );

	switch (currentState)
	{
	case INIT:

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
			CheckTarget();
			CheckDirection();
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
		App->render->Blit(sprites, position.x, position.y, &currentAnim);
	}
	else {
		App->render->BlitEx(sprites, position.x, position.y, &currentAnim, SDL_FLIP_HORIZONTAL);
	}
		

}