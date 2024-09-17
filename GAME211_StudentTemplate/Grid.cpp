#include "Grid.h"
#include "CircleTower.h"
#include "TriangleTower.h"
#include "CircleCircleTower.h"
#include "CircleTriangleTower.h"
#include "TriangleTriangleTower.h"

Grid::Grid(GameManager* game_)  {
	
	game = game_;
	
}

Grid::~Grid() {};

void Grid::RenderGrid() {
	// go over every row in the level Array
	for (int i = 0; i < grid_Rows; i++) {
		// for every row move right for each column in the array
		for (int j = 0; j < grid_Collums; j++) {
			// switch using the value of the level array index
			switch (levelArray[i][j]) {
				// uses the enum value to check if the index value matches
			case ENEMY_PATH:
				// pass the texture and position to the Tile image function 
				
				TileRender(path_Texture, Vec3(j, i, 0));
				break;
			case SPAWN_POINT:
				TileRender(spawn_Texture, Vec3(j, i, 0));
				break;
			case END_POINT:
				TileRender(end_Texture, Vec3(j, i, 0));
				break;
			default:
				break;
			}
		}
	}
}
void Grid::SelectedCell(int x_,int y_, DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers) {
	// convert mouse position from screen to cell index by dividing by the cell size
	int x =  x_ ;
	int y = 600-y_ ;
	Vec3 worldCoords = MMath::inverse(game->getProjectionMatrix())* Vec3(x,y,0);
	int pos_x = worldCoords.x+0.5f ;
	int pos_y = worldCoords.y+0.5f;
	// check if the selected cell has a value greater then zero meaning a non placeable tile
	if (levelArray[pos_y][pos_x] < 0 ) {
		std::cout << "can not place object on tile: (" << pos_x << ',' << pos_y << ")"<<'\n';
		
	}
	std::shared_ptr<TowerSystem> newTower;
	if (selected_Tower >= 0) {
		// check if the tile is a open space
		if (levelArray[pos_y][pos_x] == OPEN_SPACE) {
			
			// place the base tower
			levelArray[pos_y][pos_x] = selected_Tower;

			PlaceTower(selected_Tower, pos_y, pos_x, liveTowers);
			
			std::cout << liveTowers.size() << '\n';

			std::cout << "placed object on tile: (" << pos_x << ',' << pos_y << ")" << '\n';
			
		}

		else if (levelArray[pos_y][pos_x] >= 1 && levelArray[pos_y][pos_x] < 10) {
			
			levelArray[pos_y][pos_x] = (levelArray[pos_y][pos_x] * 10) + selected_Tower;
			
			PlaceTower(levelArray[pos_y][pos_x]  , pos_y, pos_x, liveTowers);
			std::cout << levelArray[pos_y][pos_x] << '\n';
			std::cout << liveTowers.size() << '\n';
			std::cout << "placed object on tile: (" << pos_x << ',' << pos_y << ")" << '\n';

		}
		selected_Tower = 0;
		
	}
	valid_Tile = false;
}
int Grid::SelectedCell(int x_, int y_) {
	int x = x_;
	int y = 600 - y_;
	Vec3 worldCoords = MMath::inverse(game->getProjectionMatrix()) * Vec3(x, y, 0);
	int pos_x = worldCoords.x + 0.5f;
	int pos_y = worldCoords.y + 0.5f;

	return levelArray[pos_y][pos_x];
}

void Grid::HandleEvents(const SDL_Event& event, DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		// pass the x and y coordinates to the SelectedCell function
		io.AddMouseButtonEvent(0, true);

		//SelectedCell(event.motion.x, event.motion.y, liveTowers);

		break;
	case SDL_MOUSEBUTTONUP:
		io.AddMouseButtonEvent(0, false);
		break;
	// 1 to do
	// make number pad on click events so you can change towers
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_2:
			current_Level = 2;
			ReadLevelFile();
			break;
		case SDLK_3:
			current_Level = 3;
			break;
		default:
			break;
		}
		std::cout << selected_Tower << '\n';
		break;
	default:
		break;
	}
}

void Grid::ValidTile(int x_,int y_) {
	// convert mouse position from screen to cell index by dividing by the cell size
	int x = x_;
	int y = 600 - y_;
	Vec3 worldCoords = MMath::inverse(game->getProjectionMatrix()) * Vec3(x, y, 0);
	int pos_x = worldCoords.x + 0.5f;
	int pos_y = worldCoords.y + 0.5f;
	if (levelArray[pos_y][pos_x] == 0 ) {
		valid_Tile = true;
		tower_Combo = false;
	}
	else if (levelArray[pos_y][pos_x] < 10) {
		valid_Tile = true;
		tower_Combo = true;
	}
	else if (levelArray[pos_y][pos_x] < 0 ) {
		valid_Tile = false;
		tower_Combo = false;
	}
}

