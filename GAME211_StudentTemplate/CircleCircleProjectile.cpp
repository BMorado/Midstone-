#include "CircleCircleProjectile.h"
#include "GameManager.h"

CircleCircleProjectile::CircleCircleProjectile() : ProjectileSystem()
{
}

CircleCircleProjectile::CircleCircleProjectile(MATH::Vec3 position_, MATH::Vec3 direction_, 
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

CircleCircleProjectile::CircleCircleProjectile(CircleCircleProjectile& other) : ProjectileSystem(other)
{
}

std::shared_ptr<ProjectileSystem> CircleCircleProjectile::Clone()
{
	return std::make_shared<CircleCircleProjectile>(*this);
}

bool CircleCircleProjectile::OnCreate()
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
