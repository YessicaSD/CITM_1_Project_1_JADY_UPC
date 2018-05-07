#ifndef __ModuleStageFunctionality_H__
#define __ModuleStageFunctionality_H__

#include "Module.h"
#include "Globals.h"

class ModuleStageFunctionality : public Module
{
public:

	ModuleStageFunctionality();
	~ModuleStageFunctionality();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

	void Debugging();
	void ChooseDebugElem(int, bool &, int &, int);
	void GoToScene();

public:
	int selectedScene = 1;
	//int selectedCheckpoint = 1;//= the first checkpoint of the game
	int selectedEnemy = 0;
	int selectedPowerup = 0;

	//Bools that indicate us if the player has pressed another letter before this one
	bool pressedNumScene = false;
	//bool pressedNumCheckpoint = false;
	bool pressedNumEnemy = false;
	bool pressedNumPowerup = false;

	Module * currentStage = nullptr;
};

#endif // __ModuleStageFunctionality_H_H__
