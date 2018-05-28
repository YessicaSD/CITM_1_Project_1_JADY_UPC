#ifndef _MODULEUI_H_
#define _MODULEUI_H_
#include "Module.h"
#include "Globals.h"

#define MAX_NUMBERS_SCORE 6

struct SDL_Texture;
struct SDL_Rect;
struct Sfx;
class ModulePlayer;


enum sceneType {
	NONE,
	TITLE_SCENE,
	STAGE_SCENE,
	CONTINUE_SCENE
};

enum uiState {
	COMPLETE,
	CONTINUE,
	GAME_OVER,
	INSERT_COIN,
	PUSH_BUTTON
};

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status InputUpdate();
	update_status LogicUpdate();
	update_status RenderUpdate2();
	bool CleanUp();

	void HideUi();
	void ShowUi();


public:

	//Player data---------------------------------
	uiState uiP1, uiP2;
	sceneType currentScene = NONE;

	//General data--------------------------------
	bool showUI = false;
	int credits = 0;

	char *str_score_p1 = nullptr;
	char *str_score_p2 = nullptr;
	char *str_lives_p1 = nullptr;
	char *str_lives_p2 = nullptr;
	char *str_credits = nullptr;
	char *str_debug = nullptr;
	//Audios-------------------------------------
	Sfx*coinsSfx=nullptr;
	//Textures------------------------------------
	SDL_Texture *uiTex = nullptr;
	//Rectangles---------------------------------
	SDL_Rect lives_score_p1;
	SDL_Rect live_score_p2;
	SDL_Rect pow;
	SDL_Rect powBar;
	SDL_Rect top;
	SDL_Rect push_p2;
};
#endif // !_MODULEUI_H_
