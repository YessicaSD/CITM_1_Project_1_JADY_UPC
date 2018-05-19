#include "Application.h"
#include "Powerup_Laser.h"
#include "ModuleCollision.h"
#include "Player1.h"
#include "Player2.h"
#include "Globals.h"
#include "ModulePowerups.h"
#include "ModuleUnit.h"

Powerup_Laser::Powerup_Laser(int x, int y) : Powerup(x, y)
{
	//Push backs
	laserAnim.PushBack({ 18, 80, 31, 16 });
	laserAnim.PushBack({ 49, 80, 31, 16 });
	laserAnim.speed = 0.01f;
	laserAnim.loop = true;
	//We set the animation of the base class to be this animation
	animation = &laserAnim;

	collider = App->collision->AddCollider({ 0, 0, 31, 16 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_Laser::OnCollision(Collider* col)
{
	//We find which player got this powerup
	if(col == App->player1->playerCol)
	{
		//We give it this powerup
		if ( App->player1->powerupUpgrades < 3)
		{
			App->player1->powerupUpgrades++;
		}
		if ( App->player1->powerupUpgrades == 1)
		{
			App->unit1->Enable();
			App->unit1->playerToFollow = App->player1;
			App->unit1->position.x = App->player1->position.x + App->player1->playerCenter.x;
			App->unit1->position.y = App->player1->position.y + App->player1->playerCenter.y;
			App->unit1->power = 0;
			App->unit1->unitPhase == UnitPhase::positioning;
		}
		//Change powerup type
		App->player1->currentPowerUp = POWERUP_TYPE::LASER;
		//Change unit type
		if((int)laserAnim.current_frame == 0)
		{
			App->unit1->MakeUnitOrange();
		}
		else
		{
			App->unit1->MakeUnitBlue();
		}
		
	}
	else if(col == App->player2->playerCol)
	{
		//We give it this powerup
		if (App->player2->powerupUpgrades < 3)
		{
			App->player2->powerupUpgrades++;
		}
		if (App->player2->powerupUpgrades == 1)
		{
			App->unit2->Enable();
			App->unit2->playerToFollow = App->player2;
			App->unit2->position.x = App->player2->position.x + App->player2->playerCenter.x;
			App->unit2->position.y = App->player2->position.y + App->player2->playerCenter.y;
			App->unit2->power = 0;
			App->unit2->playerToFollow = App->player2;
			App->unit2->unitPhase == UnitPhase::positioning;
		}
		//Change powerup type
		App->player2->currentPowerUp = POWERUP_TYPE::LASER;
		//Change unit type
		if ((int)laserAnim.current_frame == 0)
		{
			App->unit2->MakeUnitOrange();
		}
		else
		{
			App->unit2->MakeUnitBlue();
		}
	}
}