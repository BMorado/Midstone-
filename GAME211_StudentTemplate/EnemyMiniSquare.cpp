#include "EnemyMiniSquare.h"
#include "GameManager.h"
#include "DLinkedList.h"

const float EnemyMiniSquare::miniSquareSpeed = 2;


EnemyMiniSquare::EnemyMiniSquare(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, miniSquareSpeed, reward_, path_, game_), offset()
{
}

EnemyMiniSquare::EnemyMiniSquare(const EnemyMiniSquare& other) : 
    Enemy(other), offset(other.offset)
{
}

EnemyMiniSquare::EnemyMiniSquare(const EnemyMiniSquare& other, Vec3 pos_, Vec3 target_, Vec3 offset_) :
    Enemy(other), offset(offset_)
{
    pos = pos_ + offset;
    target = target_ + offset;
    vel = VMath::normalize(target - pos) * moveSpeed;
}

EnemyMiniSquare::~EnemyMiniSquare()
{
}

bool EnemyMiniSquare::OnCreate()
{
	image = IMG_Load("Enemy Assets/square_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return true;
}

void EnemyMiniSquare::Render(float scale)
{
    scale = scale / 2;
    // This is why we need game in the constructor, to get the renderer, etc.
    SDL_Renderer* renderer = game->getRenderer();
    Matrix4 projectionMatrix = game->getProjectionMatrix();

    // square represents the position and dimensions for where to draw the image
    SDL_Rect square;
    Vec3 screenCoords;
    float    w, h;

    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix * pos;

    // Scale the image, in case the .png file is too big or small
    w = image->w * scale;
    h = image->h * scale;

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer, texture, nullptr, &square,
        orientationDegrees, nullptr, SDL_FLIP_NONE);
}

std::shared_ptr<Enemy> EnemyMiniSquare::Clone() const
{
	return std::make_shared<EnemyMiniSquare>(*this);
}

bool EnemyMiniSquare::FindNextTile()
{
    //search path for current tile, then set next as target
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i].x == target.x - offset.x && path[i].y == target.y - offset.y)
        {
            if (i + 1 == path.size())
            {
                return false;
            }
            else {
                target = Vec3(path[i + 1].x, path[i + 1].y, 0) + offset;
                vel = VMath::normalize(target - pos) * moveSpeed;
                return true;
            }
        }
    }
    return false;
}
