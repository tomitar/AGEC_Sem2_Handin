#include "Target.h"


Target::Target() : GameObject(10, true, COLLISION_SPHERE, ANIM_SPIN)
{
	SetModel(Vector3D(), "Target.3DS", true, "Target.raw");
	
	SetPosition(Vector3D(RandomFloat(-124, 124), 0, RandomFloat(-124, 124)));
}


Target::~Target()
{
}

void Target::Update(float deltaTime, SDL_Event e)
{
	GameObject::Update(deltaTime, e);
}

void Target::Render()
{
	GameObject::Render();
}