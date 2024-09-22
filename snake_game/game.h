#pragma once
#include<iostream>

class Game {

private:

	class Block {

	public:

		unsigned char symbol;
		unsigned short xPos : 8;
		unsigned short yPos : 8;

		Block(int xPos = 0, int yPos = 0, char symbol = ' ') {

			this->xPos = xPos;
			this->yPos = yPos;
			this->symbol = symbol;
		}

		friend std::ostream& operator<< (std::ostream& out, const Block& obj) {

			out << obj.symbol << obj.symbol;
			return out;
		}
	};

	class Snake {

	private:

		enum
		{
			KEY_UP = 72,
			KEY_DOWN = 80,
			KEY_LEFT = 75,
			KEY_RIGHT = 77,
			SPACE = 32,
			ESC = 27
		};

		enum Direction { UP, DOWN, LEFT, RIGHT };
		Direction CURRENT_DIR;

		unsigned short SNAKE_LEN;

		Block* SNAKE_BODY;

	public:

		Snake(int length);
		~Snake();

		void ChangeDir();
		void ExpandSnake();

		int GetLength() { return SNAKE_LEN; }
		Block* GetHead() { return &SNAKE_BODY[0]; }

		void Move();
		bool CheckCollision(Block** GAME_MAP);
		bool CheckFood(Block FOOD);
	};

	const unsigned short HEIGHT;
	const unsigned short WIDTH;

	int SNAKE_COLOR;
	int FOOD_COLOR;
	int BORDER_COLOR;

	int FREQUENCY;

	Block** GAME_MAP;
	Block FOOD;

	short SCORE;
	bool GAME_OVER;

	bool CreateFood(int x_pos = 0, int y_pos = 0);

	void DrawMap(Snake& SNAKE);
	void ResetCursor();
	void Plot(Block* SNAKE_BODY, Snake& SNAKE);

public:

	Game(int W, int H, int FREQUENCY = 5, int SNAKE_COLOR = 2, int FOOD_COLOR = 4, int BORDER_COLOR = 7);
	~Game();

	void Start(int SNAKE_LENGTH = 3);
};