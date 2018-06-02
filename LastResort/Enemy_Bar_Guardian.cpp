#include "Application.h"
#include "Enemy_Bar_Guardian.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"
#include "ModuleEnemies.h"


Enemy_BarGuardian::Enemy_BarGuardian(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	//Animation-------------------------------------
	closingEye.PushBack({ 330, 493, 16, 74 });
	closingEye.PushBack({ 314, 493, 16, 74 });
	closingEye.loop = false;
	closingEye.speed = 0.25f;
	openingEye.PushBack({ 314, 493, 16, 74 });
	openingEye.PushBack({ 330, 493, 16, 74 });
	openingEye.loop = false;
	openingEye.speed = 0.25f;
	eyeOpen.PushBack   ({ 346, 493, 16, 74 });
	eyeClosed.PushBack ({ 298, 493, 16, 74 });
	animation = &eyeClosed;
	backAnim = { 364, 493, 30,  80 };
	topBarAnim = { 233, 460, 32, 128 };
	botBarAnim = { 265, 460, 32, 128 };
	//Render layer----------------------------------
	renderLayer = 0;
	//Collider--------------------------------------
	collider  = App->collision->AddCollider({ x - 16 + 2, y - backAnim.h/2,      backAnim.w + 16 - 2,   backAnim.h }, COLLIDER_TYPE::COLLIDER_IGNORE_HIT, (Module*)App->enemies);
	topBarCol = App->collision->AddCollider({ x -  8, y - 24 - topBarAnim.h, topBarAnim.w, topBarAnim.h }, COLLIDER_TYPE::COLLIDER_WALL);
	botBarCol = App->collision->AddCollider({ x -  8, y + 24,                topBarAnim.w, topBarAnim.h }, COLLIDER_TYPE::COLLIDER_WALL);
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
	//Set the bar positions
	topBarPos.x = position.x -  8;
	topBarPos.y = position.y - 24 - topBarAnim.h;
	botBarPos.x = position.x - 8;
	botBarPos.y = position.y + 24;

	//Set the collider position
	if (collider  != nullptr) { collider ->SetPos(position.x - 16 + 2, position.y - backAnim.h / 2); }
	if (topBarCol != nullptr) { topBarCol->SetPos(topBarPos.x, topBarPos.y); }
	if (botBarCol != nullptr) { botBarCol->SetPos(botBarPos.x, botBarPos.y); }

	//Eye logic
	switch (eyePhase)
	{
	case open:
		if(eyeCounter >= 240)
		{
			eyePhase = closing;
			animation = &closingEye;
			eyeCounter = 0;
		}
		else
		{
			eyeCounter++;
		}
		break;
	case closing:
		if (animation->Finished())
		{
			animation = &eyeClosed;
			collider->type = COLLIDER_IGNORE_HIT;//Only lose health when it's open
			eyePhase = closed;
			eyeCounter = 0;
		}
		break;
	case closed:
		if (eyeCounter >= 120)
		{
			eyePhase = opening;
			collider->type = COLLIDER_ENEMY_LIGHT;
			animation = &openingEye;
			eyeCounter = 0;
		}
		else
		{
			eyeCounter++;
		}
		break;
	case opening:
		if (animation->Finished())
		{
			animation = &eyeOpen;
			eyePhase = open;
			eyeCounter = 0;
		}
		break;
	}


	//Shoot
}

void Enemy_BarGuardian::Draw(SDL_Texture* sprites)
{
	//Blit top bar
	App->render->Blit(sprites, topBarPos.x, topBarPos.y, &topBarAnim);
	//Blit bot bar
	App->render->Blit(sprites, botBarPos.x, botBarPos.y, &botBarAnim);//24 distance from the center of the enemy
	//Blit back part
	App->render->Blit(sprites, position.x, position.y - backAnim.h / 2, &backAnim);
	//Blit eye
	App->render->Blit(sprites, position.x - 16, position.y - 74/2 + 1, &animation->GetCurrentFrame());
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

	//When it dies put two bar enemies in place
	App->enemies->AddEnemy(TOP_BAR,
		topBarPos.x + topBarAnim.w / 2 - App->stage05->spawnPos.x,
		topBarPos.y + topBarAnim.h / 2 - App->stage05->spawnPos.y,
		0,
		NOPOWERUP,
		{ 0, 0 });
 	//App->enemies->AddEnemy(TOP_BAR,
		//position.x - 8 + topBarAnim.w / 2 - App->stage05->spawnPos.x ,
		//position.y - 24 - topBarAnim.h / 2 - App->stage05->spawnPos.y ,
		//0,
		//NOPOWERUP,
		//{ 0, 0 });
}