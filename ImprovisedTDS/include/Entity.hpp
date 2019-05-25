#pragma once
//#include "Texture2D.hpp"
#include "Vector2.hpp"
//#include "SpriteBatch.hpp"

class SpriteBatch;
class Texture2D;

class Entity
{
public:
	virtual ~Entity();
	virtual void HandleInput(/*const InputHandler* input*/);
	virtual void Update(const float dt);
	virtual void Draw(const SpriteBatch* spriteBatch) = 0;

	Vector2f GetPosition() const;
	Vector2f GetVelocity() const;
	Vector2f GetOrigin() const;
	Vector2f GetSize() const;
	Texture2D* GetImage() const;
	float GetRotation() const;

protected:
	Entity();

	Texture2D* image = nullptr;
	Vector2f position;
	Vector2f velocity;
	Vector2f origin;
	Vector2f size;
	float rotation;

private:


};

inline Entity::~Entity()
{ }

inline void Entity::HandleInput()
{ }

inline void Entity::Update(const float dt)
{ }

inline Vector2f Entity::GetPosition() const
{
	return position;
}

inline Vector2f Entity::GetVelocity() const
{
	return velocity;
}

inline Vector2f Entity::GetOrigin() const
{
	return origin;
}

inline Vector2f Entity::GetSize() const
{
	return size;
}

inline Texture2D* Entity::GetImage() const
{
	return image;
}

inline float Entity::GetRotation() const
{
	return rotation;
}

inline Entity::Entity()
	: position(0.0f, 0.0f), velocity(0.0f, 0.0f), origin(0.0f, 0.0f), size(1.0f, 1.0f), rotation(0.0f)
{ }
