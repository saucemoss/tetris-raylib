#include <assert.h>
#include "Game.h"
#include <raylib.h>
#include "Settings.h"
#include <iostream>


Game::Game(int width, int height, int fps, std::string title)
	:
	board(Board::getInstance()),
	tetromino(board),
	timeInterval((float)1),
	elapsedTime(0),
	t(new Jay(board))
	
{
	assert(!GetWindowHandle());	//If assertion triggers : Window is already opened
	SetTargetFPS(fps);
	InitWindow(width, height, title.c_str());
}

Game::~Game() noexcept
{
	assert(GetWindowHandle()); //if assertion triggers : Window is already closed
	CloseWindow();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}


void Game::Update()
{
	if (IsKeyPressed(KEY_E)) 
	{
		t->RotateClockwise();
	}
	if (IsKeyPressed(KEY_Q))
	{
		t->RotateCounterClockwise();
	}
	if (IsKeyPressed(KEY_S))
	{
		t->MoveDown();
	}
	if (IsKeyPressed(KEY_A))
	{
		t->MoveLeft();
	}
	if (IsKeyPressed(KEY_D))
	{
		t->MoveRight();
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		t = new Jay(board);
	}
	t->CheckStop();
	UpdateTimeCounter();

	if (t->stop)
	{
		//delete t;
		
	}
}


void Game::Draw()
{
	ClearBackground(BLACK);
	board.Draw();
	t->Draw();
}

void Game::UpdateTimeCounter()
{
	elapsedTime += GetFrameTime();
	if (elapsedTime >= timeInterval) {
		t->MoveDown();
		elapsedTime = 0;
	}
}
