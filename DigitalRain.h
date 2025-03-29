// DigitalRain.h

#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <random>

class Raindrop {
public:
	int x;
	int y;
	int length;
	std::vector<char> symbols;
	std::vector<std::string> colors;

	Raindrop(int startX, int startY, int dropLength, const std::vector<char>& dropSymbols, const std::vector<std::string>& dropColors)
		: x(startX), y(startY), length(dropLength), symbols(dropSymbols), colors(dropColors) {
	}
};

class Screen {
public:
	int width;
	int height;
	std::vector<std::vector<char>> screen;
	std::vector<std::vector<std::string>> colorScreen;

	Screen(int screenWidth, int screenHeight)
		: width(screenWidth), height(screenHeight), screen(screenHeight, std::vector<char>(screenWidth, ' ')),
		colorScreen(screenHeight, std::vector<std::string>(screenWidth, "\033[0m")) {
	}

	void clear() {
		for (auto& row : screen) {
			std::fill(row.begin(), row.end(), ' ');
		}
		for (auto& row : colorScreen) {
			std::fill(row.begin(), row.end(), "\033[0m");
		}
	}

	void setCell(int x, int y, char symbol, const std::string& color) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			screen[y][x] = symbol;
			colorScreen[y][x] = color;
		}
	}

	void print() const {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				std::cout << colorScreen[y][x] << screen[y][x];
			}
			std::cout << "\033[0m" << std::endl;
		}
		std::cout << std::string(width, '_') << std::endl;
	}
};

class SimulationConfig {
public:
	int width;
	int height;
	int numRaindrops;
	int raindropLengthMin;
	int raindropLengthMax;
	int animationSpeed;

	SimulationConfig(int screenWidth, int screenHeight, int numDrops, int lengthMin, int lengthMax, int speed)
		: width(screenWidth), height(screenHeight), numRaindrops(numDrops), raindropLengthMin(lengthMin),
		raindropLengthMax(lengthMax), animationSpeed(speed) {
	}
};

int randomInt(int min, int max);
std::vector<char> randomChars(int length);
std::string randomColor();
std::vector<Raindrop> generateRaindrops(const SimulationConfig& config);
void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops);
void moveRaindrops(std::vector<Raindrop>& raindrops, const SimulationConfig& config);
void simulateRainfall(const SimulationConfig& config);

#endif // DIGITALRAIN_H