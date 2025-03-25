/*


			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz

DigitalRain.cpp
*/

#include "DigitalRain.h" 
#include <iostream>     // cout, endl
#include <vector>       // vector
#include <string>       // string
#include <cstdlib>      // rand, srand
#include <ctime>        // time
#include <thread>       // for this_thread::sleep_for
#include <chrono>       // for chrono::milliseconds
#include <random>       // random_device, mt19937, uniform_int_distribution
#include <stdexcept>    // invalid_argument
#include <algorithm>    // for_each
#include <array>        // array
#include <memory>       // unique_ptr, make_unique

// Constants for color codes
constexpr const char* RED = "\033[31m";
constexpr const char* GREEN = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* CYAN = "\033[36m";
constexpr const char* WHITE = "\033[37m";

constexpr std::array<const char*, 7> COLORS = { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
constexpr int NUM_COLORS = COLORS.size();

// SimulationConfig class implementation
SimulationConfig::SimulationConfig(int width, int height, int numRaindrops, int raindropLengthMin, int raindropLengthMax,
	int symbolLengthMin, int symbolLengthMax, int animationSpeed)
	: width(width), height(height), numRaindrops(numRaindrops), raindropLengthMin(raindropLengthMin),
	raindropLengthMax(raindropLengthMax), symbolLengthMin(symbolLengthMin), symbolLengthMax(symbolLengthMax),
	animationSpeed(animationSpeed) {
}

// Getters for simulation parameters
int SimulationConfig::getWidth() const { return width; }
int SimulationConfig::getHeight() const { return height; }
int SimulationConfig::getNumRaindrops() const { return numRaindrops; }
int SimulationConfig::getRaindropLengthMin() const { return raindropLengthMin; }
int SimulationConfig::getRaindropLengthMax() const { return raindropLengthMax; }
int SimulationConfig::getSymbolLengthMin() const { return symbolLengthMin; }
int SimulationConfig::getSymbolLengthMax() const { return symbolLengthMax; }
int SimulationConfig::getAnimationSpeed() const { return animationSpeed; }

// Generate random integer
int randomInt(int min, int max) {
	if (min > max) {
		throw std::invalid_argument("min should not be greater than max");
	}
	thread_local std::random_device rd;
	thread_local std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

// Generate a string of random characters
std::string randomChars(int length) {
	if (length <= 0) {
		throw std::invalid_argument("length should be greater than 0");
	}
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%^&*()[]{}|<>";
	std::string result;
	result.reserve(length);
	for (int i = 0; i < length; ++i) {
		result += chars[randomInt(0, chars.length() - 1)];
	}
	return result;
}

// Function to generate a random color code
std::string randomColor() {
	return COLORS[randomInt(0, NUM_COLORS - 1)];
}

// Function to generate raindrops
std::vector<std::unique_ptr<Raindrop<std::string, std::string>>> generateRaindrops(const SimulationConfig& config) {
	std::vector<std::unique_ptr<Raindrop<std::string, std::string>>> raindrops;
	raindrops.reserve(config.getNumRaindrops());
	for (int i = 0; i < config.getNumRaindrops(); ++i) {
		std::string symbols = randomChars(randomInt(config.getSymbolLengthMin(), config.getSymbolLengthMax()));
		std::vector<std::string> colors;
		colors.reserve(symbols.length()); // Reserve space for colors
		for (char c : symbols) {
			colors.push_back(randomColor());
		}
		raindrops.emplace_back(std::make_unique<Raindrop<std::string, std::string>>(randomInt(0, config.getWidth() - 1), randomInt(0, config.getHeight() - 1), randomInt(config.getRaindropLengthMin(), config.getRaindropLengthMax()), symbols, colors));
	}
	return raindrops;
}

// Function to update the screen and color data
void updateScreen(Matrix& matrix, const std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops) {
	matrix.clear();
	for (const auto& drop : raindrops) {
		for (int i = 0; i < drop->getLength(); ++i) {
			int y = drop->getY() - i;
			if (y >= 0 && y < matrix.getHeight()) {
				int index = i % drop->getSymbols().length();
				matrix.setCell(drop->getX(), y, drop->getSymbols()[index], drop->getColors()[index]);
			}
		}
	}
}

// Function to move raindrops downwards
void moveRaindrops(std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops, const SimulationConfig& config) {
	for (auto& drop : raindrops) {
		drop->setY(drop->getY() + 1);
		if (drop->getY() - drop->getLength() >= config.getHeight()) {
			drop->setY(0);
			drop->setX(randomInt(0, config.getWidth() - 1));
			drop->setLength(randomInt(config.getRaindropLengthMin(), config.getRaindropLengthMax())); // Assign a new random length to the raindrop
			drop->setSymbols(randomChars(randomInt(config.getSymbolLengthMin(), config.getSymbolLengthMax()))); // New random symbols for each raindrop
			std::vector<std::string> newColors;
			newColors.reserve(drop->getSymbols().length());
			for (char c : drop->getSymbols()) {
				newColors.push_back(randomColor());
			}
			drop->setColors(newColors);
		}
	}
}

// Function to simulate rainfall
void simulateRainfall(const SimulationConfig& config) {
	if (config.getWidth() <= 0 || config.getHeight() <= 0 || config.getNumRaindrops() <= 0) {
		throw std::invalid_argument("width, height, and numRaindrops should be greater than 0");
	}

	auto raindrops = generateRaindrops(config);
	Matrix matrix(config.getWidth(), config.getHeight());

	std::cout << "\033[?25l";  // Hide cursor 

	try {
		while (true) {
			updateScreen(matrix, raindrops);
			matrix.print();
			moveRaindrops(raindrops, config);
			std::this_thread::sleep_for(std::chrono::milliseconds(config.getAnimationSpeed())); // Speed of the animation
			std::cout << "\033[H"; // Move the cursor back to the top-left corner
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}