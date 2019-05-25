#include <iostream>
#include "ImprovisedTDS.hpp"

int main()
{
	// TODO list:
	//  - InputManager class that grants free access to input devices such as keyboard or mouse
	//  - Keyboard+KeyboardState/Mouse+MouseState helper class/struct that makes access to input devices easier
	//  - GameTime helper class
	//  - GameTimer class
	//  - Sprite and Animation classes
	//  - FPS/SPF (seconds per frame) counter
	//  - FontReader class that reads truetype and bitmap fonts
	//  - Vector3 struct that is the 3-Dimensional copy of Vector2
	//  - Color struct that contains color info (RGBA values) and some precompiled colors
	//  - ColorData/TextureData helper struct that contains low-level image info
	//  - Help classes: Math Utils
	//  - Collision manager
	//  - 2D Primitives class
	//  - Obstacle struct which will help for collision testing
	//  - Gui
	//  - Screen system
	//  - Level generator/Level reader
	//  - Lots of refactoring
	//  - Sound/Music support
	//  - Particle system
	//  - Redo ContentManager
	//  - more things..

	//  - Add comments to the code (even russian will be ok)
	//  - Engine should give to user all neccessary classes to work with the game, user shouldn't use GLFW/GML/GLEW/etc directly
	//  - Separate Engine to the separate project (DLL) and write its own API
	//  - Add multithreading support
	//  - (?) Add multiplayer/networking support
	//  - (?) Add Lua/Python and then modding support


	ImprovisedTDS* game = new ImprovisedTDS();
	try
	{
		game->Start();
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
		system("pause");
		//exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

