#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

#define ZOOMED_OUT_SIZE 5
#define ZOOMED_OUT_X_OFFSET 600//Change this to move the viewport to the left/right in zoomed out mode
#define ZOOMED_OUT_Y_OFFSET 440//Change this to move the viewport up/down in zoomed out mode
#define BORDER_WIDTH 2

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
		if(zoomedOut == false)
		{
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * ZOOMED_OUT_SIZE, SCREEN_HEIGHT * ZOOMED_OUT_SIZE);
			zoomedOut = true;
		}
		else
		{
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			zoomedOut = false;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//Render the camera borders, so we know where the camera is
	if (zoomedOut == true)
	{
		//Right border
		App->render->DrawQuad({ SCREEN_WIDTH, 0, BORDER_WIDTH, SCREEN_HEIGHT + BORDER_WIDTH }, 255, 255, 255, 255);
		//Down border
		App->render->DrawQuad({ 0, SCREEN_HEIGHT, SCREEN_WIDTH + BORDER_WIDTH, BORDER_WIDTH }, 255, 255, 255, 255);
		//Left border
		App->render->DrawQuad({ -BORDER_WIDTH, 0, BORDER_WIDTH, SCREEN_HEIGHT + BORDER_WIDTH }, 255, 255, 255, 255);
		//Up border
		App->render->DrawQuad({ -BORDER_WIDTH, 0, SCREEN_WIDTH + BORDER_WIDTH, BORDER_WIDTH }, 255, 255, 255, 255);
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

	//We render all the sprites to the center if we're in zoomed out mode
	if(zoomedOut == true)
	{
		rect.x += ZOOMED_OUT_X_OFFSET;
		rect.y += ZOOMED_OUT_Y_OFFSET;
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

	//We render all the sprites to the center if we're in zoomed out mode
	if (zoomedOut == true)
	{
		rec.x += ZOOMED_OUT_X_OFFSET;
		rec.y += ZOOMED_OUT_Y_OFFSET;
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

	//We render all the sprites to the center if we're in zoomed out mode
	if (zoomedOut == true)
	{
		rect.x += ZOOMED_OUT_X_OFFSET;
		rect.y += ZOOMED_OUT_Y_OFFSET;
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



