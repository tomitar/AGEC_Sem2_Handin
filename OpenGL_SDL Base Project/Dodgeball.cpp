#include "Dodgeball.h"
#include "Commons.h"

#include <iostream>
#include <string>

Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	std::cout << "Dodgeball Constructor" << std::endl;

	SetHasPhysics(true);

	SetPosition(Vector3D(	RandomFloat(-28.0f, 28.0f),
							30.0f,
							RandomFloat(-40.0f, 33.0f)));

	SetSpeed(Vector3D(		RandomFloat(0.0f,50.0f),
							0.0f,
							RandomFloat(0.0f,50.0f)));

	SetModel(position, "Tree_1.3ds", true, "dodgeballtex.tga");
}

Dodgeball::~Dodgeball()
{
}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	//bounce inelastic
	if (GetPosition().z == 0.0f)
	{
		SetSpeed(Vector3D(GetSpeed().x, GetSpeed().y, (GetSpeed().z*-1.0f)));
	}
}
