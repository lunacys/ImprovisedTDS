#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>

/*enum class Keys
{
	Unknown = -1,
	Space = 32,
	Zero = 48,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Escape = 256,
	Enter,
	Tab,
	Right = 262,
	Left,
	Down,
	Up
};

enum class MouseButton
{
	Left = 0,
	Right = 1
};

class InputManager
{
public:
	InputManager(GLFWwindow* window);
	~InputManager();
	bool IsKeyDown(const Keys& key);
	bool IsMouseButtonDown(const MouseButton& button);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallback(GLFWwindow* window, int button, int action, int mods);
private:
	static bool keys_[1024];// = {false};
	bool mouseButtons_[8] = {false};
	GLFWwindow* window_;
};

bool InputManager::keys_[1024] = { };

inline InputManager::InputManager(GLFWwindow* window)
{
	window_ = window;

	if (!window_)
		throw std::runtime_error("ERROR: Window cannot be null");

	glfwSetKeyCallback(window_, [](GLFWwindow* wd, int key, int scancode, int action, int mods)
	{
		
	});
	//glfwSetMouseButtonCallback(window_, MouseCallback);
}

inline InputManager::~InputManager()
{

}

inline bool InputManager::IsKeyDown(const Keys& key)
{
	//if (!window_)
	//	throw std::runtime_error("ERROR: Initialize first");

	return keys_[int(key)];
}

inline bool InputManager::IsMouseButtonDown(const MouseButton& button)
{
	if (!window_)
		throw std::runtime_error("ERROR: Initialize first");

	return mouseButtons_[int(button)];
}

inline void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (!window_)
	//	throw std::runtime_error("ERROR: Initialize first");

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys_[key] = true;
		else if (action == GLFW_RELEASE)
			keys_[key] = false;
	}
}

inline void InputManager::MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (!window_)
		throw std::runtime_error("ERROR: Initialize first");

	if (button >= 0 && button < 8)
	{
		if (action == GLFW_PRESS)
			mouseButtons_[button] = true;
		else if (action == GLFW_RELEASE)
			mouseButtons_[button] = false;
	}
}*/
