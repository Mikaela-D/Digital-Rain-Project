/*
			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz
*/

#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include <iostream> // std::cout, std::endl
#include <vector>   // std::vector
#include <string>   // std::string
#include <random>   // std::random_device, std::mt19937, std::uniform_int_distribution

class Raindrop {
public:
	Raindrop(int xPosition, int yPosition, int dropLength, const std::vector<char>& dropSymbols, const std::vector<std::string>& dropColors);

	int getX() const;
	int getY() const;
	int getLength() const;
	const std::vector<char>& getSymbols() const;
	const std::vector<std::string>& getColors() const;
	void setY(int newY);
	void setX(int newX);
	void setLength(int newLength);
	void setSymbols(const std::vector<char>& newSymbols);
	void setColors(const std::vector<std::string>& newColors);

private:
	int x;
	int y;
	int length;
	std::vector<char> symbols;
	std::vector<std::string> colors;
};

class Screen {
public:
	Screen(int screenWidth, int screenHeight);

	void clearScreen();
	void drawSymbol(int x, int y, char symbol, const std::string& color);
	void print() const;

	int getScreenWidth() const;
	int getScreenHeight() const;

private:
	int screenWidth;
	int screenHeight;
	std::vector<std::vector<char>> screen;
	std::vector<std::vector<std::string>> colorScreen;
};

int randomInt(int min, int max);
std::vector<char> randomChars(int length);
std::string randomColor();
std::vector<Raindrop> generateRaindrops(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength);
void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops);
void moveRaindrops(std::vector<Raindrop>& raindrops, int screenWidth, int screenHeight, int minLength, int maxLength);
void simulateRainfall(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength, int animationSpeed);

#endif // DIGITALRAIN_H