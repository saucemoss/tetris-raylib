#pragma once
#include "Vec2.h"
#include <string>
namespace settings
{
	//Window settings
	inline constexpr int screenWidth = 800;
	inline constexpr int screenHeight = 600;
	inline constexpr int fps = 60;
	inline const std::string windowTitle = "Tetris with Raylib";

	//Board settings
	inline constexpr int cellSize = 23;
	inline constexpr int padding = 2;
	inline constexpr Vec2<int> boardPosition{ 250, 70 };
	inline constexpr Vec2<int> boardWidthHeight{ 10, 20 };

}