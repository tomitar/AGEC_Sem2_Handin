#pragma once
#include "SDL.h"
#include "Object3DS.h"
#include "Collision.h"

class Sphere;

class GameObject
{
protected:
	Vector3D position;
	Vector3D rotation;
	Vector3D speed;

	double movementSpeed;
	double pitchSensitivity;
	double yawSensitivity;

	float lifePoints;
	bool isDestructable;
	bool isStatic;
	bool hasPhysics;

public:

	//Engine compulsorys
	GameObject(float startLifePoints, bool startIsDestructable, CollisionType collisionType);
	~GameObject();
	void Render();
	void Update(float deltaTime, SDL_Event e);

	//Model stuff
	void SetModel(Vector3D startpos, string name, bool vis, string texture);

	//Getters and Setters
	Vector3D GetPosition()		{ return position; }
	Vector3D GetRotation()		{ return rotation; }
	Vector3D GetSpeed()			{ return speed; }

	double GetMovementSpeed()	{ return movementSpeed; }
	double GetPitchSens()		{ return pitchSensitivity; }
	double GetYawSens()			{ return yawSensitivity; }
	
	float GetLifePoints()		{ return lifePoints; }
	bool GetIsDestructable()	{ return isDestructable; }
	bool GetIsStatic()			{ return isStatic; }
	bool HasPhysics()			{ return hasPhysics; }

	Sphere* GetBoundingSphere()	{ return boundingSphere; }


	void SetPosition(Vector3D value)							{ position = value; }
	void SetPosition(double xpos, double ypos, double zpos)		{ position = Vector3D(xpos, ypos, zpos); }
	void SetRotation(Vector3D value)							{ rotation = value; }
	void SetRotation(double xrot, double yrot, double zrot)		{ rotation = Vector3D(xrot, yrot, zrot); }
	void SetSpeed(Vector3D value)								{ speed = value; }
	void SetSpeed(double xspeed, double yspeed, double zspeed)	{ speed = Vector3D(xspeed, yspeed, zspeed); }

	void SetMovementSpeed(double value)							{ movementSpeed = value; }
	void SetPitchSens(double value)								{ pitchSensitivity = value; }
	void SetYawSens(double value)								{ yawSensitivity = value; }

	void SetLifePoints(float value)								{ lifePoints = value; }
	void SetIsDestructable(bool value)							{ isDestructable = value; }
	void SetIsStatic(bool value)								{ isStatic = value; }
	void SetHasPhysics(bool value)								{ hasPhysics = value; }

private:
	Object3DS* objectModel;

	Sphere* boundingSphere;
	float radius;
};
