#include "CircleProjectile.h"
#include "GameManager.h"

// Default Constructor
CircleProjectile::CircleProjectile() : ProjectileSystem()
{

}

// Constructor taking position, direction, speed, peirce, damage, collision radius, and life span
CircleProjectile::CircleProjectile(MATH::Vec3 position_, MATH::Vec3 direction_, 
	float speed_, float pierce_, float damage_, float collisionRadius_, float lifeSpan_, GameManager* game_)
{
	pos = position_;
	direction = direction_;
	speed = speed_;
	pierce = pierce_;
	damage = damage_;
	collisionRadius = collisionRadius_;
	lifeSpan = lifeSpan_;

    game = game_;
}

CircleProjectile::CircleProjectile(CircleProjectile& other) : ProjectileSystem(other) 
{
}

std::shared_ptr<ProjectileSystem> CircleProjectile::Clone()
{
    return std::make_shared<CircleProjectile>(*this);
}

bool CircleProjectile::OnCreate()
{
	image = IMG_Load("Projectile Assets/circle_projectile.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return true;
}



