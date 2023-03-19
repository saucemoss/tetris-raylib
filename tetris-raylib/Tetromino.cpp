#include "Tetromino.h"
#include "Board.h"
#include <iostream>

Tetromino::Tetromino(const bool* shape, int dimension, Color color, const Board& board)
	:
	shape(shape),
	dimension(dimension),
	color(color),
	boardPos(board.GetWidth() / 2 - dimension / 2, 0),
	board(board),
	currentRotation(Rotation::UP),
	stop(false)
{
}

void Tetromino::RotateClockwise()
{
	if (CanMove("Rotate"))
	{
		if (int(currentRotation) != 3)
		{
			currentRotation = Rotation(int(currentRotation) + 1);
		}
		else
		{
			currentRotation = Rotation(0);
		}
	}
}

void Tetromino::RotateCounterClockwise()
{
	if (CanMove("Rotate"))
	{
		if (int(currentRotation) != 0)
		{
			currentRotation = Rotation(int(currentRotation) - 1);
		}
		else
		{
			currentRotation = Rotation(3);
		}
	}
}

void Tetromino::CheckStop()
{
	if (stop) 
	{
		for (int y = 0; y < dimension; ++y)
		{
			for (int x = 0; x < dimension; ++x)
			{
				bool cell = false;
				switch (currentRotation)
				{
				case Tetromino::Rotation::UP:
					cell = shape[y * dimension + x];
					break;
				case Tetromino::Rotation::RIGHT:
					cell = shape[dimension * (dimension - 1) - dimension * x + y];
					break;
				case Tetromino::Rotation::DOWN:
					cell = shape[(dimension * dimension - 1) - dimension * x - y];
					break;
				case Tetromino::Rotation::LEFT:
					cell = shape[dimension - 1 + dimension * x - y];
					break;
				default:
					break;
				}
				Vec2<int> finalPos = boardPos + Vec2<int>{x, y};

				if (cell && finalPos.InBounds({ board.GetWidth(),board.GetHeight() }))
				{
					board.getInstance().SetCell(boardPos + Vec2<int>{x, y}, color);
				}
			}
		}
	}
}


void Tetromino::MoveDown()
{
	if (CanMove("Down"))
	{
		SetBoardPos(Vec2<int>{ boardPos.GetX(), boardPos.GetY() + 1});
	}
}

void Tetromino::MoveLeft()
{
	if (CanMove("Left")) {
		SetBoardPos(Vec2<int>{ boardPos.GetX() - 1, boardPos.GetY()});
	}
}

void Tetromino::MoveRight()
{
	if (CanMove("Right"))
	{
		SetBoardPos(Vec2<int>{ boardPos.GetX() + 1, boardPos.GetY()});
	}
}

void Tetromino::SetBoardPos(Vec2<int> in_boardPos)
{
	boardPos = in_boardPos;
}

bool Tetromino::CanMove(std::string direction)
{
	if (!stop) 
	{
		for (int y = 0; y < dimension; ++y) {
			for (int x = 0; x < dimension; ++x) {
				bool cell = false;
				switch (currentRotation)
				{
				case Tetromino::Rotation::UP:
					cell = shape[y * dimension + x];
					break;
				case Tetromino::Rotation::RIGHT:
					cell = shape[dimension * (dimension - 1) - dimension * x + y];
					break;
				case Tetromino::Rotation::DOWN:
					cell = shape[(dimension * dimension - 1) - dimension * x - y];
					break;
				case Tetromino::Rotation::LEFT:
					cell = shape[dimension - 1 + dimension * x - y];
					break;
				default:
					break;
				}
				if (cell) 
				{
					if (direction == "Down" && (boardPos.GetY() + y + 1 >= board.GetHeight())) // Bottom boarder
					{
						stop = true;
						return false;
					}
					if (direction == "Down" && board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y + 1 })) // Other tetromino underneath
					{
						stop = true;
						return false;
					}
					if (direction == "Right" && (boardPos.GetX() + x + 1 >= board.GetWidth())) // Right boarder
					{
						return false;
					}
					if (direction == "Left" && (boardPos.GetX() + x <= 0)) // Left boarder
					{
						return false;
					}
					if (direction == "Rotate")
					{
						if (boardPos.GetX() > board.GetWidth()/2)  // Right boarder for rotate
						{
							if(boardPos.GetX() + x + 1 >= board.GetWidth())
							{
								return false;
							}	
						}
						if (boardPos.GetX() < board.GetWidth() / 2)  // Left boarder for rotate
						{
							if ((boardPos.GetX() + x <= 0))
							{
								return false;
							}
						}
					}
				} 
			}
		}
		return true;
	}
}

void Tetromino::Draw() const
{
	for (int y = 0; y < dimension; ++y) {
		for (int x = 0; x < dimension; ++x) {
			bool cell = false;
			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * x - y];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[dimension - 1 + dimension * x - y];
				break;
			default:
				break;
			}
			if (cell)
			{
				board.DrawCell(boardPos + Vec2<int>{x, y}, color);
			}
		}
	}

}
