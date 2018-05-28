#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePowerups.h"
#include "Powerup.h"
#include "Powerup_Speed.h"
#include "Powerup_Laser.h"
#include "Powerup_G.h"
#include "Powerup_Homing.h"
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
	LOG("Loading powerup module ");
	powerupTx     = App->textures->Load("Assets/PowerUps/PowerUps.png");
	speedSFX      = App->audio->LoadSFX("Assets/PowerUps/019. Move speed upgrade.wav");
	getPowerupSFX = App->audio->LoadSFX("Assets/Powerups/GetPowerup.wav");
	return true;
}

update_status ModulePowerups::LogicUpdate()
{
	//Move the powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			//- Move
			if (powerups[i]->collider != nullptr)
			{
				powerups[i]->position.x -= (int)moveSpeed;
			}
			//- Adjust collider
			if (powerups[i]->collider != nullptr)
			{
				powerups[i]->collider->SetPos(powerups[i]->position.x, powerups[i]->position.y);
			}
		}
	}

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

update_status ModulePowerups::RenderUpdate2()
{
	//Render the powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			if (powerups[i]->animation != nullptr)
			{
				App->render->Blit(powerupTx, powerups[i]->position.x, powerups[i]->position.y, &powerups[i]->animation->GetCurrentFrame());
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
	App->audio->UnloadSFX(speedSFX);
	App->audio->UnloadSFX(getPowerupSFX);

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
				powerups[i] = new Powerup_Homing(x, y);
				powerups[i]->type = HOMING;
				break;
			case POWERUP_TYPE::GROUND:
				powerups[i] = new Powerup_G(x, y);
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
	ModulePlayer* targetPlayer = nullptr;
	ModuleUnit* targetUnit = nullptr;

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && c1 == powerups[i]->collider && (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_GOD) )
		{
			//We find which player got this powerup
			if (c2 == App->player1->playerCol)
			{
				targetPlayer = App->player1;
				targetUnit   = App->unit1;
			}
			else if (c2 == App->player2->playerCol)
			{
				targetPlayer = App->player2;
				targetUnit   = App->unit2;
			}


			//If powerup type is Speed or Despeed
			if (powerups[i]->type == SPEED || powerups[i]->type == DESPEED)
			{
				//Simply call the powerup OnCollision
				powerups[i]->OnCollision(c2, targetPlayer);
			}
			else
			{
				//Play the sound for getting a L, H or G powerup
				App->audio->ControlSFX(getPowerupSFX, PLAY_AUDIO);

				//We give it this powerup
				if (targetPlayer->powerupUpgrades < 4)//There are a maximum of 4 upgrades for each powerup
				{
					targetPlayer->powerupUpgrades++;
				}
				if (targetPlayer->powerupUpgrades == 1)
				{
					targetUnit->Enable();
					targetUnit->playerToFollow = targetPlayer;
					targetUnit->position.x = targetPlayer->position.x + targetPlayer->playerCenter.x;
					targetUnit->position.y = targetPlayer->position.y + targetPlayer->playerCenter.y;
					targetUnit->power = 0;
					targetUnit->unitPhase = UnitPhase::returning;
				}

				//Change unit color
				if ((int)powerups[i]->animation->current_frame == 0) { targetUnit->MakeUnitOrange(); }
				else { targetUnit->MakeUnitBlue(); }

				//Call the specific powerup OnCollision
				powerups[i]->OnCollision(c2, targetPlayer);
			}

			delete powerups[i];
			powerups[i] = nullptr;
			break;
		}
	}
}