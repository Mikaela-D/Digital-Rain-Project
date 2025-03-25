/*


			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Test.cpp

Mikaela Diaz
*/

#include "DigitalRain.h"
#include "Test.h"
#include <iostream>        // cout, endl
#include <cassert>         // assert

void testRaindrop() {
	Raindrop<std::string, std::string> drop(5, 10, 4, "ABCD", { "\033[31m", "\033[32m", "\033[33m", "\033[34m" });

	assert(drop.getX() == 5);
	assert(drop.getY() == 10);
	assert(drop.getLength() == 4);
	assert(drop.getSymbols() == "ABCD");
	assert(drop.getColors().size() == 4);

	drop.setX(7);
	assert(drop.getX() == 7);

	drop.setY(15);
	assert(drop.getY() == 15);

	drop.setLength(6);
	assert(drop.getLength() == 6);

	std::cout << "testRaindrop() passed.\n";
}

void testMatrix() {
	Matrix matrix(10, 5);

	matrix.setCell(2, 2, 'X', "\033[31m");
	assert(matrix.getWidth() == 10);
	assert(matrix.getHeight() == 5);

	matrix.clear();
	std::cout << "testMatrix() passed.\n";
}

void testSimulationConfig() {
	SimulationConfig config(120, 25, 10, 10, 15, 3, 5, 50);

	assert(config.getWidth() == 120);
	assert(config.getHeight() == 25);
	assert(config.getNumRaindrops() == 10);
	assert(config.getRaindropLengthMin() == 10);
	assert(config.getRaindropLengthMax() == 15);
	assert(config.getSymbolLengthMin() == 3);
	assert(config.getSymbolLengthMax() == 5);
	assert(config.getAnimationSpeed() == 50);

	std::cout << "testSimulationConfig() passed.\n";
}

void testUtilityFunctions() {
	int randomValue = randomInt(1, 10);
	assert(randomValue >= 1 && randomValue <= 10);

	std::string chars = randomChars(5);
	assert(chars.size() == 5);

	std::string color = randomColor();
	assert(!color.empty());

	std::cout << "testUtilityFunctions() passed.\n";
}

void runAllTests() {
	testRaindrop();
	testMatrix();
	testSimulationConfig();
	testUtilityFunctions();
	std::cout << "All tests passed successfully.\n";
}
