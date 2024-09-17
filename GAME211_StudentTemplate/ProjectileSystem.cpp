#include "ProjectileSystem.h"
#include "GameManager.h"

ProjectileSystem::ProjectileSystem()
{
	pos = MATH::Vec3(0, 0, 0);
	direction = MATH::Vec3(1, 0, 0);
	speed = 1;
	pierce = 1;
	damage = 1;
	collisionRadius = 1;
	lifeSpan = 10;

	game = nullptr;
	
	enemiesHit.resize(pierce);
}

ProjectileSystem::ProjectileSystem(const ProjectileSystem& projectile_) : Body(projectile_)
{
	pos = projectile_.pos;
	direction = projectile_.direction;
	speed = projectile_.speed;
	pierce = projectile_.pierce;
	damage = projectile_.damage;
	collisionRadius = projectile_.collisionRadius;
	lifeSpan = projectile_.lifeSpan;

	game = projectile_.game;

	enemiesHit.resize(pierce);

}

ProjectileSystem::ProjectileSystem(MATH::Vec3 position_, MATH::Vec3 direction_, float speed_, int pierce_, float damage_, float collisionRadius_, float lifeSpan_, GameManager* game_)
{

	pos = position_;
	direction = direction_;
	speed = speed_;
	pierce = pierce_;
	damage = damage_;
	collisionRadius = collisionRadius_;
	lifeSpan = lifeSpan_;

	game = game_;

	enemiesHit.resize(pierce);
}

ProjectileSystem::~ProjectileSystem()
{
}

void ProjectileSystem::Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, DLinkedList< std::shared_ptr<ProjectileSystem>>& projectiles_, int PLocation)
{

	updatePosition(deltaTime);

	checkAllCollision(liveEnemies);

	totalTime += deltaTime;
	if (pierce <= 0 || totalTime > lifeSpan) {
		projectiles_.killNode(PLocation);
	}
	
}

void ProjectileSystem::updateDirection(MATH::Vec3 direction_)
{
	direction = MATH::VMath::normalize(direction_);

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
}

std::shared_ptr<ProjectileSystem> ProjectileSystem::Clone() const
{
	return std::make_shared<ProjectileSystem>(*this);
}

bool ProjectileSystem::OnCreate()
{
	return false;
}

void ProjectileSystem::Render(float scale)
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

void ProjectileSystem::OnDestroy()
{
	SDL_DestroyTexture(texture);
}

void ProjectileSystem::updatePosition(float deltaTime)
{

	pos += (direction * (deltaTime * speed));

}

void ProjectileSystem::checkAllCollision(DLinkedList<std::shared_ptr<Enemy>>& liveEnemies)
{
	
	for (int i = 0; i < liveEnemies.size(); i++) {

		Enemy* enemie = liveEnemies[i].get();
		
		if (MATH::VMath::distance(pos, enemie->getPos()) < collisionRadius) {
		
			bool isHit = false;
			//check to see if its in enemies hit
			for (int j = 0; j < totalHit; j++) {
				if (enemie == enemiesHit.at(j)) {
					isHit = true;

				}
			}

			if (!isHit) {
				enemie->TakeDamage(damage, liveEnemies, i);
				enemiesHit[totalHit] = enemie;
				totalHit++;
				pierce--;
			}

		}

		if (pierce <= 0) return;

	}


}


