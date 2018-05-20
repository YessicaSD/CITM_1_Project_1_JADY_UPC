#include "Application.h"
#include "Enemy_Pinata_Spawner.h"
#include "Enemy_Pinata.h"
#include "ModuleStage05.h"
#include "ModuleCollision.h"


Enemy_Pinata_Spawner::Enemy_Pinata_Spawner(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	//Animation-------------------------------------------
	openAnim.PushBack({ 156,52,64,19 });
	openAnim.PushBack({ 156,71,64,19 });
	openAnim.PushBack({ 156,90,64,19 });
	openAnim.PushBack({ 156,109,64,19 });
	openAnim.PushBack({ 156,128,64,19 });
	openAnim.PushBack({ 156,128,64,19 });
	openAnim.PushBack({ 156,109,64,19 });
	openAnim.PushBack({ 156,90,64,19 });
	openAnim.PushBack({ 156,71,64,19 });
	openAnim.speed = 0.3f;
	//Add collider----------------------------------------
	collider = App->collision->AddCollider({ fixedPos.x, fixedPos.x, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);

}

void Enemy_Pinata_Spawner::Move()
{
	//Update position-------------------------------------------
	position = App->stage05->spawnPos + fixedPos;
	//Enemies Spawning------------------------------------------



}