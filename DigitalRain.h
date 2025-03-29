// DigitalRain.h

#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <random>

template <typename T>
class Raindrop {
public:
	int x, y, length;
	std::vector<T> symbols;
	std::vector<std::string> colors;

	Raindrop(int x, int y, int length, const std::vector<T>& symbols, const std::vector<std::string>& colors)
		: x(x), y(y), length(length), symbols(symbols), colors(colors) {
	}
};

template <typename T>
class Matrix {
public:
	int width, height;
	std::vector<std::vector<T>> screen;
	std::vector<std::vector<std::string>> colorScreen;

	Matrix(int width, int height)
		: width(width), height(height), screen(height, std::vector<T>(width, ' ')), colorScreen(height, std::vector<std::string>(width, "\033[0m")) {
	}

	void clear() {
		for (auto& row : screen) std::fill(row.begin(), row.end(), ' ');
		for (auto& row : colorScreen) std::fill(row.begin(), row.end(), "\033[0m");
	}

	void setCell(int x, int y, T symbol, const std::string& color) {
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
std::vector<Raindrop<char>> generateRaindrops(const SimulationConfig& config);
void updateScreen(Matrix<char>& matrix, const std::vector<Raindrop<char>>& raindrops);
void moveRaindrops(std::vector<Raindrop<char>>& raindrops, const SimulationConfig& config);
void simulateRainfall(const SimulationConfig& config);

#endif