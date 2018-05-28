#include "Application.h"
#include "Enemy_IntergalacticF.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"
#include <stdlib.h>

#define INTERGALACTIC_SPEED_FRAMES 30

Enemy_Intergalactic_F::Enemy_Intergalactic_F(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	renderLayer = 0;

	shootFrames = rand() %120 + 120;

	//Position--------------------------------------

	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;

	//Movement--------------------------------------
	enemyMov.originPoint = { -39, 50 };

	enemyMov.PushBack({ -10,27 }, INTERGALACTIC_SPEED_FRAMES);

	enemyMov.PushBack({  0 , 0 }, INTERGALACTIC_SPEED_FRAMES);

	enemyMov.PushBack({ -10,-27 }, INTERGALACTIC_SPEED_FRAMES);

	enemyMov.PushBack({ -39,-50 }, INTERGALACTIC_SPEED_FRAMES);

	enemyMov.loop = true;
	//Animations------------------------------------

	shotAnim.PushBack({ 669, 96,16,16 });
	shotAnim.PushBack({ 685 , 96,16,16 });
	shotAnim.speed = 0.2;


	for (int i = 0; i < 4; ++i) {
		moveRAnim.PushBack({ 669 - i * 48, 48,48,48 });
	}
	moveRAnim.speed = 0.3f;

	for (int i = 0; i < 4; ++i) {
		moveLAnim.PushBack({ 669 - i * 48, 0,48,48 });
	}
	moveLAnim.speed = 0.3f;

	for (int i = 0; i < 3; ++i) {
		rotateRAnim.PushBack({ 525 + i * 48, 96 ,48, 48 });
	}
	rotateRAnim.speed = 0.1f;

	for (int i = 0; i < 3; ++i) {
		rotateLAnim.PushBack({ 621 - i * 48, 96,48,48 });
	}
	rotateLAnim.speed = 0.1f;


	//Add collider--------------------------------
	collider = App->collision->AddCollider({ x - 20, y- 20, 40, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}


//Check tarjet player------------------------------------------------

void Enemy_Intergalactic_F::CheckTarget() {

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

void Enemy_Intergalactic_F::CheckDirection() {

	if (float_position.x  < currentTarget->position.x) {
		currentDir = RIGHT;
	}
	else if (float_position.x >= currentTarget->position.x) {
		currentDir = LEFT;
	}

	if (lastDir == NONE) {
		lastDir = currentDir;
	}
	else if (lastDir != currentDir ) {
		currentState = ROTATE;
		lastDir = currentDir;
	}
}

//Movement-------------------------------------------------------------

void Enemy_Intergalactic_F::Move()
{
	fPoint vectorIncrease;
	fPoint PlayerPos;

	switch (currentState)
	{

	case MOVE:
		CheckTarget();
		CheckDirection();

		enemyMov.GetCurrentPosition();

		float_position.y = App->stage05->spawnPos.y + fixedPos.y + enemyMov.GetPosition().y;
		float_position.x = App->stage05->spawnPos.x + fixedPos.x + enemyMov.GetPosition().x;

		//Shots logic-----------------------------------------------------------------

		if (currentFrames > shootFrames && currentFrames != -1) {
			currentFrames = -1;
			isShooting = true;
			if (currentDir == RIGHT)
				App->particles->AddParticle(App->particles->i_f_Shot, { (float)(position.x -24), (float)(position.y - 8) }, { 2.8f, 0.0f }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);
			else
				App->particles->AddParticle(App->particles->i_f_Shot, { (float)(position.x - 24), (float)(position.y -8) }, {- 2.8f, 0.0f }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT, 0, PARTICLE_FOLLOW_WORLD);

		}
		else
			++currentFrames;
		break;

	case ROTATE:
		//Not move
		break;
	}
	position = { (int)float_position.x, (int)float_position.y };

	if (collider != nullptr)
		collider->SetPos(position.x - 20, position.y - 20);
}

void Enemy_Intergalactic_F::Draw(SDL_Texture* sprites)
{
	SDL_Rect currentAnim;

	switch (currentState)
	{
	case MOVE:

		if (currentDir == RIGHT) {
			currentAnim = moveRAnim.LoopAnimation();
		}
			
		else if (currentDir == LEFT) {
			currentAnim = moveLAnim.LoopAnimation();
		}

		if (isShooting == true) {

			if (currentDir == RIGHT)
				App->render->BlitEx(sprites, position.x +16, position.y - 14, &shotAnim.GetFrameEx());
			else
				App->render->Blit(sprites, position.x - 32, position.y - 14, &shotAnim.GetFrameEx());

			if (shotAnim.finished == true) {
				shotAnim.Reset(); 
				isShooting = false;
				currentFrames = 0;
			} 
		}


		break;
	case ROTATE:

		if (currentDir == RIGHT) {
			currentAnim = rotateRAnim.GetFrameEx();
			if (rotateRAnim.finished == true) {
				moveRAnim.Reset();
				rotateRAnim.Reset();
				currentState = MOVE;
			}
		}
			

		else if (currentDir == LEFT) {
			currentAnim = rotateLAnim.GetFrameEx();
			if (rotateLAnim.finished == true) {
				moveLAnim.Reset();
				rotateLAnim.Reset();
				currentState = MOVE;
			}
		}
		break;
	}

	//Draw------------------------------------------------------------------

	App->render->Blit(sprites, position.x - 24, position.y -24, &currentAnim);

}