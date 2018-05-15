#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleStage05.h"
#include "ModuleEnemies.h"

#define DEFAULT_BORDER_WIDTH 1
#define MAX_ZOOM 5
#define MOVE_AMOUNT 5
#define AXIS_LENGTH 5000
#define MARK_LENGTH 20

ModuleRender::ModuleRender() : Module()
{

}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC ;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (WIN_FULLSCREEN_DESKTOP == 1)
	{
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	ResetMovedPosition();

	return ret;
}

void ModuleRender::ResetMovedPosition()
{
	movedPosition.x = 0;
	movedPosition.y = 0;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (App->input->keyboard[SDL_SCANCODE_KP_8] == KEY_REPEAT) { movedPosition.y += MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_4] == KEY_REPEAT) { movedPosition.x += MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_5] == KEY_REPEAT) { movedPosition.y -= MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_6] == KEY_REPEAT) { movedPosition.x -= MOVE_AMOUNT; }
	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_REPEAT) { ResetMovedPosition(); }
	if (App->input->keyboard[SDL_SCANCODE_KP_7] == KEY_DOWN)
	{
		if (zoomedOutSize < MAX_ZOOM)
		{
			zoomedOutSize++;
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * zoomedOutSize * SCREEN_SIZE, SCREEN_HEIGHT * zoomedOutSize * SCREEN_SIZE);
		}
	}
	if(App->input->keyboard[SDL_SCANCODE_KP_9] == KEY_DOWN)
	{
		if (zoomedOutSize > 1)
		{
			zoomedOutSize--;
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * zoomedOutSize * SCREEN_SIZE, SCREEN_HEIGHT * zoomedOutSize * SCREEN_SIZE);
		}
	}
	if(App->input->keyboard[SDL_SCANCODE_KP_DIVIDE] == KEY_DOWN)
	{
		if (showWorldGrid == true) { showWorldGrid = false; }
		else { showWorldGrid = true; }
	}
	if (App->input->keyboard[SDL_SCANCODE_KP_MULTIPLY] == KEY_DOWN)
	{
		if (showTilemapGrid == true) { showTilemapGrid = false; }
		else { showTilemapGrid = true; }
	}
	if (App->input->keyboard[SDL_SCANCODE_KP_PERIOD] == KEY_DOWN)
	{
		if (showSpawnArea == true) { showSpawnArea = false; }
		else { showSpawnArea = true; }
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	
	//- INFO: Border width is multiplied by zoomedOutSize to mantain its size across all the zoomed out modes
	int borderWidth = DEFAULT_BORDER_WIDTH * zoomedOutSize;

	//Render the spawn and despawn area--------------------------------------------------------------------------------------------------
	if(showSpawnArea)
	{
		//Spawn area
		App->render->DrawQuad({ -SPAWN_MARGIN_LEFT, -SPAWN_MARGIN_UP, SCREEN_WIDTH + SPAWN_MARGIN_LEFT + SPAWN_MARGIN_RIGHT, SPAWN_MARGIN_UP }, 255, 165, 0, 50);//Up
		App->render->DrawQuad({ -SPAWN_MARGIN_LEFT, SCREEN_HEIGHT, SCREEN_WIDTH + SPAWN_MARGIN_LEFT + SPAWN_MARGIN_RIGHT, SPAWN_MARGIN_DOWN }, 255, 165, 0, 50);//Down
		App->render->DrawQuad({ -SPAWN_MARGIN_LEFT, 0, SPAWN_MARGIN_LEFT, SCREEN_HEIGHT }, 255, 165, 0, 50);//Left
		App->render->DrawQuad({ SCREEN_WIDTH, 0, SPAWN_MARGIN_RIGHT, SCREEN_HEIGHT }, 255, 165, 0, 50);//Right
		//Despawn area
		App->render->DrawQuad({ -DESPAWN_MARGIN_LEFT, -DESPAWN_MARGIN_UP, SCREEN_WIDTH + DESPAWN_MARGIN_LEFT + DESPAWN_MARGIN_RIGHT, DESPAWN_MARGIN_UP }, 255, 0, 0, 50);//Up
		App->render->DrawQuad({ -DESPAWN_MARGIN_LEFT, SCREEN_HEIGHT, SCREEN_WIDTH + DESPAWN_MARGIN_LEFT + DESPAWN_MARGIN_RIGHT, DESPAWN_MARGIN_DOWN }, 255, 0, 0, 50);//Down
		App->render->DrawQuad({ -DESPAWN_MARGIN_LEFT, 0, DESPAWN_MARGIN_LEFT, SCREEN_HEIGHT }, 255, 0, 0, 50);//Left
		App->render->DrawQuad({ SCREEN_WIDTH, 0, DESPAWN_MARGIN_RIGHT, SCREEN_HEIGHT }, 255, 0, 0, 50);//Right
	}

	//Render the background grid------------------------------------------------------------------------------------------------------------
	if (showTilemapGrid)
	{
		//X marks
		for (int i = -AXIS_LENGTH + (int)App->stage05->spawnPos.x; i <= AXIS_LENGTH + (int)App->stage05->spawnPos.x; i += 100)
		{
			App->render->DrawQuad({ -borderWidth / 2 + i, -AXIS_LENGTH / 2, borderWidth, AXIS_LENGTH }, 123, 255, 123, 50);
		}
		//Y marks
		for (int i = -AXIS_LENGTH + (int)App->stage05->spawnPos.y; i <= AXIS_LENGTH + (int)App->stage05->spawnPos.y; i += 100)
		{
			App->render->DrawQuad({ -AXIS_LENGTH / 2, -borderWidth / 2 + i, AXIS_LENGTH, borderWidth }, 123, 255, 123, 50);
		}
		//X
		App->render->DrawQuad({ -AXIS_LENGTH / 2, -borderWidth / 2 + (int)App->stage05->spawnPos.y, AXIS_LENGTH, borderWidth }, 0, 255, 0, 123);
		//Y
		App->render->DrawQuad({ -borderWidth / 2 + (int)App->stage05->spawnPos.x, -AXIS_LENGTH / 2, borderWidth, AXIS_LENGTH }, 0, 255, 0, 123);
	}

	//Render the grids-------------------------------------------------------------------------------------------------------------------
	if(showWorldGrid)
	{
		//X marks
		for(int i = -AXIS_LENGTH; i <= AXIS_LENGTH; i += 100)
		{
			App->render->DrawQuad({ -borderWidth / 2 + i, -AXIS_LENGTH / 2, borderWidth, AXIS_LENGTH }, 123, 123, 255, 50);
		}
		//Y marks
		for (int i = -AXIS_LENGTH; i <= AXIS_LENGTH; i += 100)
		{
			App->render->DrawQuad({ -AXIS_LENGTH / 2, -borderWidth / 2 + i, AXIS_LENGTH, borderWidth }, 123, 123, 255, 50);
		}
		//X
		App->render->DrawQuad({ -AXIS_LENGTH / 2, -borderWidth / 2, AXIS_LENGTH, borderWidth }, 0, 0, 255, 123);
		//Y
		App->render->DrawQuad({ -borderWidth / 2, -AXIS_LENGTH / 2, borderWidth, AXIS_LENGTH }, 0, 0, 255, 123);
	}

	//Render the camera borders, so we know where the camera is--------------------------------------------------------------------------
	//Up border
	App->render->DrawQuad({ -borderWidth, -borderWidth, SCREEN_WIDTH + borderWidth * 2, borderWidth }, 255, 255, 255, 255);
	//Down border
	App->render->DrawQuad({ -borderWidth, SCREEN_HEIGHT, SCREEN_WIDTH + borderWidth * 2, borderWidth }, 255, 255, 255, 255);
	//Left border
	App->render->DrawQuad({ -borderWidth, 0, borderWidth, SCREEN_HEIGHT }, 255, 255, 255, 255);
	//Right border
	App->render->DrawQuad({ SCREEN_WIDTH, 0, borderWidth, SCREEN_HEIGHT }, 255, 255, 255, 255);

	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;

	rect.x = x * SCREEN_SIZE;
	rect.y = y * SCREEN_SIZE;

	AddZoomAndMovedPosition(rect);

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);

	rec.x *= SCREEN_SIZE;
	rec.y *= SCREEN_SIZE;
	rec.w *= SCREEN_SIZE;
	rec.h *= SCREEN_SIZE;

	AddZoomAndMovedPosition(rec);

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

//Blit that flips the texture horizontally
bool ModuleRender::BlitEx(SDL_Texture* texture, int x, int y, SDL_Rect* section, SDL_RendererFlip axis)
{
	bool ret = true;
	SDL_Rect rect;

	rect.x = x * SCREEN_SIZE;
	rect.y = y * SCREEN_SIZE;

	AddZoomAndMovedPosition(rect);

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, NULL, NULL, axis) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::AddZoomAndMovedPosition(SDL_Rect & rect)
{
	//Zooming and moving the viewport
	rect.x += (SCREEN_WIDTH * (zoomedOutSize - 1) / 2 + movedPosition.x)* SCREEN_SIZE; 
	rect.y += (SCREEN_HEIGHT * (zoomedOutSize - 1) / 2 + movedPosition.y)*SCREEN_SIZE;
}



