#include "Dodgeball.h"
#include "Commons.h"

Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	SetHasPhysics(true);
	/*SetSpeed(Vector3D(	RandomFloat(0.0f,50.0f),
									0.0f,
							RandomFloat(0.0f,50.0f)));*/

	//SetPosition(Vector3D(	RandomFloat(0.0f, 50.0f),
	//						0.0f,
	//						RandomFloat(0.0f, 50.0f)));

	SetPosition(Vector3D(10.0f, 30.0f, 10.0f));
}

Dodgeball::~Dodgeball()
{
}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	//bounce inelastic
	if (GetPosition().y == 0.0f)
	{
		SetSpeed(Vector3D(GetSpeed().x, GetSpeed().y*-1.0f, (GetSpeed().z)));
	}
}
