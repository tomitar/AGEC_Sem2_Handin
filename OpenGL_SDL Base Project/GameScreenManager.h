#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	virtual void DrawHUD(std::string inString);

	void ChangeScreen(SCREENS newScreen);

private:
	GameScreen* mCurrentScreen;
	SCREENS thisScreen;
	std::string oldMessage;

	float frameTime;
	int totalframes;
};


#endif //_GAMESCREENMANAGER_H