#include "GameObject.h"

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
	if (boundingSphere != NULL)
	{
		boundingSphere->SetCollided(false);
		boundingSphere->Update(position);
	}
	objectModel->update(deltaTime, e, ANIM_CUSTOM, position);
}
