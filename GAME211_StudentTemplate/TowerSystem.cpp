#include "TowerSystem.h"
#include "VMath.h"
#include "GameManager.h"

TowerSystem::TowerSystem()
{
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	range = 0;
	fireRate = 0;
	currentTime = 0;
	projectile = std::make_shared<ProjectileSystem>();

	game = nullptr;
}

TowerSystem::TowerSystem(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_)
{
	pos.x = x_;
	pos.y = y_;
	pos.z = z_;

	range = range_;
	fireRate = fireRate_;
	currentTime = 0;

	game = game_;
}

TowerSystem::TowerSystem(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_)
{
	pos = pos_;
	fireRate = fireRate_;
	range = range_;
	currentTime = 0;

	game = game_;
}

TowerSystem::TowerSystem(const TowerSystem& tower_)
{
	pos = tower_.pos;
	range = tower_.range;
	fireRate = tower_.fireRate;
	currentTime = 0;

	game = tower_.game;
}

void TowerSystem::update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles)
{
	//update current tower time by adding delta time to it
	currentTime += deltaTime;

	//time since last shot is greater than fire rate
	if (currentTime > fireRate) {

		//calls Fire projectile which cheaks if there is an enemie in range
		// if there is an eneime in range spawns a projectile and returns true setting the current time back to 0
		// if no eneime is in range no projectle is spawned and time isnt reset
		if (fireProjectile(enemies, projectiles)) {
			currentTime = 0;
		}

	}



}

void TowerSystem::update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles, std::shared_mutex& mutex_)
{
	//update current tower time by adding delta time to it
	currentTime += deltaTime;

	//time since last shot is greater than fire rate
	if (currentTime > fireRate) {

		//calls Fire projectile which cheaks if there is an enemie in range
		// if there is an eneime in range spawns a projectile and returns true setting the current time back to 0
		// if no eneime is in range no projectle is spawned and time isnt reset
		if (fireProjectile(enemies, projectiles, mutex_)) {
			currentTime = 0;
		}
		
	}
}

bool TowerSystem::OnCreate()
{
	return false;
}

void TowerSystem::Render(float scale)
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

void TowerSystem::OnDestroy()
{
	SDL_DestroyTexture(texture);
	projectile->OnDestroy();
}

bool TowerSystem::fireProjectile(DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles)
{

	//loops throught all enemies
	for (int i = 0; i < enemies.size(); i++) {

		float distanceFromTower = MATH::VMath::distance(pos, enemies[i]->getPos());

		//cheaks the dictance between the tower and enemy to see if enemy distance is less than towers range
		if (distanceFromTower < range) {

			//creates new projectile with a direction vector towards the enemie
			std::shared_ptr<ProjectileSystem> newProj = projectile->Clone();
			Vec3 direction = MATH::VMath::normalize((enemies[i]->getPos() + (enemies[i]->getVel() * (distanceFromTower / newProj->getProjectileSpeed()))) - pos);
			newProj->updateDirection(direction);
			projectiles.pushBack(newProj);

			

			//update oriantion of the tower based on the enemie its firing at
			if (direction.y >= 0) {
				if (direction.x >= 0) {
					orientation = DEGREES_TO_RADIANS * (90 * direction.x);
				}
				else
				{
					orientation = DEGREES_TO_RADIANS * ((90 * (direction.y)) + 270);
				}
			}
			else
			{
				if (direction.x >= 0) {
					orientation = DEGREES_TO_RADIANS * ((90 * -(direction.y)) + 90);
				}
				else
				{
					orientation = DEGREES_TO_RADIANS * ((90 * -(direction.x)) + 180);
				}
			}


			//returns that a projectile has fired
			return true;
		}
	}

	//if code gets to here it means that no enemies are within range to fire at so it returns false
	return false;
}

bool TowerSystem::fireProjectile(DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles, std::shared_mutex& mutex_)
{
	
	
	//loops throught all enemies
	for (int i = 0; i < enemies.size(); i++) {

		//locks current thread if its being written to
		std::shared_lock<std::shared_mutex> lock(mutex_);

		float distanceFromTower = MATH::VMath::distance(pos, enemies[i]->getPos());

		//cheaks the dictance between the tower and enemy to see if enemy distance is less than towers range
		if ( distanceFromTower < range) {


			//locks out other threads during writing process
			std::unique_lock<std::shared_mutex> lock2(mutex_);
			//creates new projectile with a direction vector towards the enemie
			std::shared_ptr<ProjectileSystem> newProj = projectile->Clone();
			newProj->updateDirection((enemies[i]->getPos() + (enemies[i]->getVel() * (distanceFromTower/newProj->getProjectileSpeed()))) - pos);
			projectiles.pushBack(newProj);

			//returns that a projectile has fired
			return true;
		}
	}

	//if code gets to here it means that no enemies are within range to fire at so it returns false
	return false;
}


