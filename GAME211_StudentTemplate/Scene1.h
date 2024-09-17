#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include "Scene.h"
#include "Grid.h"
#include "Enemy.h"
#include "TowerSystem.h"
#include "DLinkedList.h"
#include "GameOver.h"

class WaveController;

using namespace MATH;
class Scene1 : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
    Matrix4     inverseProjection;	// set in OnCreate()
	Grid* grid;

	std::unique_ptr<WaveController> waveController;
	DLinkedList<std::shared_ptr<Enemy>> liveEnemies;
	DLinkedList<std::shared_ptr<TowerSystem>> liveTowers;
	DLinkedList<std::shared_ptr<ProjectileSystem>> liveProjectiles;

	//
	ImGuiIO& io = ImGui::GetIO();
	
	//storage location of resorces
	int totalLives = 100;
	int totalMoney = 10000;

	//fonts used by imGui
	ImFont* font;
	ImFont* font2;
	
	//bool that controls the visiblility of the heal and money
	bool topMenuBar = true;
	//bools that control if tower menus are visable
	bool towerSelect = false;
	bool towerCombination = false;
	//bool for gui that skips the wave
	bool SkipWaveGUI = true;
	bool WaveActive = false;

	//position for windows based on click location
	Vec2 clickPos;
	Vec2 mousePos;



	GameOver* gameOver;

	//base cost of towers
	const int CircleTowerCost = 100;
	const int TriangleTowerCost = 150;

	//cost of combining
	const int CircleTowerCombinationCost = 100;
	const int TriangleTowerCombinationCost = 150;

	//created enum for easy switch use
	enum TowerType {
		
		none = 0,
		circle = 1,
		triangle = 2,
		square = 3,
		hexagon = 4,
		octogon = 5,
		star = 6,
		diamond =7

	};

	int selectedTowerType = 0;


public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
    void HandleEvents(const SDL_Event &event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	int getLives();
	int getMoney();
	void setLives(int lives);
	void setMoney(int money);
	void LoseLives(int damage);
	void AddMoney(int money);
	void ChosenTower();

	//all the GUI requierments in one place
	void renderGUI();
	void renderTowerSelect();
	void renderTowerCombination();
	void renderSkipWave();


};

#endif
