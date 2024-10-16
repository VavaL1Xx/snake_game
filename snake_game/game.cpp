#include "game.h"
#include <windows.h>
#include <conio.h>


Game::Game(int W, int H, int FREQUENCY, int SNAKE_COLOR, int FOOD_COLOR, int BORDER_COLOR, char SYMBOL) : HEIGHT(H + 2), WIDTH(W + 2) {

	srand(time(NULL));

	GAME_OVER = false;
	SCORE = 0;

	this->SNAKE_COLOR = SNAKE_COLOR;
	this->FOOD_COLOR = FOOD_COLOR;
	this->BORDER_COLOR = BORDER_COLOR;
	this->FREQUENCY = FREQUENCY;
	this->SYMBOL = SYMBOL;

	GAME_MAP = new Block * [HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		GAME_MAP[i] = new Block[WIDTH];
	}

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);


	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if ((i == 0 || i == HEIGHT - 1) || ((i > 0 && i < HEIGHT - 1) && (j == 0 || j == WIDTH - 1))) {
				GAME_MAP[i][j].symbol = SYMBOL;
			}

			GAME_MAP[i][j].xPos = j;
			GAME_MAP[i][j].yPos = i;
		}
	}

	CreateFood();
}

Game::~Game() {

	for (int i = 0; i < HEIGHT; i++) {
		delete[] GAME_MAP[i];
	}

	delete[] GAME_MAP;
	GAME_MAP = nullptr;
}

void Game::DrawMap(Snake& SNAKE) {

	ResetCursor();

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GAME_OVER) SetConsoleTextAttribute(h, BORDER_COLOR);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {

			if (i > 0 && i < HEIGHT - 1 && j > 0 && j < WIDTH - 1 && !GAME_OVER)
				SetConsoleTextAttribute(h, SNAKE_COLOR);

			if (i == FOOD.yPos && j == FOOD.xPos && !GAME_OVER)
				SetConsoleTextAttribute(h, FOOD_COLOR);

			std::cout << GAME_MAP[i][j];
			if (!GAME_OVER) SetConsoleTextAttribute(h, BORDER_COLOR);

		}
		std::cout << std::endl;
	}

	if (!GAME_OVER) SetConsoleTextAttribute(h, 7);
	std::cout << "\nSCORE: " << SCORE << std::endl;
	std::cout << "SNAKE LENGTH: " << SNAKE.GetLength() << std::endl;
	std::cout << "FREQUENCY: " << FREQUENCY << std::endl;
}

bool Game::CreateFood(int x_pos, int y_pos) {

	while (SCORE < ((WIDTH - 2) * (HEIGHT - 2))) {

		x_pos = WIDTH == 3 ? 1 : rand() % (WIDTH - 2) + 1;
		y_pos = HEIGHT == 3 ? 1 : rand() % (HEIGHT - 2) + 1;

		if (GAME_MAP[y_pos][x_pos].symbol == ' ') {

			FOOD = Block(x_pos, y_pos, SYMBOL);
			GAME_MAP[y_pos][x_pos].symbol = SYMBOL;

			return true;
		}
	}
	return false;
}

void Game::Start(int SNAKE_LENGTH) {

	Snake SNAKE(SNAKE_LENGTH, SYMBOL);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	DrawMap(SNAKE);

	while (!GAME_OVER) {

		Plot(SNAKE.GetHead(), SNAKE);
		SNAKE.ChangeDir();
		SNAKE.Move();

		if (SNAKE.CheckFood(FOOD)) {

			SNAKE.ExpandSnake();
			SCORE++;

			if (!(SCORE % 10))
				FREQUENCY += 1;

			if (!CreateFood())
				GAME_OVER = true;
		}
		else if (!SNAKE.CheckCollision(GAME_MAP))
			GAME_OVER = true;

		Sleep(1000 / FREQUENCY);
	}

	if (SCORE == (WIDTH - 2) * (HEIGHT - 2))
		SetConsoleTextAttribute(h, 2);
	else
		SetConsoleTextAttribute(h, 4);

	std::cout << "\nGAME OVER!" << std::endl;
	DrawMap(SNAKE);
	SetConsoleTextAttribute(h, 7);
	std::cout << "\n\n\n";
}

