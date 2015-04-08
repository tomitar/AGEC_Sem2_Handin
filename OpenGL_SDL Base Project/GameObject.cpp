#include "GameObject.h"


GameObject::GameObject(float startLifePoints, bool startIsDestructable)
{
	objectModel = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Tree.3ds", true, "no texture");
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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Getters and Setters

float GameObject::GetLifePoints()
{
	return lifePoints;
}

bool GameObject::GetIsDestructable()
{
	return isDestructable;
}

void GameObject::SetLifePoints(float newLifePoints)
{
	lifePoints = newLifePoints;
}

void GameObject::SetIsDestructable(bool newDestructable)
{
	isDestructable = newDestructable;
}