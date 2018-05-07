#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL_image\include\SDL_image.h"
#include "ModuleReady.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Player1.h"
#include "ModuleStage01.h"
#include "ModuleStage02.h"
#include "ModuleStage05.h"
#include "ModuleAudio.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"


ModuleStageReady::ModuleStageReady()
{

	// BackgroundsRect  


	//Ready
	BGroundReady.x = 0;
	BGroundReady.y = 112;
	BGroundReady.w = 80;
	BGroundReady.h = 16;

	//Black
	backgroundBlack.x = 0;
	backgroundBlack.y = 0;
	backgroundBlack.w = SCREEN_WIDTH;
	backgroundBlack.h = SCREEN_HEIGHT;

}

ModuleStageReady::~ModuleStageReady()
{}

// Load assets
bool ModuleStageReady::Start()
{
	LOG("Loading Ready Scene assets");
	bool ret = true;

	backgroundReady = App->textures->Load("Assets/UI.png");

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &backgroundBlack);
	start_time = SDL_GetTicks();

	return ret;
}

bool ModuleStageReady::CleanUp()
{
	//Remove all memory leaks

	LOG("Unloading Ready Scene assets");
	App->textures->Unload(backgroundReady);
	return true;
}


// Update: draw background

update_status ModuleStageReady::Update()
{
	// Draw everything

	//App->render->Blit(backgroundReady, 0, 0, NULL, 0.0f);
	current_time = (SDL_GetTicks() - start_time);
	if (current_time > 1000)
	{
		App->fade->FadeToBlack(this, App->stage05, 0.5f);
	}
	App->render->Blit(backgroundReady, 110 /*SCREEN_WIDTH/2*/, 100 /*SCREEN_HEIGHT/2*/, &BGroundReady); //MAGIC NUMBERS

	return UPDATE_CONTINUE;
}

