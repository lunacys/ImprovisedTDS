#pragma once
#include "Entity.hpp"

class Player : public Entity
{
public:
	Player(Texture2D* img, Vector2f pos);
	~Player();

	void Update(const float dt) override;
	void Draw(const SpriteBatch* spriteBatch) override;
};
