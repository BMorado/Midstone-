#include "TriangleProjectiles.h"
#include "GameManager.h"

TriangleProjectiles::TriangleProjectiles()
{
}

TriangleProjectiles::TriangleProjectiles(MATH::Vec3 position_, MATH::Vec3 direction_, float speed_, float pierce_, float damage_, float collisionRadius_, float lifeSpan_, GameManager* game_)
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

TriangleProjectiles::TriangleProjectiles(TriangleProjectiles& other) : ProjectileSystem(other)
{
}

std::shared_ptr<ProjectileSystem> TriangleProjectiles::Clone()
{
	return std::make_shared<ProjectileSystem>(*this);
}

bool TriangleProjectiles::OnCreate()
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
