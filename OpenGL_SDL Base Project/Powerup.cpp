#include "Powerup.h"

Powerup::Powerup() : GameObject(0.0f,true,COLLISION_SPHERE,ANIM_SPIN)
{
	float randf = RandomFloat(0.0f, 3.0f);
	
	if (randf < 1.0f)
	{
		SetPType(PT_NONE);
	}
	else if (randf < 2.0f)
	{
		SetPType(PT_SPEED);
	}
	else if (randf < 3.0f)
	{
		SetPType(PT_SPEED);
	}

	switch (myPType)
	{
	case PT_NONE:
		SetModel(position, "none", false, "none");
		duration = 0.0f;
		break;
	case PT_SPEED:
		SetModel(position, "Tree_1.3DS", true, "Powerup.raw");
		duration = 3.0f;
		break;
	}

	SetPosition(Vector3D(RandomFloat(-124, 124), 0, RandomFloat(-124, 124)));
	SetHasActive(false);
}

Powerup::~Powerup()
{
}

void Powerup::Render()
{
	GameObject::Render();
}

void Powerup::Update(float deltaTime, SDL_Event e)
{
	GameObject::Update(deltaTime, e);
	if (GetHasActive() == true)
	{
		duration = duration - deltaTime;
	}
}

bool Powerup::GetHasFinished()
{
	if (duration < 0.0f)
	{
		return true;
	}

	return false;
}