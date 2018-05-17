#include "ParticleLaser.h"
#include "Particle.h"
Particle_Laser::Particle_Laser(Particle& p) : Particle(p)
{
	p.anim.PushBack( { 142,216,16,16 } );
	
}
void Particle_Laser:: Move() {

}
