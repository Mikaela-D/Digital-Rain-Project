/*


			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz

DigitalRain.h
*/

#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include <iostream>     // cout, endl
#include <vector>       // vector
#include <string>       // string
#include <memory>       // unique_ptr, make_unique

// Template class to represent a raindrop
template <typename SymbolType, typename ColorType>
class Raindrop {
public:
	// Constructor to initialize raindrop properties
	Raindrop(int x, int y, int length, const SymbolType& symbols, const std::vector<ColorType>& colors)
		: x(x), y(y), length(length), symbols(symbols), colors(colors) {
	}

	// Getters for raindrop properties
	int getX() const { return x; }
	int getY() const { return y; }
	int getLength() const { return length; }
	const SymbolType& getSymbols() const { return symbols; }
	const std::vector<ColorType>& getColors() const { return colors; }

	// Setters for raindrop properties
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	void setLength(int newLength) { length = newLength; }
	void setSymbols(const SymbolType& newSymbols) { symbols = newSymbols; }
	void setColors(const std::vector<ColorType>& newColors) { colors = newColors; }

private:
	int x; // x-coordinate of the raindrop
	int y; // y-coordinate of the raindrop
	int length;
	SymbolType symbols;
	std::vector<ColorType> colors;
};

// Class to represent the matrix screen and color data
class Matrix {
public:
	// Constructor to initialize matrix dimensions
	Matrix(int width, int height)
		: width(width), height(height), screen(height, std::vector<char>(width, ' ')),
		colorScreen(height, std::vector<std::string>(width, "\033[0m")) {
	}

	// Clear the matrix screen
	void clear() {
		for (int y = 0; y < height; ++y) {
			std::fill(screen[y].begin(), screen[y].end(), ' ');
			std::fill(colorScreen[y].begin(), colorScreen[y].end(), "\033[0m");
		}
	}

	// Set a cell in the matrix with a symbol and color
	void setCell(int x, int y, char symbol, const std::string& color) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			screen[y][x] = symbol;
			colorScreen[y][x] = color;
		}
	}

	// Print the matrix on the console
	void print() const {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				std::cout << colorScreen[y][x] << screen[y][x];
			}
			std::cout << "\033[0m" << std::endl; // Reset color at the end of each line
		}
		// Print the ground line
		std::cout << std::string(width, '_') << std::endl;
	}

	// Getters for matrix dimensions
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	int width; // Width of the matrix
	int height; // Height of the matrix
	std::vector<std::vector<char>> screen; // Characters on the matrix screen
	std::vector<std::vector<std::string>> colorScreen; // Colors for each character on the matrix screen
};

// Class to hold simulation parameters
class SimulationConfig {
public:
	// Constructor to initialise simulation parameters
	SimulationConfig(int width, int height, int numRaindrops, int raindropLengthMin, int raindropLengthMax, int animationSpeed);

	// Getters for simulation parameters
	int getWidth() const;
	int getHeight() const;
	int getNumRaindrops() const;
	int getRaindropLengthMin() const;
	int getRaindropLengthMax() const;
	int getAnimationSpeed() const;

private:
	int width; // Width of the simulation area
	int height; // Height of the simulation area
	int numRaindrops; // Number of raindrops in the simulation
	int raindropLengthMin; // Minimum length of a raindrop
	int raindropLengthMax; // Maximum length of a raindrop
	int animationSpeed; // Speed of the animation
};

// Function declarations
int randomInt(int min, int max);
std::string randomChars(int length);
std::string randomColor();
std::vector<std::unique_ptr<Raindrop<std::string, std::string>>> generateRaindrops(const SimulationConfig& config); // Updated declaration
void updateScreen(Matrix& matrix, const std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops); // Updated declaration
void moveRaindrops(std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops, const SimulationConfig& config); // Updated declaration
void simulateRainfall(const SimulationConfig& config);

#endif