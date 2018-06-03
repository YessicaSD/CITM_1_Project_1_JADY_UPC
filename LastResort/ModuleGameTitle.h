#ifndef __MODULEGAMETITLE_H__
#define __MODULEGAMETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
struct  Music;

struct SDL_Texture;

class ModuleGameTitle : public Module
{
public:
	ModuleGameTitle();
	~ModuleGameTitle();

	bool Start();
	update_status LogicUpdate();
	bool CleanUp();

public:

	SDL_Texture * TitleTexture = nullptr;
	SDL_Texture *L1Texture =nullptr;
	SDL_Texture *A2Texture = nullptr;
	SDL_Texture *S3Texture = nullptr;
	SDL_Texture *T4Texture = nullptr;
	SDL_Texture *R5Texture = nullptr;
	SDL_Texture *E6Texture = nullptr;
	SDL_Texture *S7Texture = nullptr;
	SDL_Texture *O8Texture = nullptr;
	SDL_Texture *R9Texture = nullptr; //2LASTCHAR
	SDL_Texture *T10Texture = nullptr;
	SDL_Texture *neogeoTx = nullptr;

	//SDL_Rect LastResortRect;

	Animation L1;
	Animation A2;
	Animation S3;
	Animation T4;
	Animation R5;
	Animation E6;
	Animation S7;
	Animation O8;
	Animation R9;
	Animation T10;

	//Time variables
	Uint32 start_time; 
	Uint32 current_time;
	bool titleDone = false;
	int time=30;
	char*str_time;
	float speed = 0.3f;
	//audios
	Music* Titlemusic = nullptr;
};

#endif // __MODULEGAMETITLE_H__
