#pragma once
#include <vector>
#include "Entity.hpp"

class EntityManager
{
public:
	static void Add(Entity* entity);
	
	static void HandleInput();
	static void Update(const float dt);
	static void Draw(const SpriteBatch* spriteBatch);

private:
	static void AddEntity(Entity* entity);

	static std::vector<Entity*> entities_;
	static std::vector<Entity*> entitiesToAdd_;

	static bool isUpdating_;
};

bool EntityManager::isUpdating_ = false;
std::vector<Entity*> EntityManager::entities_ = {};
std::vector<Entity*> EntityManager::entitiesToAdd_ = {};

inline void EntityManager::Add(Entity* entity)
{
	if (!isUpdating_)
		AddEntity(entity);
	else
		entitiesToAdd_.push_back(entity);
}

inline void EntityManager::HandleInput()
{
	if (!isUpdating_)
		for (Entity* e : entities_)
			e->HandleInput();
}

inline void EntityManager::Update(const float dt)
{
	isUpdating_ = true;

	for (Entity* e : entities_)
	{
		//std::cout << e->GetPosition().X << ", " << e->GetPosition().Y << std::endl;
		e->Update(dt);
	}

	isUpdating_ = false;

	for (Entity* e : entitiesToAdd_)
		AddEntity(e);
	entitiesToAdd_.clear();

	// Check for if we should destroy an entity
}

inline void EntityManager::Draw(const SpriteBatch* spriteBatch)
{
	for (Entity* e : entities_)
		e->Draw(spriteBatch);
}

inline void EntityManager::AddEntity(Entity* entity)
{
	entities_.push_back(entity);
}

//bool EntityManager::isUpdating_ = false;
//std::vector<Entity*> EntityManager::entities_ = {};
//std::vector<Entity*> EntityManager::entitiesToAdd_ = {};