#include "Enemy.h"

#include "GameManager.h"
#include "DLinkedList.h"
#include "ProjectileSystem.h"

Enemy::Enemy(int maxHealth_, float moveSpeed_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
    Body{}, maxHealth{ maxHealth_ }, currentHealth{ maxHealth_ }, moveSpeed{ moveSpeed_ }, 
    reward{ reward_ }, path{ path_ }, game { game_ }
{
    pos = Vec3(path_[0].x, path_[0].y, 0);
    target = pos;
}

Enemy::Enemy(const Enemy& other) : 
    Body{ other }, maxHealth{ other.maxHealth }, currentHealth{ other.maxHealth },
    moveSpeed{ other.moveSpeed }, reward{ other.reward }, path{ other.path }, 
    game{ other.game }, target{ other.target }
{
    pos = Vec3(path[0].x, path[0].y, 0);
}

Enemy::~Enemy()
{
    
}

bool Enemy::OnCreate()
{
	image = IMG_Load("Blinky.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
    FindNextTile();
    return true;
}

void Enemy::Render(float scale)
{
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

void Enemy::HandleEvents(const SDL_Event& event)
{
}

void Enemy::Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
    //if the target is within movement distance, don't run body's update to avoid overshooting it
    Vec3 targetDistance = target - pos;
    if (abs(targetDistance.x) + abs(targetDistance.y) < moveSpeed * deltaTime)
    {
        pos = target;
        if (!FindNextTile())
        {
            game->LoseLives(currentHealth);
            liveEnemies.killNode(thisIndex);
        }
    }
    else Body::Update(deltaTime);
}

void Enemy::OnDestroy()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

int Enemy::TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	currentHealth -= amount;
    if (currentHealth <= 0)
    {
        game->AddMoney(reward);
        liveEnemies.killNode(thisIndex);
    }
	return currentHealth;
}

std::shared_ptr<Enemy> Enemy::Clone() const
{
    return std::make_shared<Enemy>(*this);
}

bool Enemy::FindNextTile()
{
    //search path for current tile, then set next as target
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i].x == target.x && path[i].y == target.y)
        {
            if (i + 1 == path.size())
            {
                return false;
            }
            else {
                target = Vec3(path[i + 1].x, path[i + 1].y, 0);
                vel = VMath::normalize(target - pos) * moveSpeed;
                return true;
            }
        }
    }
    return false;
}
