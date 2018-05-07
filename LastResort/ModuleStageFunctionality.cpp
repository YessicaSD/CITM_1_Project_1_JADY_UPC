#include "Application.h"
#include "ModuleStageFunctionality.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePowerups.h"
#include "ModuleUnit.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStage01.h"
#include "ModuleStage02.h"
#include "ModuleStage05.h"
#include "ModuleStageClear.h"
#include "ModuleGameOver.h"
#include "ModuleNeoGeo.h"
#include "ModuleGameTitle.h"
#include "ModuleReady.h"
#include "ModuleContinue.h"

ModuleStageFunctionality::ModuleStageFunctionality()
{

}

ModuleStageFunctionality::~ModuleStageFunctionality()
{

}

bool ModuleStageFunctionality::Start()
{
	App->player1->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	//App->ui->ShowUi();
	//App->ui->current_stage = this;
	return true;
}

bool ModuleStageFunctionality::CleanUp()
{
	App->player1->Disable();
	App->player2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->powerups->Disable();
	return true;
}

update_status ModuleStageFunctionality::PreUpdate()
{
	Debugging();
	return UPDATE_CONTINUE;
}

void ModuleStageFunctionality::Debugging()
{
	//SELECTION ELEMENT------------------------------------------
	//- Select scene
	if(App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		debugElem = DebugElement::scene;
		selectedElemNum = -1;
	}
	//- Select checkpoint (to implement when checkpoints are added)
	//- Select enemy
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN)
	{
		debugElem = DebugElement::enemy;
		selectedElemNum = -1;
	}
	//- Select powerup
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN)
	{
		debugElem = DebugElement::powerup;
		selectedElemNum = -1;
	}

	//CHOSE ELEMENT-----------------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) { ChooseDebugElem(0); }
	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN) { ChooseDebugElem(1); }
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN) { ChooseDebugElem(2); }
	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN) { ChooseDebugElem(3); }
	if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN) { ChooseDebugElem(4); }
	if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN) { ChooseDebugElem(5); }
	if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN) { ChooseDebugElem(6); }
	if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN) { ChooseDebugElem(7); }
	if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN) { ChooseDebugElem(8); }
	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN) { ChooseDebugElem(9); }

	//DEBUG!------------------------------------------------------
	if(App->input->keyboard[SDL_SCANCODE_F9] == KEY_DOWN)
	{
		switch(debugElem)
		{
		case DebugElement::scene:
			GoToScene();
			break;
		//case DebugElement::checkpoint:
		//	break;
		case DebugElement::enemy:
			App->enemies->AddEnemy((ENEMY_TYPES)selectedElemNum, App->player1->position.x + 100, App->player1->position.y);
			break;
		case DebugElement::powerup:
			App->powerups->AddPowerup(App->player1->position.x + 100, App->player1->position.y, (POWERUP_TYPE)selectedElemNum);
			break;
		}		
	}
}

void ModuleStageFunctionality::ChooseDebugElem(int numberPressed)
{
	if (selectedElemNum == -1)
	{
		//If we haven't pressed any number before, we put that number
		selectedElemNum = numberPressed;
	}
	else
	{
		//If we have pressed a number before, we put this number on the tens and add the number we pressed
		selectedElemNum = selectedElemNum * 10 + numberPressed;
	}
	//Check that it doesn't surpass its maximum element
	if (debugElem == DebugElement::scene)
	{
		if(selectedElemNum > 11)//11 = number of scenes currently in the game
		{
			selectedElemNum = 11;
		}
	}
	else if (debugElem == DebugElement::enemy)
	{
		if (selectedElemNum >= ENEMY_TYPES::MAX_ENEMY)
		{
			selectedElemNum = ENEMY_TYPES::MAX_ENEMY - 1;
		}
	}
	else if (debugElem == DebugElement::powerup)
	{
		if (selectedElemNum >= POWERUP_TYPE::MAX_POWERUP)
		{
			selectedElemNum = POWERUP_TYPE::MAX_POWERUP - 1;
		}
	}
}

void ModuleStageFunctionality::GoToScene()
{
	switch (selectedElemNum)
	{
	case 1:
		//STAGE 1
		App->fade->FadeToBlack(currentStage, App->stage01, 0.5f);
		break;
	case 2:
		//STAGE 2
		App->fade->FadeToBlack(currentStage, App->stage02, 0.5f);
		break;
		//case 3:
		//	//STAGE 3
		//	break;
		//case 4:
		//	//STAGE 4
		//	break;
	case 5:
		//STAGE 5
		App->fade->FadeToBlack(currentStage, App->stage05, 0.5f);
		break;
	case 6:
		//WIN SCREEN
		if (App->player1->winlvl == false && App->player2->winlvl == false)
		{
			App->player1->winlvl = App->player2->winlvl = true;
			App->player1->numLvlwin = App->player2->numLvlwin = 1;
		}
		App->fade->FadeToBlack(currentStage, App->stageclearScene, 3.5f);
		App->unit1->Disable();
		App->unit2->Disable();
		currentStage = nullptr;
		break;
	case 7:
		//LOSE SCREEN
		App->fade->FadeToBlack(currentStage, App->gameoverScene, 3.5f);
		App->unit1->Disable();
		App->unit2->Disable();
		currentStage = nullptr;
		break;
	case 8:
		//NEO GEO SCREEEN
		App->fade->FadeToBlack(currentStage, App->neogeoScene, 3.5f);
		break;
	case 9:
		//LAST RESORT SCREEN
		App->fade->FadeToBlack(currentStage, App->titleScene, 3.5f);
		break;
	case 10:
		//READY SCREEN
		App->fade->FadeToBlack(currentStage, App->readyScene, 3.5f);
		break;
	case 11:
		//CONTINUE SCREEN
		App->fade->FadeToBlack(currentStage, App->continueScene, 3.5f);
		break;
	}
}