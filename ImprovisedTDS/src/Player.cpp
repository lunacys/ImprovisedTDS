#include "Player.hpp"
//#include "InputManager.hpp"
#include "SpriteBatch.hpp"

Player::Player(Texture2D* img, Vector2f pos)
{
	image = img;
	position = pos;
}

Player::~Player()
{

}

void Player::Update(const float dt)
{
	//position.X += 16 * dt;
	//position.Y += 16.5f * dt;
}

void Player::Draw(const SpriteBatch* spriteBatch)
{
	spriteBatch->Draw(image, position.ToGlmVec2());
}
