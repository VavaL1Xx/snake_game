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

void GetHelp();

int main(int argc, char* argv[]) {

	int WIDTH = 32;
	int HEIGHT = 16;

	int FREQUENCY = 10;

	int SNAKE_COLOR = GREEN;
	int FOOD_COLOR = RED;
	int BORDER_COLOR = BLUE;

	char SYMBOL = char(219);

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
			WIDTH = std::atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
			HEIGHT = std::atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-freq") == 0 && i + 1 < argc) {
			FREQUENCY = std::atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-sncol") == 0 && i + 1 < argc) {
			SNAKE_COLOR = std::atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-fdcol") == 0 && i + 1 < argc) {
			FOOD_COLOR = std::atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-bdcol") == 0 && i + 1 < argc) {
			BORDER_COLOR = std::atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-symb") == 0 && i + 1 < argc) {
			SYMBOL = argv[++i][0];
		}
		else if (strcmp(argv[i], "-help") == 0) {
			GetHelp();
			return 0;
		}
		else {
			std::cerr << "\nUnknown argument: " << argv[i] << "\n";
			return 0;
		}
	}

	if (argc > 1) std::cout << "\n*** input [-help] for more information ***\n";
	
	std::cout << "starting game with parameters:\n\n";
	std::cout << "width: " << WIDTH << "\n";
	std::cout << "height: " << HEIGHT << "\n";
	std::cout << "frequency: " << FREQUENCY << "\n";
	std::cout << "snake color: " << SNAKE_COLOR << "\n";
	std::cout << "food color: " << FOOD_COLOR << "\n";
	std::cout << "border color: " << BORDER_COLOR << "\n";
	std::cout << "symbol: " << SYMBOL << "\n";

	std::cout << "\npress any key to begin...\n";

	while (1) {

		// 1 - WIDTH
		// 2 - HEIGHT
		// 3 - FREQUENCY
		// 4 - SNAKE COLOR
		// 5 - FOOD COLOR
		// 6 - BORDER COLOR
		// 7 - SYMBOL

		Game game(WIDTH, HEIGHT, FREQUENCY, SNAKE_COLOR, FOOD_COLOR, BORDER_COLOR, SYMBOL);
		
		system("pause");
		system("cls");

		// SNAKE_LEN

		game.Start(5);
	}

	return 0;
}

void GetHelp() {

	std::cout << "\n-w \t:width of game map\n";
	std::cout << "-h \t:height of game map\n";
	std::cout << "-freq \t:frequency of game\n\n";
	std::cout << "-symb \t:drawing symbol\n\n";

	std::cout << "-sncol \t: snake color\n";
	std::cout << "-fdcol \t: food color\n";
	std::cout << "-bdcol \t: border color\n\n";
}