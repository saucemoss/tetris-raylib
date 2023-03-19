#include "Board.h"
#include <assert.h>
#include "Settings.h"
Board::Cell::Cell()
	:
	bExists(false),
	c(WHITE)
{
}

void Board::Cell::SetColor(Color c_in)
{
	c = c_in;
	bExists = true;
}

void Board::Cell::Remove()
{
	bExists = false;
}

bool Board::Cell::Exists() const
{
	return bExists;
}

Color Board::Cell::GetColor() const
{
	return c;
}

Board::Board() 
{
	assert(width > 0 && height > 0); //If assertion triggrs : The width or height is smaller than 0
	assert(cellSize > 0); //If assertion triggrs : The cell size is smaller than 1
	cells.resize(width * height);
}


void Board::SetCell(Vec2<int> pos, Color c)
{	
	assert(pos.InBounds(Vec2{ width,height })); //If assertion triggers pos vec out of bounds
	cells[pos.GetY() * width + pos.GetX()].SetColor(c);
}

void Board::DrawCell(Vec2<int> pos) const
{
	Color color = cells[pos.GetY() * width + pos.GetX()].GetColor();
	DrawCell(pos, color);
}

void Board::DrawCell(Vec2<int> pos, Color color) const
{
	assert(pos.InBounds(Vec2{ width,height })); //If assertion triggers pos vec out of bounds
	Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
	raycpp::DrawRectangle(topLeft,
		Vec2{ cellSize, cellSize } - padding, color);
}

void Board::Draw() const
{
	for (int iY = 0; iY < height; iY++) 
	{
		for (int iX = 0; iX < width; iX++)
		{
			if (CellExists({ iX,iY })) 
			{
				DrawCell({ iX,iY });
			}
		}
	}
	DrawBorder();
}

void Board::DrawBorder() const
{
	raycpp::DrawRectangleLinesEx(screenPos - (cellSize / 2),
		Vec2{width * cellSize,height * cellSize} + cellSize,
		cellSize/2,
		WHITE);
}

bool Board::CellExists(Vec2<int> pos) const
{
	return cells[pos.GetY()*width + pos.GetX()].Exists();
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
