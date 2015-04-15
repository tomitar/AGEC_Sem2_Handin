#include "Dodgeball.h"


Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	SetHasPhysics(true);

}


Dodgeball::~Dodgeball()
{
}
