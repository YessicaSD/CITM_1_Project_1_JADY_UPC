#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePowerups.h"
#include "Powerup.h"
#include "Powerup_Speed.h"
#include "Powerup_Laser.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleUnit.h"


ModulePowerups::ModulePowerups()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerups[i] = nullptr;
}

ModulePowerups::~ModulePowerups()
{

}

bool ModulePowerups::Start()
{
	powerupTx = App->textures->Load("Assets/PowerUps/PowerUps.png");
	SpeedSfx = App->audio->LoadSFX("Assets/PowerUps/019. Move speed upgrade.wav");
	return true;
}

update_status ModulePowerups::Update()
{
	//Move the powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			//- Collider
			if (powerups[i]->collider != nullptr)
			{
				powerups[i]->position.x -= (int)moveSpeed;
			}
		}
	}

	//Render the powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			//- Collider
			if (powerups[i]->collider != nullptr)
			{
				powerups[i]->collider->SetPos(powerups[i]->position.x, powerups[i]->position.y);
			}
			//- Sprite
			if (powerups[i]->animation != nullptr)
			{
				App->render->Blit(powerupTx, powerups[i]->position.x, powerups[i]->position.y, &powerups[i]->animation->GetCurrentFrame());
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModulePowerups::PostUpdate()
{
	//Check camera position to decide what to despawn
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			if (powerups[i]->position.x < 0 - DESPAWN_MARGIN_LEFT ||
				powerups[i]->position.y < 0 - DESPAWN_MARGIN_UP ||
				powerups[i]->position.y > 0 + SCREEN_HEIGHT + DESPAWN_MARGIN_DOWN ||
				powerups[i]->position.x > 0 + SCREEN_WIDTH + DESPAWN_MARGIN_RIGHT)
			{
				LOG("DeSpawning powerup at x: %d, y: %d", powerups[i]->position.x, powerups[i]->position.y);
				delete powerups[i];
				powerups[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModulePowerups::CleanUp()
{
	LOG("Freeing all powerups");

	App->textures->Unload(powerupTx);

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}
	App->audio->UnloadSFX(SpeedSfx);
	return true;
}

bool ModulePowerups::AddPowerup(int x, int y, POWERUP_TYPE type)//x and y should be the position in which the enemy that drops the powerup has died
{
	bool ret = false;

	//Here we will have the code based on SpawnEnemy, because we'll be rendering the collider directly
	//Find room for the new powerup

	for (uint i = 0; i < MAX_POWERUPS; ++i) {

		if (powerups[i] == nullptr) {
			switch (type)
			{
			case POWERUP_TYPE::SPEED:
				powerups[i] = new Powerup_Speed(x, y);
				powerups[i]->type = SPEED;
				break;
			case POWERUP_TYPE::DESPEED:
				powerups[i] = new Powerup_Speed(x, y);
				powerups[i]->type = DESPEED;
				break;
			case POWERUP_TYPE::LASER:
				powerups[i] = new Powerup_Laser(x, y);
				powerups[i]->type = LASER;
				break;
			case POWERUP_TYPE::HOMING:
				powerups[i] = new Powerup_Laser(x, y);
				powerups[i]->type = HOMING;
				break;
			case POWERUP_TYPE::GROUND:
				powerups[i] = new Powerup_Laser(x, y);
				powerups[i]->type = GROUND;
				break;
			}
			break;
		}
	}

	//For now, we'll have speed for despeed and laser for homing and ground
	return ret;
}

void ModulePowerups::OnCollision(Collider* c1, Collider* c2)
{

	ModulePlayer* playerTarget = nullptr;
	ModuleUnit* unitTarget = nullptr;

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && c1 == powerups[i]->collider && (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_GOD) )
		{

			//We find which player got this powerup----------------------------------

			if (c2 == App->player1->playerCol) {
				playerTarget = App->player1;
				unitTarget = App->unit1;
			}
			else if (c2 == App->player2->playerCol) {
				playerTarget = App->player2;
				unitTarget = App->unit2;
			}


			//If powerup type is SPEED or DESPEED-----------------------------------

			if (powerups[i]->type == SPEED || powerups[i]->type == DESPEED) {

				powerups[i]->OnCollision(c2, playerTarget);
				delete powerups[i];
				powerups[i] = nullptr;
				break;

			}

			//We give it this powerup-----------------------------------------------

			if (playerTarget->powerupUpgrades < 3)
			{
				playerTarget->powerupUpgrades++;
			}
			if (playerTarget->powerupUpgrades == 1)
			{
				unitTarget->Enable();
				unitTarget->playerToFollow = App->player1;
				unitTarget->position.x = playerTarget->position.x + playerTarget->playerCenter.x;
				unitTarget->position.y = playerTarget->position.y + playerTarget->playerCenter.x;
				unitTarget->power = 0;
				unitTarget->unitPhase == UnitPhase::positioning;
			}

			//Change unit type-----------------------------------------------------

			if ((int)powerups[i]->animation->current_frame == 0)
			{
				unitTarget->MakeUnitOrange();
			}
			else
			{
				unitTarget->MakeUnitBlue();
			}

			//Callback PowerUp OnCollision-----------------------------------------
			powerups[i]->OnCollision(c2, playerTarget);


			delete powerups[i];
			powerups[i] = nullptr;
			break;
		}
	}
}