void Game::ResetCursor() {

	COORD position = { 0,0 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}


Game::Snake::Snake(int length, char symbol) : SNAKE_LEN(length) {

	SNAKE_BODY = new Block[SNAKE_LEN];
	CURRENT_DIR = DOWN;

	for (int i = 0; i < SNAKE_LEN; i++)
		SNAKE_BODY[i] = Block(1, 0, symbol);
}

Game::Snake::~Snake() {

	delete[] SNAKE_BODY;
	SNAKE_BODY = nullptr;
}

void Game::Plot(Block* SNAKE_BODY, Snake& SNAKE) {

	for (int i = 0; i < SNAKE.GetLength(); i++)
		GAME_MAP[SNAKE_BODY[i].yPos][SNAKE_BODY[i].xPos].symbol = SYMBOL;

	DrawMap(SNAKE);

	if (SNAKE_BODY[SNAKE.GetLength() - 1].yPos != 0 || SNAKE_BODY[SNAKE.GetLength() - 1].xPos != 1) {
		GAME_MAP[SNAKE_BODY[SNAKE.GetLength() - 1].yPos][SNAKE_BODY[SNAKE.GetLength() - 1].xPos].symbol = ' ';
	}

}

void Game::Snake::Move() {

	for (int i = SNAKE_LEN - 1; i > 0; i--) {

		SNAKE_BODY[i].xPos = SNAKE_BODY[i - 1].xPos;
		SNAKE_BODY[i].yPos = SNAKE_BODY[i - 1].yPos;
	}

	switch (CURRENT_DIR) {

	case UP:
		SNAKE_BODY[0].yPos -= 1;
		break;
	case DOWN:
		SNAKE_BODY[0].yPos += 1;
		break;
	case LEFT:
		SNAKE_BODY[0].xPos -= 1;
		break;
	case RIGHT:
		SNAKE_BODY[0].xPos += 1;
		break;
	}
}

void Game::Snake::ChangeDir() {

	if (_kbhit()) {

		switch (_getch()) {

		case KEY_UP:
		case 'ö':
		case 'w':
			if (CURRENT_DIR != DOWN)
				CURRENT_DIR = UP;
			break;

		case KEY_DOWN:
		case 'û':
		case 's':
			if (CURRENT_DIR != UP)
				CURRENT_DIR = DOWN;
			break;

		case KEY_LEFT:
		case 'ô':
		case 'a':
			if (CURRENT_DIR != RIGHT)
				CURRENT_DIR = LEFT;
			break;

		case KEY_RIGHT:
		case 'â':
		case 'd':
			if (CURRENT_DIR != LEFT)
				CURRENT_DIR = RIGHT;
			break;

		case SPACE:
			system("pause");
			system("cls");
			break;

		case ESC:
			exit(EXIT_FAILURE);
			break;
		}
	}
}

bool Game::Snake::CheckCollision(Block** GAME_MAP) {
	return GAME_MAP[SNAKE_BODY[0].yPos][SNAKE_BODY[0].xPos].symbol == ' ';
}

bool Game::Snake::CheckFood(Block FOOD) {
	return SNAKE_BODY[0].xPos == FOOD.xPos && SNAKE_BODY[0].yPos == FOOD.yPos;
}

void Game::Snake::ExpandSnake() {

	Block* newArr = new Block[SNAKE_LEN + 1];

	for (int i = 0; i < SNAKE_LEN; i++)
		newArr[i] = SNAKE_BODY[i];

	newArr[SNAKE_LEN].xPos = SNAKE_BODY[SNAKE_LEN - 1].xPos;
	newArr[SNAKE_LEN].yPos = SNAKE_BODY[SNAKE_LEN - 1].yPos;

	SNAKE_LEN++;
	delete[] SNAKE_BODY;
	SNAKE_BODY = newArr;
	newArr = nullptr;
}
