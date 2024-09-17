#ifndef GRID_H
#define GRID_H

#include <VMath.h>
#include<SDL.h>
#include <SDL_image.h>
#include<vector>
#include"GameManager.h"
#include "DLinkedList.h"
#include <fstream>
#include <string>
#include "Enum.h"
#include"TowerSystem.h"
template <typename T>
class DLinkedList;


using namespace MATH;
union SDL_Event;

class Grid {
private:

	
	// the value of the tower the palyer is holding
	
	// the amount of columns in the grid
	const static int grid_Collums = 25;
	// the amount of rows in the grid
	const static int grid_Rows = 15;
	// the cell size for each tile
	int cell_Size = 50;

	GameManager* game;
	
	ImGuiIO& io = ImGui::GetIO();

	int current_Level =1;
	bool found_Level = false;
	bool grid_Data = false;
	bool path_Data = false;
	

	SDL_Texture* path_Texture;	
	SDL_Texture* tower_Texture;
	SDL_Texture* spawn_Texture;
	SDL_Texture* end_Texture;
	// linked list holding all the enemy path corner positions 
	DLinkedList<Vec2> EnemyPath;


	//the spawn point of the enemy
	int levelArray[15][25];
	Vec2 spawn_point = Vec2(0, 8);
	
public:
	bool valid_Tile;
	int selected_Tower;
	bool tower_Combo = false;
	//Grid();
	Grid( GameManager* game_);
	~Grid();

	// DRAWING THE SELECTED SQUARE STILL HAS ISSUES AS WE CHANGED THE WAY WE ARE DETERMINING POSTION! \\
	/// <summary>
	/// The function that is called to initiate the rendering of each cell 
	/// loops over each row and renders each tile for that row
	/// also determine what image needs to be rendered for each tile and at what position
	/// </summary>
	void RenderGrid(); // Draw the level grid to the screen

	/// <summary>
	/// finds the state of the tile selected by the player and prints a message stating if you can or cant place a tower there
	/// </summary>
	/// <param name="x_">the mouse x position</param>
	/// <param name="y_">the mouse y position</param>
	void SelectedCell(int x_,int y_, DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers);
	
	/// <summary>
	/// Handles the mouse and keyboard inputs
	/// </summary>
	/// <param name="event">The sdl keybord and mouse events</param>
	void HandleEvents(const SDL_Event& event, DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers);// handle events from the user mouse and keyboard
	
	/// <summary>
	/// Renders the tile for each grid cell
	/// </summary>
	/// <param name="img_">The image of the tile</param>
	/// <param name="pos_">THe position to render the tile</param>
	void TileRender(SDL_Texture* img_,Vec3 pos_);
	
	
	/// <summary>
	/// handles what needs to be done as soon as the grid object is created
	/// </summary>
	/// <returns>Returns true once it si done</returns>
	bool OnCreate(DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers);

	/// <summary>
	/// Read from the level file and extract the grid data and enemy paths
	/// </summary>
	void ReadLevelFile();


	void ValidTile(int x, int y);

	int SelectedCell(int x_, int y_);

	void PlaceTower(int tower_,  int pos_y, int pos_x ,DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers);


	DLinkedList<Vec2>& GetPath() { return EnemyPath; }
};


#endif // !GRID_H

