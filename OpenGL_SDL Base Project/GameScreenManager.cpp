#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenLevel3.h"
#include "GameScreenMenu.h"
#include "GameScreenGameLevel1.h"
#include "GameScreenGameLevel2.h"
#include "GameScreenGameOver.h"
#include "ScoreScreen.h"
#include <string>
#include <sstream>

//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);

	totalframes = 0;
	frameTime = 0.0f;
	currentScore = 0.0f;
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
	DrawHUD(oldMessage);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			ChangeScreen(SCREEN_LEVEL1);
			break;
		case SDLK_2:
			ChangeScreen(SCREEN_LEVEL2);
			break;
		case SDLK_3:
			ChangeScreen(SCREEN_LEVEL3);
			break;
		case SDLK_RETURN:
			switch (thisScreen)
			{
			case SCREEN_MENU:
				ChangeScreen(SCREEN_GAMELEVEL1);
				break;
			case SCREEN_HIGHSCORES:
				ChangeScreen(SCREEN_GAMELEVEL2);
				break;
			case SCREEN_GAMELEVEL1:
				ChangeScreen(SCREEN_GAMELEVEL2);
				break;
			case SCREEN_GAMELEVEL2:
				break;
			}
			
		}
	}

	frameTime = frameTime + deltaTime;
	totalframes++;

	if (frameTime >= 1.0f)
	{
		frameTime = 0.0f;

		std::stringstream ss;
		ss << "CURRENT FPS: " << (totalframes) << "     OPENGL & SDL PROJECT     TOM BARTHOLOMEW     2015" << std::endl;
		oldMessage = ss.str();

		totalframes = 0;
	}

	if (mCurrentScreen->GetGameOverFlag() == true)
	{
		currentScore += mCurrentScreen->GetLevelScore();
		ChangeScreen(SCREEN_GAMEOVER);
	}
	else if (mCurrentScreen->GetVictoryFlag() == true)
	{
		currentScore += mCurrentScreen->GetLevelScore();
		ChangeScreen(SCREEN_HIGHSCORES);
		mCurrentScreen->SetLevelScore(currentScore);
	}

}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	GameScreenLevel3* tempScreen3;
	GameScreenMenu* tempScreenMenu;
	GameScreenGameLevel1* tempScreenLevel1;
	GameScreenGameLevel2* tempScreenLevel2;
	GameScreenGameOver* tempScreenOver;
	ScoreScreen* tempScreenScore;

	//Initialise the new screen.
	switch(newScreen)
	{
		case SCREEN_INTRO:
		break;

		case SCREEN_MENU:
			tempScreenMenu = new GameScreenMenu();
			mCurrentScreen = (GameScreen*)tempScreenMenu;
			tempScreenMenu = NULL;
			thisScreen = SCREEN_MENU;
		break;

		case SCREEN_LEVEL1:
			tempScreen1 = new GameScreenLevel1();
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
			thisScreen = SCREEN_LEVEL1;
		break;

		case SCREEN_LEVEL2:
			tempScreen2 = new GameScreenLevel2();
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
			thisScreen = SCREEN_LEVEL2;
		break;

		case SCREEN_LEVEL3:
			tempScreen3 = new GameScreenLevel3();
			mCurrentScreen = (GameScreen*)tempScreen3;
			tempScreen3 = NULL;
			thisScreen = SCREEN_LEVEL3;
		break;

		case SCREEN_GAMELEVEL1:
			tempScreenLevel1 = new GameScreenGameLevel1();
			mCurrentScreen = (GameScreen*)tempScreenLevel1;
			tempScreenLevel1 = NULL;
			thisScreen = SCREEN_GAMELEVEL1;
		break;

		case SCREEN_GAMELEVEL2:
			tempScreenLevel2 = new GameScreenGameLevel2();
			mCurrentScreen = (GameScreen*)tempScreenLevel2;
			tempScreenLevel2 = NULL;
			thisScreen = SCREEN_GAMELEVEL2;
			break;

		case SCREEN_GAMEOVER:
			tempScreenOver = new GameScreenGameOver();
			mCurrentScreen = (GameScreen*)tempScreenOver;
			tempScreenOver = NULL;
			thisScreen = SCREEN_GAMEOVER;
		break;
		
		case SCREEN_HIGHSCORES:
			tempScreenScore = new ScoreScreen();
			mCurrentScreen = (GameScreen*)tempScreenScore;
			tempScreenScore = NULL;
			thisScreen = SCREEN_HIGHSCORES;
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::DrawHUD(string inString)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glColor3f(0.8f, 0.8f, 0.8f);
	glRasterPos2i(0, 0);

	for (int i = 0; i < inString.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)inString[i]);
	}

	glRasterPos2i(0, 6);
	string line2;

	switch (thisScreen)
	{
		case SCREEN_LEVEL1:
			line2 = "CURRENT SCREEN: TERRAIN & INPUT SHOWCASE";
		break;

		case SCREEN_LEVEL2:
			line2 = "CURRENT SCREEN: WIREFRAME & ANIMATION SHOWCASE";
		break;

		case SCREEN_LEVEL3:
			line2 = "CURRENT SCREEN: LEVEL3";
		break;

		case SCREEN_MENU:
			line2 = "CURRENT SCREEN: MENU / SPLASH";
		break;

		case SCREEN_GAMELEVEL1:
			line2 = "CURRENT SCREEN: GAME LEVEL ONE";
		break;

		case SCREEN_GAMELEVEL2:
			line2 = "CURRENT SCREEN: GAME LEVEL TWO";
		break;
	}

	for (int i = 0; i < line2.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)line2[i]);
	};

	glDisable(GL_COLOR);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}