#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <string>
#include "Commons.h"
#include "GameObject.h"
#include <vector>

class Camera;

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	//Getters and setters
	GameObject* GetObjectFromArray(int arrayIndex);
	void ClearArrayLocation(int arrayIndex);
	void AddObjectToArray(GameObject* objectReference, int arrayIndex);

	float GetGravityVal()			{ return gravityVal; }
	void SetGravityVal(float value)	{ gravityVal = value; }

protected:
	Camera* mCamera;

private:
	std::vector<GameObject*> gameObjectArray;
	float gravityVal;
};


#endif //_GAMESCREEN_H