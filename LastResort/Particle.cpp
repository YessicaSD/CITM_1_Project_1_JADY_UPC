#include "Particle.h"
#include "SDL\include\SDL_timer.h"
Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	collision_fx(p.collision_fx), born(p.born), life(p.life), texture(p.texture) //struct texture added

{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{

	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;
	Move();
	

	if (collider != nullptr) {

		collider->SetPos(position.x, position.y - anim.GetFrame().h / 2);

		if (collider->type == COLLIDER_PLAYER_1_SHOT || COLLIDER_PLAYER_2_SHOT || COLLIDER_ENEMY_SHOT) {
			if (position.x >  SCREEN_WIDTH+DESPAWN_MARGIN_RIGHT || position.x < 0- DESPAWN_MARGIN_LEFT)
				ret = false;
			else if (position.y > SCREEN_HEIGHT+DESPAWN_MARGIN_DOWN || position.y < 0- DESPAWN_MARGIN_UP) {
				ret = false;
			}
		}
	}
	return ret;
}
void Particle::Move() {
	position.x += speed.x;
	position.y += speed.y;
}
