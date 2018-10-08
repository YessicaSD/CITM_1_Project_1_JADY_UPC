#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 25

class Module;

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleStage01;
class Player1;
class Player2;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleGameTitle;
class ModuleStageReady;
class Module2lvlScene;
class Module5lvlScene;
class ModuleGameOver;
class ModuleContinue;
class ModuleNeoGeo;
class ModuleParticles;
class ModuleCollision;
class ModuleEnemies;

class ModuleUnit;
class ModuleFonts;
class ModuleUI;
class ModulePowerups;
class ModuleStageFunctionality;



class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };

	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleStage01* stage01 = nullptr;
	Module2lvlScene* stage02 = nullptr;
	Module5lvlScene* stage05 = nullptr;
	Player1* player1 = nullptr;
	Player2* player2 = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleNeoGeo* neogeoScene = nullptr;
	ModuleGameTitle* titleScene = nullptr;
	ModuleStageReady* readyScene = nullptr;
	ModuleGameOver* gameoverScene = nullptr;
	ModuleContinue* continueScene = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleUnit * unit1 = nullptr;
	ModuleUnit * unit2 = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleUI* ui = nullptr;
	ModulePowerups* powerups = nullptr;
	ModuleStageFunctionality* stageFunctionality = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	//Custom variables
	bool pauseExecution = false;
	bool pauseNextFrame = false;
	bool showLayer0 = true;
	bool showLayer1 = true;
	bool showLayer2 = true;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__