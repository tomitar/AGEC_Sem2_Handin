#include "GameObject.h"
#include "Constants.h"
#include <iostream>
using namespace::std;

GameObject::GameObject(float startLifePoints, bool startIsDestructable, CollisionType collType)
{
	//debug
	cout << "GAMEOBJECT constructor" << endl;
	radius = 2.0f;

	SetIsDestructable(startIsDestructable);
	SetLifePoints(startLifePoints);
	SetMovementSpeed(10);
	SetHasPhysics(false);

	switch (collType)
	{
		case COLLISION_SPHERE:
			boundingSphere = new Sphere(position, radius);
		break;
		case COLLISION_CUBE:
		break;
		case COLLISION_NONE:
		break;
	}
}

GameObject::~GameObject()
{
}

void GameObject::Render()
{
	if (boundingSphere->GetCollided())
	{
		cout << "COLLISION!" << endl;
	}
	objectModel->render(ANIM_CUSTOM);
}

void GameObject::SetModel(Vector3D startpos, string name, bool vis, string texture)
{
	objectModel = new Object3DS(startpos, name, vis, texture);
}

void GameObject::Update(float deltaTime, SDL_Event e)
{
	if (hasPhysics = true)
	{
		float constGravity = GRAVITY;
		constGravity = constGravity*deltaTime;
		speed.y = speed.y - (constGravity);
	}

	/*position.x += speed.x;
	position.y += speed.y;
	position.z += speed.z;*/

	if (boundingSphere != NULL)
	{
		boundingSphere->SetCollided(false);
		boundingSphere->Update(position);
	}
	objectModel->update(deltaTime, e, ANIM_CUSTOM, position);
}
