#include <core/Game.hpp>
#include <iostream>
#include <resources/Assets.hpp>

int main()
{
	Assets::Initialize();

	Game demo{};

	try 
	{
		demo.run();
	} 
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}