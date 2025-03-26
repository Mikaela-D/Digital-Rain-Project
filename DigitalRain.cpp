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

// Constants for color codes, evaluate at compile time
constexpr const char* RED = "\033[31m";
constexpr const char* GREEN = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* CYAN = "\033[36m";
constexpr const char* WHITE = "\033[37m";

// Array of color codes
constexpr std::array<const char*, 7> COLORS = { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
constexpr int NUM_COLORS = COLORS.size(); // Number of colors available

// SimulationConfig class implementation
SimulationConfig::SimulationConfig(int width, int height, int numRaindrops, int raindropLengthMin, int raindropLengthMax, int animationSpeed)
	: width(width), height(height), numRaindrops(numRaindrops), raindropLengthMin(raindropLengthMin), raindropLengthMax(raindropLengthMax),
	animationSpeed(animationSpeed) {
}

// Getters for simulation parameters
int SimulationConfig::getWidth() const { return width; }
int SimulationConfig::getHeight() const { return height; }
int SimulationConfig::getNumRaindrops() const { return numRaindrops; }
int SimulationConfig::getRaindropLengthMin() const { return raindropLengthMin; }
int SimulationConfig::getRaindropLengthMax() const { return raindropLengthMax; }
int SimulationConfig::getAnimationSpeed() const { return animationSpeed; }

// Generate random integer within a range
int randomInt(int min, int max) {
	if (min > max) {
		throw std::invalid_argument("min should not be greater than max");
	}
	thread_local std::random_device rd;  // Random device for generating seed
	thread_local std::mt19937 gen(rd()); // Mersenne Twister RNG
	std::uniform_int_distribution<> dist(min, max); // Uniform distribution
	return dist(gen); // Generate random number
}

// Generate a string of random characters
std::string randomChars(int length) {
	if (length <= 0) {
		throw std::invalid_argument("length should be greater than 0");
	}
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%^&*()[]{}|<>"; // Possible characters
	std::string result;
	result.reserve(length); // Reserve space for efficiency
	for (int i = 0; i < length; ++i) {
		result += chars[randomInt(0, chars.length() - 1)]; // Append random character
	}
	return result;
}

// Function to generate a random color code
std::string randomColor() {
	return COLORS[randomInt(0, NUM_COLORS - 1)]; // Select random color
}

// Function to generate raindrops based on the simulation configuration
std::vector<std::unique_ptr<Raindrop<std::string, std::string>>> generateRaindrops(const SimulationConfig& config) {
	std::vector<std::unique_ptr<Raindrop<std::string, std::string>>> raindrops;
	raindrops.reserve(config.getNumRaindrops()); // Reserve space for efficiency
	for (int i = 0; i < config.getNumRaindrops(); ++i) {
		std::string symbols = randomChars(randomInt(3, 5)); // Generate random symbols (hardcoded min and max lengths)
		std::vector<std::string> colors;
		colors.reserve(symbols.length()); // Reserve space for colors
		for (char c : symbols) {
			colors.push_back(randomColor()); // Assign random colour to each symbol
		}
		// Create new Raindrop object and add to the vector
		raindrops.emplace_back(std::make_unique<Raindrop<std::string, std::string>>(
			randomInt(0, config.getWidth() - 1),
			randomInt(0, config.getHeight() - 1),
			randomInt(config.getRaindropLengthMin(), config.getRaindropLengthMax()),
			symbols, colors
		));
	}
	return raindrops;
}

// Function to update the screen and color data based on the raindrops' positions
void updateScreen(Matrix& matrix, const std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops) {
	matrix.clear(); // Clear the matrix screen
	for (const auto& drop : raindrops) {
		for (int i = 0; i < drop->getLength(); ++i) {
			int y = drop->getY() - i; // Calculate new Y position
			if (y >= 0 && y < matrix.getHeight()) {
				int index = i % drop->getSymbols().length(); // Loop through symbols
				matrix.setCell(drop->getX(), y, drop->getSymbols()[index], drop->getColors()[index]); // Set cell with symbol and color
			}
		}
	}
}

// Function to move raindrops downwards and reset them when they go off-screen
void moveRaindrops(std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops, const SimulationConfig& config) {
	for (auto& drop : raindrops) {
		drop->setY(drop->getY() + 1); // Move raindrop down by one
		// Reset raindrop if it goes off-screen
		if (drop->getY() - drop->getLength() >= config.getHeight()) {
			drop->setY(0); // Reset Y position to top
			drop->setX(randomInt(0, config.getWidth() - 1)); // Assign new random X position
			drop->setLength(randomInt(config.getRaindropLengthMin(), config.getRaindropLengthMax())); // Assign a new random length to the raindrop
			drop->setSymbols(randomChars(randomInt(3, 5))); // New random symbols for each raindrop (hardcoded min and max lengths)
			std::vector<std::string> newColors;
			newColors.reserve(drop->getSymbols().length());
			for (char c : drop->getSymbols()) {
				newColors.push_back(randomColor()); // Assign new random colours
			}
			drop->setColors(newColors); // Set new colours
		}
	}
}

// Function to simulate rainfall
void simulateRainfall(const SimulationConfig& config) {
	// Validate the simulation configuration
	if (config.getWidth() <= 0 || config.getHeight() <= 0 || config.getNumRaindrops() <= 0) {
		throw std::invalid_argument("width, height, and numRaindrops should be greater than 0");
	}

	// Generate initial raindrops based on the configuration
	auto raindrops = generateRaindrops(config);
	Matrix matrix(config.getWidth(), config.getHeight()); // Create matrix for display

	std::cout << "\033[?25l";  // Hide cursor 

	try {
		while (true) {
			// Update the screen with the current positions of the raindrops
			updateScreen(matrix, raindrops);
			// Print the updated matrix to the console
			matrix.print();
			// Move the raindrops downwards
			moveRaindrops(raindrops, config);
			// Pause for the animation speed duration
			std::this_thread::sleep_for(std::chrono::milliseconds(config.getAnimationSpeed())); // Speed of the animation
			std::cout << "\033[H"; // Move the cursor back to the top-left corner
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}