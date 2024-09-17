#pragma once

class GameOver
{
private:
	int lives, money;

public:
	GameOver();

	GameOver(int lives_);

	bool isAlive(int lives_);
};

