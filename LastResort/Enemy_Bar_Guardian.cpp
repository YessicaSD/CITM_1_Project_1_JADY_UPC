#include "Application.h"
#include "Enemy_Bar_Guardian.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"


Enemy_BarGuardian::Enemy_BarGuardian(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animation-------------------------------------
	//eyeAnim.PushBack();
	backAnim = { 364, 493, 30,  80 };
	topBarAnim = { 233, 460, 32, 128 };
	botBarAnim = { 265, 460, 32, 128 };
	//Render layer----------------------------------
	renderLayer = 0;
	//Collider--------------------------------------
	collider  = App->collision->AddCollider({ x,     y - backAnim.h/2,      backAnim.w,   backAnim.h   }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
	topBarCol = App->collision->AddCollider({ x - 8, y - 24 - topBarAnim.h, topBarAnim.w, topBarAnim.h }, COLLIDER_TYPE::COLLIDER_WALL);
	botBarCol = App->collision->AddCollider({ x - 8, y + 24,                topBarAnim.w, topBarAnim.h }, COLLIDER_TYPE::COLLIDER_WALL);
}

void Enemy_BarGuardian::Move()
{
	//Move
	switch(phase)
	{
	case barGuard_Up:
		accumulatedY -= moveSpeed;
		if(accumulatedY <= -1)
		{
			position.y -= 1;
			accumulatedY += 1;
		}
		//Go down if it reaches the top
		if(position.y <= 0 + 63)//INFO: 63 = Offset at which it changed direction
		{
			transitionCounter = 0;
			phase = barGuard_Transition;
		}
		break;

	case barGuard_Down:
		accumulatedY += moveSpeed;
		if (accumulatedY >= 1)
		{
			position.y += 1;
			accumulatedY -= 1;
		}
		//Go up if it reaches the bottom
		if (position.y >= SCREEN_HEIGHT - 63)
		{
			transitionCounter = 0;
			phase = barGuard_Transition;
		}
		break;
	case barGuard_Transition:
		if(transitionCounter >= 5)
		{
			if (position.y < SCREEN_HEIGHT / 2)
			{
				phase = barGuard_Down;
			}
			else
			{
				phase = barGuard_Up;
			}
		}
		else
		{
			transitionCounter++;
		}
		break;
	}
	//Set the collider position
	if (collider  != nullptr) { collider ->SetPos(position.x    , position.y - backAnim.h / 2); }
	if (topBarCol != nullptr) { topBarCol->SetPos(position.x - 8, position.y - 24 - topBarAnim.h); }
	if (botBarCol != nullptr) { botBarCol->SetPos(position.x - 8, position.y + 24); }

	//Eye logic




	//Shoot
}

void Enemy_BarGuardian::OnCollision(Collider* c2)
{
	//Only lose health if it is open (look at ship motor)
	//When it dies put two bar enemies in place
}

void Enemy_BarGuardian::Draw(SDL_Texture* sprites)
{
	//Blit top bar
	App->render->Blit(sprites, position.x - 8, position.y - 24 - topBarAnim.h, &topBarAnim);
	//Blit bot bar
	App->render->Blit(sprites, position.x - 8, position.y + 24, &botBarAnim);//24 distance from the center of the enemy
	//Blit back part
	App->render->Blit(sprites, position.x, position.y - backAnim.h / 2, &backAnim);
	//Blit eye
}

Enemy_BarGuardian::~Enemy_BarGuardian()
{
	if (collider != nullptr)
	{
		collider->to_delete = true;
	}
	if (topBarCol != nullptr)
	{
		topBarCol->to_delete = true;
	}
	if (botBarCol != nullptr)
	{
		botBarCol->to_delete = true;
	}
}