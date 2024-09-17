#include "CircleTriangleProjectile.h"
#include "GameManager.h"

CircleTriangleProjectile::CircleTriangleProjectile() : ProjectileSystem()
{
}

CircleTriangleProjectile::CircleTriangleProjectile(MATH::Vec3 position_, MATH::Vec3 direction_,
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

CircleTriangleProjectile::CircleTriangleProjectile(CircleTriangleProjectile& other) : ProjectileSystem(other)
{
}

std::shared_ptr<ProjectileSystem> CircleTriangleProjectile::Clone()
{
	return std::make_shared<CircleTriangleProjectile>(*this);
}

bool CircleTriangleProjectile::OnCreate()
{
	image = IMG_Load("Projectile Assets/triangle_projectile.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return true;
}
