// DigitalRain.h

#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <random>

class Raindrop {
public:
	int x, y, length;
	std::vector<char> symbols;
	std::vector<std::string> colors;

	Raindrop(int x, int y, int length, const std::vector<char>& symbols, const std::vector<std::string>& colors)
		: x(x), y(y), length(length), symbols(symbols), colors(colors) {
	}
};

class Screen {
public:
	int width, height;
	std::vector<std::vector<char>> screen;
	std::vector<std::vector<std::string>> colorScreen;

	Screen(int width, int height)
		: width(width), height(height), screen(height, std::vector<char>(width, ' ')), colorScreen(height, std::vector<std::string>(width, "\033[0m")) {
	}

	void clear() {
		for (auto& row : screen) std::fill(row.begin(), row.end(), ' ');
		for (auto& row : colorScreen) std::fill(row.begin(), row.end(), "\033[0m");
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
	int width, height, numRaindrops, raindropLengthMin, raindropLengthMax, animationSpeed;

	SimulationConfig(int width, int height, int numRaindrops, int raindropLengthMin, int raindropLengthMax, int animationSpeed)
		: width(width), height(height), numRaindrops(numRaindrops), raindropLengthMin(raindropLengthMin),
		raindropLengthMax(raindropLengthMax), animationSpeed(animationSpeed) {
	}
};

int randomInt(int min, int max);
std::vector<char> randomChars(int length);
std::string randomColor();
std::vector<Raindrop> generateRaindrops(const SimulationConfig& config);
void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops);
void moveRaindrops(std::vector<Raindrop>& raindrops, const SimulationConfig& config);
void simulateRainfall(const SimulationConfig& config);

#endif