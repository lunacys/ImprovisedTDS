#pragma once
#include "Engine.hpp"

#define TARGET_FPS 60.0
#define MS_PER_UPDATE (1 / TARGET_FPS)

class ImprovisedTDS
{
public:
	ImprovisedTDS();
	~ImprovisedTDS();

	void Start();
	void Exit();

	void Initialize();
	void LoadContent();
	void HandleInput();
	void Update(double dt);
	void Draw();

private:
	static void ErrorCallback(int error, const char* description);

	GLuint windowWidth_ = 800;
	GLuint windowHeight_ = 600;

	bool isProceed_ = true;

	GLFWwindow* gameWindow_ = nullptr;
	SpriteBatch* spriteBatch_ = nullptr;
	ContentManager* content_ = nullptr;
	Camera2D* camera_ = nullptr;
};

