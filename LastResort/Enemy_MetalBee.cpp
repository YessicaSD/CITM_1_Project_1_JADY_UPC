#include "Application.h"
#include "Enemy_MetalBee.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"

#define MAX_PINATA_SPEED 1.5f

Enemy_MetalBee::Enemy_MetalBee(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	moveAnim.PushBack({520,250,48,44});
	moveAnim.PushBack({ 570,250,48,44 });
	moveAnim.speed = 0.2f;
	animation = &moveAnim;

	rotateAnimRight.PushBack({ 621,250,43,44 });
	rotateAnimRight.PushBack({ 666,250,37,45 });
	rotateAnimRight.PushBack({ 705,250,39,45 });
	rotateAnimRight.PushBack({ 746,250,41,45 });
	rotateAnimRight.PushBack({ 789,250,41,45 });
	rotateAnimRight.PushBack({ 832,250,41,45 });
	rotateAnimRight.PushBack({ 882,250,37,45 });
	rotateAnimRight.PushBack({ 882,250,37,45 });
	rotateAnimRight.speed = 0.2f;

	rotateAnimLeft.PushBack({ 921,250,43,44 });
	rotateAnimLeft.PushBack({876,296,43,44 });
	rotateAnimLeft.PushBack({ 921,250,43,44 });
	rotateAnimLeft.PushBack({ 519,296,37,45 });
	rotateAnimLeft.PushBack({ 558,296,37,45 });
	rotateAnimLeft.PushBack({ 558,296,37,45 });
	rotateAnimLeft.PushBack({ 597,296,40,45 });
	rotateAnimLeft.PushBack({ 639,296,40,45 });
	rotateAnimLeft.PushBack({ 681,296,48,45 });
	rotateAnimLeft.PushBack({ 681,296,48,45 });
	rotateAnimLeft.PushBack({ 731,296,48,45 });
	rotateAnimLeft.PushBack({ 826,296,48,44 });
	rotateAnimLeft.PushBack({ 826,296,48,44 });

	collider = App->collision->AddCollider({ x - 12 , y - 12, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);

	speed = { 0.2f, 0.0f };
	aceleration = { 0.1f, 0.1f };

}
void Enemy_MetalBee:: Move()
{
	fPoint vectorIncrease;
	fPoint PlayerPos;

	// Update player position---------------------------------------
	if (currentState != ROTATE_LEFT && currentState != ROTATE_RIGHT) {
		CheckTarget();
		CheckDirection();
	}

	PlayerPos.x = (float)currentTarget->position.x + currentTarget->playerCenter.x;
	PlayerPos.y = (float)currentTarget->position.y + currentTarget->playerCenter.y;

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

	float_position.x += speed.x;
	float_position.y += speed.y;

	position = { (int)float_position.x, (int)float_position.y };

	//Set the collider position
	if (collider != nullptr) {

		collider->SetPos(position.x - 12, position.y - 12);
	}
}
void Enemy_MetalBee::CheckTarget() {

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
void Enemy_MetalBee::CheckDirection() {

	//	Check X direction----------------------

	if (float_position.x  < currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDirX = RIGHT;
	}
	else if (float_position.x >= currentTarget->position.x + currentTarget->playerCenter.x) {
		currentDirX = LEFT;
	}

	if (lastDirX != currentDirX) {
		if (currentDirX == LEFT)
		{
			currentState = ROTATE_LEFT;
		}
		if (currentDirX == RIGHT)
		{
			currentState = ROTATE_RIGHT;
		}
		lastDirX = currentDirX;
	}

}

void Enemy_MetalBee::Draw(SDL_Texture* sprites)
{

	blitEx = false;

	switch (currentState)
	{

	case FOLLOW:

		break;

	case ROTATE_RIGHT:

		animation = &rotateAnimRight;
		if (animation->Finished()) {

			animation->loop = 0;
			animation->current_frame = 0;
			animation = &moveAnim;
			currentState = FOLLOW;
			
		}
		break;
	case ROTATE_LEFT:
		animation = &rotateAnimLeft;
		if (animation->Finished()) {

			animation->loop = 0;
			animation->current_frame = 0;
			animation = &moveAnim;
			currentState = FOLLOW;

		}
		break;

	}

	//Check direction for flip blit or not----------------------------------
	if (currentDirX == LEFT)
		blitEx = true;

	//Draw------------------------------------------------------------------
	if (!blitEx) {
		App->render->Blit(sprites, position.x - 15, position.y - 15, &animation->GetCurrentFrame());
	}
	else {
		App->render->BlitEx(sprites, position.x - 15, position.y - 15, &animation->GetCurrentFrame(), SDL_FLIP_HORIZONTAL);
	}

}


