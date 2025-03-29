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

	Raindrop(int xPosition, int yPosition, int dropLength, const std::vector<char>& dropSymbols, const std::vector<std::string>& dropColors);
};

class Screen {
public:
	int screenWidth;
	int screenHeight;
	std::vector<std::vector<char>> screen;
	std::vector<std::vector<std::string>> colorScreen;

	Screen(int screenWidth, int screenHeight);

	void clearScreen();
	void drawSymbol(int x, int y, char symbol, const std::string& color);
	void print() const;
};

int randomInt(int min, int max);
std::vector<char> randomChars(int length);
std::string randomColor();
std::vector<Raindrop> generateRaindrops(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength);
void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops);
void moveRaindrops(std::vector<Raindrop>& raindrops, int screenWidth, int screenHeight, int minLength, int maxLength);
void simulateRainfall(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength, int animationSpeed);

#endif // DIGITALRAIN_H