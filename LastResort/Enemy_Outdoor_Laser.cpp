#include "Application.h"
#include "Enemy_Outdoor_Laser.h"
#include "ModuleCollision.h"
#include "ModuleStage05.h"

Enemy_Outdoor_Laser::Enemy_Outdoor_Laser(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	OutdoorLacerAnim.PushBack({ 142,216,16,16 });
	/*OutdoorLacerAnim.loop = true;*/
	animation = &OutdoorLacerAnim;
	position_x = x;
	position_y = y;
	collider = App->collision->AddCollider({ x, y + 3, 24, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_Outdoor_Laser::Move()
{
	//position.x = App->stage05->spawnPos.x + position_x;
	//position.y = App->stage05->spawnPos.y + position_y;
}
