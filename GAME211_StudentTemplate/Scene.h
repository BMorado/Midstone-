#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include <memory>
#include "GameManager.h"

using namespace MATH;
class Spawner;
class Enemy;
class TowerSystem;

class Scene {
public:
    class GameManager* game = NULL;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
    virtual void HandleEvents(const SDL_Event& event) = 0;
    virtual ~Scene(){};
	virtual float getxAxis() = 0;
	virtual float getyAxis() = 0;
	virtual SDL_Window* getWindow() = 0;
    virtual Matrix4 getProjectionMatrix() = 0;
	virtual Matrix4 getInverseMatrix() = 0;
	virtual int getLives() = 0;
	virtual int getMoney() = 0;
	virtual void setLives(int lives) = 0;
	virtual void setMoney(int money) = 0;
	virtual void LoseLives(int lives) = 0;
	virtual void AddMoney(int money) = 0;
};

#endif
