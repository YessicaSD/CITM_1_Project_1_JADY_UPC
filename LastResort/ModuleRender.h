#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

struct SDL_Renderer;
struct SDL_Texture;


class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status InputUpdate();
	update_status ScreenUpdate();
	bool CleanUp();

	/*void Render(SDL_Texture* Texture, SDL_Rect* section);*/
	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);
	bool BlitEx(SDL_Texture* texture, int x, int y, SDL_Rect* section, SDL_RendererFlip axis = SDL_FLIP_HORIZONTAL,double angle=NULL);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void ResetMovedPosition();
	void AddZoomAndMovedPosition(SDL_Rect&);

public:
	iPoint camera;
	SDL_Renderer* renderer = nullptr;
	iPoint movedPosition;

	//Zoom out
	int zoomedOutSize = 1;
	bool showWorldGrid = false;
	bool showTilemapGrid = false;
	bool showSpawnArea = false;
};

#endif //__ModuleRenderer_H__