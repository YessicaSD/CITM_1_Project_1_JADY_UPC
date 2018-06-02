#include "Application.h"
#include "Enemy_MetalBee.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleStage05.h"
#include "MovPath.h"

#define MAX_PINATA_SPEED 1.5f

Enemy_MetalBee::Enemy_MetalBee(int x, int y, float hp, int scoreValue, POWERUP_TYPE pu_t) : Enemy(x, y, hp, scoreValue, pu_t)
{
	moveAnim.PushBack({520,250,48,44});
	moveAnim.PushBack({ 570,250,48,44 });



}
void Enemy_MetalBee:: Move()
{

}