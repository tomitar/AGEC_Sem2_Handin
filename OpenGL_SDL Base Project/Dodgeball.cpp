#include "Dodgeball.h"
#include "Commons.h"

Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	SetHasPhysics(true);
	SetSpeed(Vector3D(	RandomFloat(0.0f,50.0f),
									0.0f,
						RandomFloat(0.0f,50.0f)));

}

Dodgeball::~Dodgeball()
{
}

Dodgeball::Update(float deltaTime, SDL_Event e)
{

}
