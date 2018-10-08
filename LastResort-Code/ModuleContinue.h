#ifndef _ModuleContinue_H_
#define _ModuleContinue_H_
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct  Music;

class ModuleContinue : public Module
{
public:
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status LogicUpdate();
	bool CleanUp();
private:
	bool time_finished = false;
	bool rest_bgAlpha = true;
	int number = NULL;
	float bgAlpha = NULL;
	SDL_Rect background_rect;
	SDL_Rect continue_rect;
	Animation numbersAnim;
	Animation fireAnim[8];
	SDL_Texture* backgroundTex = nullptr;
	SDL_Texture* continueTex = nullptr;
public:
	Music* continue_and_go = nullptr; 
	//needs to be public because in case that music is not stopped here, we stop it in game over
};
#endif // !_ModuleContinue_H_
