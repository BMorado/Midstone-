#pragma once
#include <memory>

class Enemy;

struct Wave 
{
	std::shared_ptr<Enemy> waveEnemy;
	int numInWave;

	Wave(std::shared_ptr<Enemy> waveEnemy_, int numInWave_) : waveEnemy{ waveEnemy_ }, numInWave{ numInWave_ } {}
	Wave(const Wave& other) : waveEnemy{ other.waveEnemy }, numInWave{ other.numInWave } {}
};
