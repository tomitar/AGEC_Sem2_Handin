#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Terrain.h"
#include "Object3DS.h"
#include "Commons.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void		SetLight();

	lighting	mLight;
	float light_Pos[3];

//--------------------------------------------------------------------------------------------------
private:	
	float   mCurrentTime;
	Object3DS*	m_p3DSModel;
	Terrain mTerrain;
};


#endif //_GAMESCREENLEVEL1_H