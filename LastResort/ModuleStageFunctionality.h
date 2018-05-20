#ifndef __ModuleStageFunctionality_H__
#define __ModuleStageFunctionality_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

enum debuggingElement
{
	NOTHING = 0,
	SCENES,
	CHECKPOINTS,
	ENEMIES,
	POWERUPS
};

class ModuleStageFunctionality : public Module
{
public:

	ModuleStageFunctionality();
	~ModuleStageFunctionality();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

	void Debugging();
	void ChooseDebugElem(int, bool &, int &, int, int);
	void GoToScene();

public:
	int selectedScene = 1;
	int selectedCheckpoint = 0;
	int selectedEnemy = 0;
	int selectedPowerup = 0;

	//Bools that indicate us if the player has pressed another letter before this one
	bool pressedNumScene = false;
	bool pressedNumCheckpoint = false;
	bool pressedNumEnemy = false;
	bool pressedNumPowerup = false;

	//Bools that indicate us what is the last element you're debugging
	debuggingElement debugElem = NOTHING;

	Module * currentStage = nullptr;

	SDL_Texture* PlayerTexture = nullptr;
	SDL_Texture* SpeedAnimationTex = nullptr;
};

#endif // __ModuleStageFunctionality_H_H__
