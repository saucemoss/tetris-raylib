#pragma once
#include "RaylibCpp.h"
#include <vector>
#include "Vec2.h"
#include "Settings.h"
class Board
{
public:
	static Board& getInstance() 
	{
		static Board instance;
		return instance;
	} // instance
	Board(const Board&) = delete;
	Board & operator = (const Board&) = delete;
	//Meyer's Singleton

	void SetCell(Vec2<int> pos, Color c);
	void DrawCell(Vec2<int> pos) const;
	void DrawCell(Vec2<int> pos, Color color) const;
	void Draw() const;
	void DrawBorder() const;
	bool CellExists(Vec2<int> pos) const;
	int GetWidth() const;
	int GetHeight() const;

private:
	class Cell
	{
	public:
		Cell();
		void SetColor(Color c_in);
		void Remove();
		bool Exists() const;
		Color GetColor() const;
	private:
		bool bExists;
		Color c;
	};

	//Board(Vec2<int> screenPos, Vec2<int> widthHeight, int cellsize, int padding);
	Board();
	~Board() {}
	
	std::vector<Cell> cells;
	const int width = settings::boardWidthHeight.GetX();
	const int height = settings::boardWidthHeight.GetY();
	const int cellSize = settings::cellSize;
	const int padding = settings::padding;
	Vec2<int> screenPos = settings::boardPosition;


};