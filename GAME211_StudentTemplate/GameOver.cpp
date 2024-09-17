#include "GameOver.h"
#include "Scene.h"

GameOver::GameOver()
{
}

GameOver::GameOver(int lives_) 
{
	lives = lives_;
}

// Checking if player is dead
bool GameOver::isAlive(int lives_)
{
	lives = lives_;
	if (lives > 0)
	{
		return true;
	}

	else if (lives <= 0)
	{
		return false;
	}

	return true;
}
