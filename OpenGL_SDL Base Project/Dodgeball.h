#pragma once
#include "GameObject.h"
#include "Player.h"
#include "SDL_mixer.h"

class Dodgeball : GameObject
{
public:
	Dodgeball();
	~Dodgeball();
	void Update(float deltaTime, SDL_Event e);
	void Render();

	bool PositionCheck();
	Sphere* GetBoundingSphere();

	void SetHasHitPlayer(bool value);
	bool GetHasHitPlayer()					{ return HasHitPlayer; }

	void SetParentPlayer(Player* value)		{ ParentPlayer = value; }
	Player* GetParentPlayer()				{ return ParentPlayer; }

	void SetPositionOffset(Vector3D value)	{ positionOffset = value; }

private:
	bool HasHitPlayer;
	Player* ParentPlayer;
	Vector3D positionOffset;
	Mix_Chunk *bounceWav;
};