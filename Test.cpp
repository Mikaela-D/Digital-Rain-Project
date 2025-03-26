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

// Function to test the Raindrop class
void testRaindrop() {
	// Create a Raindrop object with specific properties
	Raindrop<std::string, std::string> drop(5, 10, 4, "ABCD", { "\033[31m", "\033[32m", "\033[33m", "\033[34m" });

	// Verify the properties of the Raindrop object using assertions
	assert(drop.getX() == 5);
	assert(drop.getY() == 10);
	assert(drop.getLength() == 4);
	assert(drop.getSymbols() == "ABCD");
	assert(drop.getColors().size() == 4);

	// Modify the properties of the Raindrop object and verify again
	drop.setX(7);
	assert(drop.getX() == 7);

	drop.setY(15);
	assert(drop.getY() == 15);

	drop.setLength(6);
	assert(drop.getLength() == 6);

	std::cout << "testRaindrop() passed.\n";
}

// Function to test the Matrix class
void testMatrix() {
	// Create a Matrix object with specific dimensions
	Matrix matrix(10, 5);

	// Set a cell in the matrix and verify the dimensions
	matrix.setCell(2, 2, 'X', "\033[31m");
	assert(matrix.getWidth() == 10);
	assert(matrix.getHeight() == 5);

	// Clear the matrix and print a success message
	matrix.clear();
	std::cout << "testMatrix() passed.\n";
}

// Function to test the SimulationConfig class
void testSimulationConfig() {
	// Create a SimulationConfig object with specific parameters
	SimulationConfig config(120, 25, 10, 10, 15, 50);

	// Verify the parameters of the SimulationConfig object using assertions
	assert(config.getWidth() == 120);
	assert(config.getHeight() == 25);
	assert(config.getNumRaindrops() == 10);
	assert(config.getRaindropLengthMin() == 10);
	assert(config.getRaindropLengthMax() == 15);
	assert(config.getAnimationSpeed() == 50);

	std::cout << "testSimulationConfig() passed.\n";
}

// Function to test utility functions
void testUtilityFunctions() {
	// Test the randomInt function to generate a random integer within a range
	int randomValue = randomInt(1, 10);
	assert(randomValue >= 1 && randomValue <= 10);

	// Test the randomChars function to generate a string of random characters
	std::string chars = randomChars(5);
	assert(chars.size() == 5);

	// Test the randomColor function to generate a random color code
	std::string color = randomColor();
	assert(!color.empty());

	std::cout << "testUtilityFunctions() passed.\n";
}

// Function to run all tests
void runAllTests() {
	testRaindrop();
	testMatrix();
	testSimulationConfig();
	testUtilityFunctions();
	std::cout << "All tests passed successfully.\n";
}