void Grid::TileRender(SDL_Texture* img_, Vec3 pos_) {
	// the width and height of the image
	int w = 40, h = 40;
	// retrieve the basic setting for the image
	Matrix4 projectionMatrix =  game->getProjectionMatrix();
	Vec3 screenCoords;
	// having scaling issue some tile not rendered fully with using projection matrix still looking into fix or better method 
	Vec3 invert_Y = Vec3(pos_.x, 15, 0) - Vec3(0, pos_.y, 0);
	screenCoords = projectionMatrix * (invert_Y);

	SDL_Rect tile;
	
	tile.x = static_cast<int>(screenCoords.x - 0.5f * w);
	tile.y = static_cast<int>(screenCoords.y  - 0.5f * h) ;
	tile.w = static_cast<int>(w);
	tile.h = static_cast<int>(h);
	// render the image
	SDL_RenderCopy(game->getRenderer(), img_, NULL, &tile);
}

void Grid::ReadLevelFile() {
	
	std::ifstream LevelFile;
	LevelFile.open("LevelData.txt");
	if (LevelFile.fail()) {
		std::cout << "LevelData.txt can not open \n";
	}
	std::string LevelData;
	LevelData = "";
	
	while (found_Level == false) {
		LevelFile >> LevelData;
		if (LevelData == "Level_" + std::to_string(current_Level))
			found_Level = true;
	}
	for (int i = 0; i < EnemyPath.size(); i++)
		EnemyPath.killNode(i);
		while (found_Level) {
			
			std::cout << LevelData << "\n";
			for (int i = 0; i < grid_Rows; i++) {
				for (int j = 0; j < grid_Collums; j++) {
					LevelFile >> LevelData;
					if (LevelData == "Path_Data_" + std::to_string(current_Level)) {
						path_Data = true;
						while (path_Data) {
							LevelFile >> LevelData;
							if (LevelData == "Level_End_" + std::to_string(current_Level)) {
								path_Data = false;
								found_Level = false;
							}	
							else if (path_Data)
							{
								int temp = std::stoi(LevelData);
								LevelFile >> LevelData;
								EnemyPath.pushBack(Vec2(temp, 15-std::stoi(LevelData)));
							}
						}						
					}
					else if (found_Level) {
						levelArray[i][j] = std::stoi(LevelData) * -1;				
					}
				}
			}
		}
		LevelFile.close();
		RenderGrid();
}


bool Grid::OnCreate(DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers) {
	path_Texture = IMG_LoadTexture(game->getRenderer(), "Enemy Path.png");
	//tower_Texture = IMG_LoadTexture(game->getRenderer(), "Tower.png");
	end_Texture = IMG_LoadTexture(game->getRenderer(), "End Point.png");
	spawn_Texture = IMG_LoadTexture(game->getRenderer(), "Start Point.png");
	for (int i = 0; i < (15 * 25); i++) {
		liveTowers.pushFront(nullptr);
	}
	ReadLevelFile();
	return true;
}
void Grid::PlaceTower(int tower_, int pos_y, int pos_x, DLinkedList<std::shared_ptr<TowerSystem>>& liveTowers) {
	std::shared_ptr<TowerSystem> newTower;
	
	switch (tower_) {
		
	case circle:
		newTower = std::make_shared<CircleTower>(pos_x, 15 - pos_y, 0, 1, 5, game);
		break;
	case triangle:
		newTower = std::make_shared<TriangleTower>(pos_x, 15 - pos_y, 0, 2, 10, game);
		break;
	case square:
		break;
	case hexagon:
		break;
	case octogon:
		break;
	case star:
		break;
	case diamond:
		break;
	case circlecircle:
		newTower = std::make_shared<CircleCircleTower>(pos_x, 15 - pos_y,0, 0.33f, 6.0f, game);
		break;
	case circletriangle:
		newTower = std::make_shared<CircleTriangleTower>(pos_x, 15 - pos_y, 0, 1.0f, 10.0f, game);
		break;
	case triangletriangle:
		newTower = std::make_shared<TriangleTriangleTower>(pos_x, 15 - pos_y, 0, 4.0f, 999.0f, game);
		break;
	case trianglecircle:
		newTower = std::make_shared<CircleTriangleTower>(pos_x, 15 - pos_y, 0, 1.0f, 10.0f, game);
		break;
	default:
		break;
	}
	newTower->OnCreate();
	liveTowers[15 * pos_y + pos_x] = newTower;
}