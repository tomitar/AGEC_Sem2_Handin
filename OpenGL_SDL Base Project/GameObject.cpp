#include "GameObject.h"

GameObject::GameObject(float startLifePoints, bool startIsDestructable)
{
	SetIsDestructable(startIsDestructable);
	SetLifePoints(startLifePoints);
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