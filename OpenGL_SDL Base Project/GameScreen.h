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

	bool GetGameOverFlag()			{ return gameOverFlag; }
	void SetGameOverFlag(bool value){ gameOverFlag = value; }

	bool GetVictoryFlag()			{ return victoryFlag; }
	void SetVictoryFlag(bool value)	{ victoryFlag = value; }

	float GetLevelScore()			{ return levelScore; }
	void SetLevelScore(float value)	{ levelScore = value; }

	void PrintStringToScreen(int xpos, int ypos, string inString);

protected:
	Camera* mCamera;

private:
	//Current max number of objects in a scene is 64.
	std::vector<GameObject*> gameObjectArray;
	float gravityVal;
	bool gameOverFlag;
	bool victoryFlag;
	float levelScore;
};


#endif //_GAMESCREEN_H