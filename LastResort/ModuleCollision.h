#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 70

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = 0,//A collider that doesn't generate any collision
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_1_SHOT,
	COLLIDER_PLAYER_2_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_UNIT,
	COLLIDER_POWERUP,
	COLLIDER_GOD,//Collider the player gets on god mode
	COLLIDER_HIT_DETECTION_WALL,//The unit needs this collider to know when it collides with a wall
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	int damage = 1;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetDamage(int dmg) {
		damage = dmg;
	}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__