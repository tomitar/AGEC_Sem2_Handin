#include "GameObject.h"

#include <iostream>
using namespace::std;

GameObject::GameObject(float startLifePoints, bool startIsDestructable, CollisionType collType)
{
	cout << "GAMEOBJECT constructor" << endl;
	SetIsDestructable(startIsDestructable);
	SetLifePoints(startLifePoints);
	SetMovementSpeed(10);
}

GameObject::~GameObject()
{
}

void GameObject::Render()
{
	objectModel->render(ANIM_CUSTOM);
}

void GameObject::SetModel(Vector3D startpos, string name, bool vis, string texture)
{
	objectModel = new Object3DS(startpos, name, vis, texture);
}

void GameObject::Update(float deltaTime, SDL_Event e)
{
	objectModel->update(deltaTime, e, ANIM_CUSTOM, position);
}