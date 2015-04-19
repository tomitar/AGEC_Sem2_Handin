#include "Dodgeball.h"
#include "Commons.h"
#include <iostream>

Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	SetHasPhysics(true);
	/*SetSpeed(Vector3D(	RandomFloat(0.0f,50.0f),
									0.0f,
							RandomFloat(0.0f,50.0f)));*/

	//SetPosition(Vector3D(	RandomFloat(0.0f, 50.0f),
	//						0.0f,
	//						RandomFloat(0.0f, 50.0f)));

	SetSpeed(Vector3D(0.0f, 0.0f, 0.0f));
	SetPosition(Vector3D(10.0f, 30.0f, 10.0f));
	SetModel(position, "Tree_1.3ds", true, "notext");
}

Dodgeball::~Dodgeball()
{
}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	//bounce inelastic
	if (GetPosition().y < 0.0f)
	{
		SetSpeed(Vector3D(GetSpeed().x, GetSpeed().y*-1.0f, (GetSpeed().z)));
	}
	std::cout << (float)GetPosition().x << " " << (float)GetPosition().y << " " << (float)GetPosition().z << std::endl;

	GameObject::Update(deltaTime,e);
}

void Dodgeball::Render()
{
	GameObject::Render();
}