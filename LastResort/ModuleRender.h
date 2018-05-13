#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "p2Point.h"

struct SDL_Renderer;
struct SDL_Texture;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	/*void Render(SDL_Texture* Texture, SDL_Rect* section);*/
	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);
	bool FlippedBlit(SDL_Texture* texture, int x, int y, SDL_Rect* section);
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
};

#endif //__ModuleRenderer_H__