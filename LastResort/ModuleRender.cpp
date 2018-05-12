#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

#define ZOOMED_OUT_X_OFFSET 152//These values help to center the image
#define ZOOMED_OUT_Y_OFFSET 111
#define BORDER_WIDTH 1
#define MAX_ZOOM 5

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

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{	
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		zoomedOutSize++;
		//If we get to the maximum zoom, we go back to normal
		if (zoomedOutSize > MAX_ZOOM) { zoomedOutSize = 1; }
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * zoomedOutSize, SCREEN_HEIGHT * zoomedOutSize);
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//Render the camera borders, so we know where the camera is
	//INFO: Border width is multiplied by zoomedOutSize to mantain its size across all the zoomed out modes
	if (zoomedOutSize != 1)
	{
		//Up border
		App->render->DrawQuad({ -BORDER_WIDTH * zoomedOutSize, -BORDER_WIDTH * zoomedOutSize, SCREEN_WIDTH + BORDER_WIDTH * zoomedOutSize * 2, BORDER_WIDTH * zoomedOutSize }, 255, 255, 255, 255);
		//Down border
		App->render->DrawQuad({ -BORDER_WIDTH * zoomedOutSize, SCREEN_HEIGHT, SCREEN_WIDTH + BORDER_WIDTH * zoomedOutSize * 2, BORDER_WIDTH * zoomedOutSize }, 255, 255, 255, 255);
		//Left border
		App->render->DrawQuad({ -BORDER_WIDTH * zoomedOutSize, 0, BORDER_WIDTH * zoomedOutSize, SCREEN_HEIGHT}, 255, 255, 255, 255);
		//Right border
		App->render->DrawQuad({ SCREEN_WIDTH, 0, BORDER_WIDTH * zoomedOutSize, SCREEN_HEIGHT}, 255, 255, 255, 255);
	}

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

	//We render all the sprites to the center (for zoomed out mode)
	if (zoomedOutSize != 1)
	{
		rect.x += SCREEN_WIDTH * (zoomedOutSize - 1) / 2;
		rect.y += SCREEN_HEIGHT * (zoomedOutSize - 1) / 2;
	}

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

	//We render all the sprites to the center (for zoomed out mode)
	if (zoomedOutSize != 1)
	{
		rec.x += SCREEN_WIDTH * (zoomedOutSize - 1) / 2;
		rec.y += SCREEN_HEIGHT * (zoomedOutSize - 1) / 2;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

//Blit that flips the texture horizontally
bool ModuleRender::FlippedBlit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;

	rect.x = x * SCREEN_SIZE;
	rect.y = y * SCREEN_SIZE;

	//We render all the sprites to the center (for zoomed out mode)
	if (zoomedOutSize != 1)
	{
		rect.x += SCREEN_WIDTH * (zoomedOutSize - 1) / 2;
		rect.y += SCREEN_HEIGHT * (zoomedOutSize - 1) / 2;
	}

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

	
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, NULL, NULL, SDL_FLIP_HORIZONTAL) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}



