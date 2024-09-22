#include "game.h"

enum Colors {

	BLUE = 1,
	GREEN = 2,
	SKY_BLUE = 3,
	RED = 4,
	PURPLE = 5,
	YELLOW = 14,
	WHITE = 7
};

int main() {

	int WIDTH = 32;
	int HEIGHT = 16;

	int FREQUENCY = 10;

	int SNAKE_COLOR = GREEN;
	int FOOD_COLOR = RED;
	int BORDER_COLOR = BLUE;

	std::cout << "press any key to begin...\n";

	while (1) {

		// 1 - WIDTH
		// 2 - HEIGHT
		// 3 - FREQUENCY
		// 4 - SNAKE COLOR
		// 5 - FOOD COLOR
		// 6 - BORDER COLOR

		Game game(WIDTH, HEIGHT, FREQUENCY, SNAKE_COLOR, FOOD_COLOR, BORDER_COLOR);
		
		system("pause");
		system("cls");

		// SNAKE_LEN

		game.Start(5);
	}

	return 0;
}