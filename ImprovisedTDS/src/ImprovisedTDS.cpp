#define STB_IMAGE_IMPLEMENTATION

#include "ImprovisedTDS.hpp"
#include "EntityManager.hpp"
#include "AssetBank.hpp"
#include "Player.hpp"
#include <ctime>

ImprovisedTDS::ImprovisedTDS()
{ }

ImprovisedTDS::~ImprovisedTDS()
{
	delete content_;
	delete spriteBatch_;
	delete camera_;
	glfwDestroyWindow(gameWindow_);
	glfwTerminate();
}

void ImprovisedTDS::Start()
{
	Initialize();
	LoadContent();

	double lastTimeLocked = glfwGetTime();
	double previous = glfwGetTime();
	double lag = 0.0;
	int nbFramesLocked = 0;

	while(isProceed_ && !glfwWindowShouldClose(gameWindow_))
	{
		double currentTime = glfwGetTime();
		double elapsed = currentTime - previous; // delta time
		previous = currentTime;
		lag += elapsed;

		glfwPollEvents();
		HandleInput();

		while (lag >= MS_PER_UPDATE)
		{
			nbFramesLocked++;
			if (currentTime - lastTimeLocked >= 1.0)
			{
				std::cout << 1000.0 / double(nbFramesLocked) << " ms/frame" << std::endl;
				// Target values are: 60fps - 16.6666ms, 30fps - 33.3333ms
				// formula: (1/targetFps)*1000
				nbFramesLocked = 0;
				lastTimeLocked += 1.0;
			}
			Update(elapsed); // TODO: Repair very fast Update when user drags the game window

			lag -= MS_PER_UPDATE;
		}
		//std::thread t(&ImprovisedTDS::Draw, this);
		//t.join();
		Draw();
	}
}

void ImprovisedTDS::Exit()
{
	isProceed_ = false;
	glfwSetWindowShouldClose(gameWindow_, GL_TRUE);
}

void ImprovisedTDS::Initialize()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		throw std::exception("ERROR: Couldn't initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	gameWindow_ = glfwCreateWindow(windowWidth_, windowHeight_, "Improvised TDS", nullptr, nullptr);
	if (!gameWindow_)
		throw std::exception("ERROR: Couldn't create GLFW window");

	glfwMakeContextCurrent(gameWindow_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::exception("ERROR: Failed to initialize OpenGL context");
	}

	glfwSwapInterval(1);

	// TODO: Check this!
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 
	glViewport(0, 0, windowWidth_, windowHeight_);

	content_ = new ContentManager();
	content_->SetRootDirectory("Content");

	srand((unsigned int)time(nullptr));


}

void ImprovisedTDS::LoadContent()
{
	spriteBatch_ = new SpriteBatch();

	AssetBank::LoadAll();

	Player* p = new Player(AssetBank::Wall3, Vector2f(64, 64));
	camera_ = new Camera2D(p, glm::vec2(0, 0));

	EntityManager::Add(p);
}

void ImprovisedTDS::HandleInput()
{
	if (glfwGetKey(gameWindow_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		Exit();
	if (glfwGetKey(gameWindow_, GLFW_KEY_A) == GLFW_PRESS)
		camera_->Move(glm::vec2(-1.0f, 0.0f));
	if (glfwGetKey(gameWindow_, GLFW_KEY_D) == GLFW_PRESS)
		camera_->Move(glm::vec2(1.0f, 0.0f));
	if (glfwGetKey(gameWindow_, GLFW_KEY_W) == GLFW_PRESS)
		camera_->Move(glm::vec2(0.0f, -1.0f));
	if (glfwGetKey(gameWindow_, GLFW_KEY_S) == GLFW_PRESS)
		camera_->Move(glm::vec2(0.0f, 1.0f));
	/*if (glfwGetKey(gameWindow_, GLFW_KEY_F) == GLFW_PRESS)
		camera_->Zoom += 0.01f;
	if (glfwGetKey(gameWindow_, GLFW_KEY_G) == GLFW_PRESS)
		camera_->Zoom -= 0.01f;
	if (glfwGetKey(gameWindow_, GLFW_KEY_Z) == GLFW_PRESS)
		camera_->Rotation += 0.1f;
	if (glfwGetKey(gameWindow_, GLFW_KEY_X) == GLFW_PRESS)
		camera_->Rotation -= 0.1f;*/

	EntityManager::HandleInput();
}

void ImprovisedTDS::Update(double dt)
{
	//content_->GetShader("Sprite")->SetUniform("view", camera_->GetViewMatrix());
	//camera_->MoveTo(glm::vec2(100, 100), 1, dt);
	camera_->Update(dt);
	EntityManager::Update(float(dt));
}

void ImprovisedTDS::Draw()
{
	glClearColor(0.2f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	spriteBatch_->Begin(camera_->GetViewMatrix());

	for (unsigned int i = 0; i < windowWidth_; i += 32)
	{
		for (unsigned int j = 0; j < windowHeight_; j += 32)
		{
			glm::vec2 pos(i, j);
			if (i == 0 || j == 0 || i == windowWidth_ - 32 || j == windowHeight_ - 32)
				spriteBatch_->Draw(AssetBank::Wall1, pos);
			else
				spriteBatch_->Draw(AssetBank::Floor, pos);
		}
	}
	EntityManager::Draw(spriteBatch_);
	spriteBatch_->End();

	glfwSwapBuffers(gameWindow_);
}

void ImprovisedTDS::ErrorCallback(int error, const char* description)
{
	std::cerr << "ERROR: Code: " << error << "; " << description << std::endl;
}
