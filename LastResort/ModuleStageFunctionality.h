#ifndef __ModuleStageFunctionality_H__
#define __ModuleStageFunctionality_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;
struct Mix_Chunk;

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
	//Advanced debugger------------------------------------------------
	debuggingElement debugElem = NOTHING;
	//- Selected element
	int selectedScene = 1;
	int selectedCheckpoint = 0;
	int selectedEnemy = 0;
	int selectedPowerup = 0;
	//- Bools that indicate us if the player has pressed another letter before this one
	bool pressedNumScene = false;
	bool pressedNumCheckpoint = false;
	bool pressedNumEnemy = false;
	bool pressedNumPowerup = false;
	//- Other
	Module * currentStage = nullptr;

	//Assets------------------------------------------------------------
	//Textures
	SDL_Texture* PlayerTexture = nullptr;
	SDL_Texture* SpeedAnimationTex = nullptr;
	//SFX
	SFX releaseChargeSFX;
	SFX chargeSFX;
	SFX lockUnitSFX;
	SFX unlockUnitSFX;

	//Other-------------------------------------------------------------
	bool godMode = false;
};

#endif // __ModuleStageFunctionality_H_H__
