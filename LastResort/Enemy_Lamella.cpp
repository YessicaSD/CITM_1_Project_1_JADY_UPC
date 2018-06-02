#include "Application.h"
#include "Enemy_Lamella.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleRender.h"

Enemy_Lamella::Enemy_Lamella(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Position
	auxPos.x = (float)position.x;
	auxPos.y = (float)position.y;
	//Animation
	appearingAnim.PushBack({ 523, 388, 28, 28 });
	appearingAnim.PushBack({ 553, 388, 32, 32 });
	appearingAnim.PushBack({ 587, 388, 30, 30 });
	appearingAnim.PushBack({ 619, 387, 28, 28 });
	appearingAnim.PushBack({ 649, 388, 36, 36 });
	appearingAnim.PushBack({ 687, 388, 32, 32 });
	appearingAnim.PushBack({ 721, 388, 28, 28 });
	appearingAnim.PushBack({ 520, 426, 32, 32 });
	appearingAnim.PushBack({ 520, 426, 32, 32 });
	appearingAnim.PushBack({ 554, 426, 30, 30 });
	appearingAnim.PushBack({ 586, 426, 28, 28 });
	appearingAnim.PushBack({ 616, 426, 36, 36 });
	appearingAnim.PushBack({ 654, 426, 32, 32 });
	appearingAnim.PushBack({ 688, 426, 28, 28 });
	appearingAnim.PushBack({ 718, 426, 32, 32 });
	appearingAnim.PushBack({ 520, 464, 30, 30 });
	appearingAnim.PushBack({ 552, 464, 30, 30 });
	appearingAnim.PushBack({ 582, 464, 36, 36 });
	appearingAnim.PushBack({ 620, 464, 32, 32 });
	appearingAnim.PushBack({ 654, 464, 28, 28 });
	appearingAnim.PushBack({ 684, 464, 32, 32 });
	appearingAnim.PushBack({ 718, 464, 30, 30 });
	appearingAnim.PushBack({ 520, 501, 28, 28 });
	appearingAnim.PushBack({ 550, 502, 36, 36 });
	appearingAnim.PushBack({ 588, 502, 32, 32 });
	appearingAnim.PushBack({ 622, 502, 28, 28 });
	appearingAnim.PushBack({ 652, 502, 32, 32 });
	appearingAnim.PushBack({ 686, 502, 30, 30 });
	appearingAnim.PushBack({ 717, 501, 30, 30 });
	appearingAnim.PushBack({ 520, 540, 36, 36 });
	appearingAnim.PushBack({ 558, 540, 32, 32 });
	appearingAnim.PushBack({ 591, 538, 32, 32 });
	appearingAnim.PushBack({ 625, 540, 32, 32 });
	appearingAnim.speed = 0.25f;
	appearingAnim.loop = false;

	disappearingAnim.PushBack({ 625, 540, 32, 32 });
	disappearingAnim.PushBack({ 591, 538, 32, 32 });
	disappearingAnim.PushBack({ 558, 540, 32, 32 });
	disappearingAnim.PushBack({ 520, 540, 36, 36 });
	disappearingAnim.PushBack({ 717, 501, 30, 30 });
	disappearingAnim.PushBack({ 686, 502, 30, 30 });
	disappearingAnim.PushBack({ 652, 502, 32, 32 });
	disappearingAnim.PushBack({ 622, 502, 28, 28 });
	disappearingAnim.PushBack({ 588, 502, 32, 32 });
	disappearingAnim.PushBack({ 550, 502, 36, 36 });
	disappearingAnim.PushBack({ 520, 501, 28, 28 });
	disappearingAnim.PushBack({ 718, 464, 30, 30 });
	disappearingAnim.PushBack({ 684, 464, 32, 32 });
	disappearingAnim.PushBack({ 654, 464, 28, 28 });
	disappearingAnim.PushBack({ 620, 464, 32, 32 });
	disappearingAnim.PushBack({ 582, 464, 36, 36 });
	disappearingAnim.PushBack({ 552, 464, 30, 30 });
	disappearingAnim.PushBack({ 520, 464, 30, 30 });
	disappearingAnim.PushBack({ 718, 426, 32, 32 });
	disappearingAnim.PushBack({ 688, 426, 28, 28 });
	disappearingAnim.PushBack({ 654, 426, 32, 32 });
	disappearingAnim.PushBack({ 616, 426, 36, 36 });
	disappearingAnim.PushBack({ 586, 426, 28, 28 });
	disappearingAnim.PushBack({ 554, 426, 30, 30 });
	disappearingAnim.PushBack({ 520, 426, 32, 32 });
	disappearingAnim.PushBack({ 520, 426, 32, 32 });
	disappearingAnim.PushBack({ 721, 388, 28, 28 });
	disappearingAnim.PushBack({ 687, 388, 32, 32 });
	disappearingAnim.PushBack({ 649, 388, 36, 36 });
	disappearingAnim.PushBack({ 619, 387, 28, 28 });
	disappearingAnim.PushBack({ 587, 388, 30, 30 });
	disappearingAnim.PushBack({ 553, 388, 32, 32 });
	disappearingAnim.PushBack({ 523, 388, 28, 28 });
	disappearingAnim.speed = 0.25f;
	disappearingAnim.loop = false;

	movingAnim.PushBack({ 658, 538, 32, 32 });
	movingAnim.PushBack({ 519, 578, 32, 32 });
	movingAnim.PushBack({ 552, 579, 32, 32 });
	movingAnim.PushBack({ 584, 577, 32, 32 });
	movingAnim.speed = 0.25f;
	movingAnim.loop = true;

	animation = &appearingAnim;

	//Add collider
	collider = App->collision->AddCollider({ position.x - animation->GetFrame().w / 2, y - animation->GetFrame().h / 2 , animation->GetFrame().w, animation->GetFrame().h}, COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}

void Enemy_Lamella::Move()
{
	switch(lamellaPhase)
	{
	case appearing:
		//Check if it has finished appearing
		if (animation->Finished())
		{
			//Change phase
			lamellaPhase = moving;
			animation = &movingAnim;

			//Select the player it has to move to
			if (App->player1->isActive && App->player2->isActive)
			{
				//- Check which is nearer
				if (position.DistanceTo(App->player1->position + App->player1->playerCenter) <=
					position.DistanceTo(App->player2->position + App->player2->playerCenter))
				{
					targetPos = App->player1->position + App->player1->playerCenter;
				}
				else
				{
					targetPos = App->player2->position + App->player2->playerCenter;
				}
			}
			else if (App->player1->isActive && !App->player2->isActive)
			{
				targetPos = App->player1->position + App->player1->playerCenter;
			}
			else if (!App->player1->isActive && App->player2->isActive)
			{
				targetPos = App->player2->position + App->player2->playerCenter;
			}
		}
		break;
	case moving:
		if(position.DistanceTo(targetPos) > moveSpeed)
		{
			fPoint direction;
			//We get the unit vector from the position to the target position
			direction.UnitVector({ (float)targetPos.x, (float)targetPos.y }, { (float)position.x, (float)position.y });
			//Move
			auxPos.x += direction.x * moveSpeed;
			auxPos.y += direction.y * moveSpeed;
			//Set the position
			position.x = (int)auxPos.x;
			position.y = (int)auxPos.y;
		}
		else
		{
			//If it has reached the position, disappear
			position = targetPos;
			lamellaPhase = disappearing;
			animation = &disappearingAnim;
		}
		break;
	case disappearing:
		//Check if it has finished disappearing to despawn it
		//killed = true?
		break;
	}

	//Get current frame (we need it to adjust the collider's position correctly)
	currentFrame = animation->GetCurrentFrame();

	//Set colliders
	if(collider != nullptr)
	{
		collider->SetPos(position.x - currentFrame.w / 2, position.y - currentFrame.h / 2);
	}
}

void Enemy_Lamella::Draw(SDL_Texture* sprites)
{
	//Blit
	App->render->Blit(sprites, position.x - currentFrame.w/2, position.y - currentFrame.h/2, &currentFrame);
}