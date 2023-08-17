#include "Errors.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>

// Prints out an error message and exits the game
void fatalError(std::string errorMsg) {
	std::cout << errorMsg << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(100);
}