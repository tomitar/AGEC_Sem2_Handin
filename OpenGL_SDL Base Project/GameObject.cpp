#include "GameObject.h"
#include "Constants.h"
#include <iostream>
using namespace::std;

GameObject::GameObject(float startLifePoints, bool startIsDestructable, CollisionType newCollType, ANIMMODE newAnim)
{
	radius = 2.0f;

	SetIsDestructable(startIsDestructable);
	SetLifePoints(startLifePoints);
	SetMovementSpeed(10);
	SetHasPhysics(false);
	collType = newCollType;
	animMode = newAnim;

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
	objectModel->render(animMode);
}

void GameObject::SetModel(Vector3D startpos, string name, bool vis, string texture)
{
	objectModel = new Object3DS(startpos, name, vis, texture);
}

void GameObject::Update(float deltaTime, SDL_Event e)
{
	if (hasPhysics == true)
	{
		float constGravity = GRAVITY;
		constGravity = constGravity*deltaTime;
		speed.y = speed.y - (constGravity);
	}

	position.x += speed.x*deltaTime;
	position.y += speed.y*deltaTime;
	position.z += speed.z*deltaTime;

	if (boundingSphere != NULL)
	{
		boundingSphere->SetCollided(false);
		boundingSphere->Update(position);
	}
	objectModel->update(deltaTime, e, animMode, position);
}

float GameObject::RandomFloat(float a, float b)
{
	float random = ((float)rand() / (float)RAND_MAX);
	float diff = b - a;
	float r = random*diff;
	return a + r;
}