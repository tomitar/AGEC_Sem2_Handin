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

protected:
	Camera* mCamera;

private:
	//Current max number of objects in a scene is 64.
	std::vector<GameObject*> gameObjectArray;
};


#endif //_GAMESCREEN_H