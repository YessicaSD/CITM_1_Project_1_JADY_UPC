#include "Application.h"
#include "Enemy_Pinata.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "MovPath.h"


Enemy_Pinata::Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	pinataMov.originPoint = { 0,0 };
	pinataMov.PushBack({ 0,90 }, 150);
	//Animations-----------------------------
	moveAnim.PushBack({ 263, 63,40,38 });   //1
	moveAnim.PushBack({ 223, 101,40,38 });  //2
	moveAnim.PushBack({ 263, 101,40,38 });  //3

	rotateAnim.PushBack({ 223, 139,40,38 }); //1
	rotateAnim.PushBack({ 263, 139,40,38 }); //2
	rotateAnim.PushBack({ 223, 139,40,38 }); //3

	initAnim.PushBack({ 223, 63,40,38 });   //1
	initAnim.PushBack({ 263, 139,40,38 });  //2
	initAnim.PushBack({ 223, 139,40,38 });  //3
	//Add collider--------------------------
	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Pinata::Move()
{
	//Check tarjet player---------------------------------------------
	if (checkTarget == true) {

		if (App->player2->position.DistanceTo(position) > App->player1->position.DistanceTo(position)) {
			currentTarget = App->player1;
		}
		else {
			currentTarget = App->player2;
		}

		if (lastTarget == nullptr) {
			lastTarget = currentTarget;
		}
		else if (lastTarget != currentTarget) {
			checkDirection = true;
			lastTarget = currentTarget;
		}
	}
	//Check enemie direction-------------------------------------------
	if (checkDirection == true) {
		if (position.x < currentTarget->position.x) {
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

	//Move-------------------------------------------------------------

	switch (currentState)
	{
	case INIT:
		if (pinataMov.movFinished) {
			checkTarget = true;
			currentState = FOLLOW;
			break;
		}
		pinataMov.GetCurrentPosition();
		position.x = pinataMov.GetPosition().x;
		position.y = pinataMov.GetPosition().y;
		break;

	case FOLLOW:
		
		break;
	case ROTATE:

		break;
	default:
		break;
	}

}

void Enemy_Pinata::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;
	blitEx = false;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	switch (currentState)
	{
	case INIT:

		if (pinataMov.currentMov == 0) {
			currentAnim = initAnim.frames[0];
		}
		else {
			currentAnim = initAnim.GetCurrentFrame();
		}
		break;

	case FOLLOW:



		break;
	case ROTATE:

		break;
	default:
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
		App->render->BlitEx(sprites, position.x, position.y, &currentAnim);
	}
		

}