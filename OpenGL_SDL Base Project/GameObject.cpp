#include "GameObject.h"


GameObject::GameObject()
{
	objectModel = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Tree.3ds", true, "no texture");
}


GameObject::~GameObject()
{
}

void GameObject::Render()
{
	objectModel->render(ANIM_CUSTOM);
}