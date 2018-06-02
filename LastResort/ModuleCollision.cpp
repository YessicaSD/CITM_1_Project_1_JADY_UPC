#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	//Collider none-----------------------------------------------------
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_WALL] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_GOD] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_IGNORE_HIT][COLLIDER_ENEMY_SHOT2] = false;

	//Collider wall-----------------------------------------------------
	matrix[COLLIDER_WALL][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_UNIT] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_WALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_WALL][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_WALL][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT2] = false;

	//Collider player---------------------------------------------------
	matrix[COLLIDER_PLAYER][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_LIGHT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_HEAVY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_UNIT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT2] = true;


	//Collider enemy light----------------------------------------------
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_UNIT] = true;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_ENEMY_LIGHT][COLLIDER_ENEMY_SHOT2] = false;

	//Collider enemy heavy----------------------------------------------
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_UNIT] = true;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_ENEMY_HEAVY][COLLIDER_ENEMY_SHOT2] = false;

	//Collider player 1 shot--------------------------------------------
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY_LIGHT] = true;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY_HEAVY] = true;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_PLAYER_1_SHOT][COLLIDER_ENEMY_SHOT2] = true;

	//Collider player 2 shot--------------------------------------------
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_LIGHT] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_HEAVY] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_SHOT2] = true;

	//Collider enemy shot-----------------------------------------------
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_UNIT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT2] = false;

	//Collider unit-----------------------------------------------------
	matrix[COLLIDER_UNIT][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_WALL] = false;
	matrix[COLLIDER_UNIT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY_LIGHT] = true;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY_HEAVY] = true;
	matrix[COLLIDER_UNIT][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_UNIT][COLLIDER_UNIT] = false;
	matrix[COLLIDER_UNIT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_UNIT][COLLIDER_GOD] = false;
	matrix[COLLIDER_UNIT][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_UNIT][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_UNIT][COLLIDER_ENEMY_SHOT2] = true;

	//Collider powerup--------------------------------------------------
	matrix[COLLIDER_POWERUP][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_UNIT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_GOD] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT2] = false;

	//Collider god------------------------------------------------------
	matrix[COLLIDER_GOD][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_GOD][COLLIDER_WALL] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GOD][COLLIDER_UNIT] = false;
	matrix[COLLIDER_GOD][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;	
	matrix[COLLIDER_GOD][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_GOD][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY_SHOT2] = false;

	//Collider hit detection wall---------------------------------------
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_WALL] = true;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_UNIT] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_GOD] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_HIT_DETECTION_WALL][COLLIDER_ENEMY_SHOT2] = false;

	// Collider shot industrictuble-------------------------------------------------------
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_UNIT] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE][COLLIDER_ENEMY_SHOT2] = false;

	// Collider hit detection enemy-------------------------------------------------------
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_ENEMY_LIGHT] = true;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_ENEMY_HEAVY] = true;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_PLAYER_1_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_UNIT] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_GOD] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_HIT_DETECTION_ENEMY][COLLIDER_ENEMY_SHOT2] = false;

	//Collider enemy shot 2 -----------------------------------------------------------------
	//This is just the same as enemy shot but this can be destroyed with the player shot (IMPORTANT)
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_IGNORE_HIT] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY_LIGHT] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY_HEAVY] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_PLAYER_1_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_UNIT] = true;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_HIT_DETECTION_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_HIT_DETECTION_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY_SHOT2] = false;
}


// Destructor
ModuleCollision::~ModuleCollision()
{

}

update_status ModuleCollision::LogicUpdate()
{
	LOG("Filled colliders %i", getFilledColNum());
	// Calculate collisions
	Collider* c1 = nullptr;
	Collider* c2 = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
				{
					c1->callback->OnCollision(c1, c2);
				}

				if (matrix[c2->type][c1->type] && c2->callback)
				{
					c2->callback->OnCollision(c2, c1);
				}
			}
		}
	}

	// Remove all colliders scheduled for deletion---------------------------------------------
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::ScreenUpdate()
{
	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_IGNORE_HIT: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_LIGHT: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ENEMY_HEAVY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_1_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_2_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 51, 255, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_UNIT: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_POWERUP: // orange
			App->render->DrawQuad(colliders[i]->rect, 255, 125, 0, alpha);
			break;
		case COLLIDER_GOD: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_HIT_DETECTION_WALL:
			App->render->DrawQuad(colliders[i]->rect, 255, 125, 125, alpha);
			break;
		case COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE: // magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_HIT_DETECTION_ENEMY:
			App->render->DrawQuad(colliders[i]->rect, 255, 125, 125, alpha);
			break;
		case COLLIDER_ENEMY_SHOT2:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;

		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	uint i;
	for (i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			return ret;//Does the same as a break, but allows us to skip the last if
		}
	}

	//If we get to max colliders, pop an error
	if(i == MAX_COLLIDERS)
	{
		LOG("Max colliders reached!\n");
	}

	return ret;
}

int ModuleCollision::getFilledColNum()
{
	int filledColNum = 0;

	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			filledColNum++;
		}
	}

	return filledColNum;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	//Return true if there is an overlap between argument "r" and property "rect"
	return (this->rect.x + this->rect.w > r.x   &&
		this->rect.x                < r.x + r.w &&
		this->rect.y + this->rect.h > r.y       &&
		this->rect.y < r.y + r.h);
}