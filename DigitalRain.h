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

#include <vector>
#include <string>
#include <memory>

// Template class to represent a raindrop
template <typename SymbolType, typename ColorType>
class Raindrop {
public:
	Raindrop(int x, int y, int length, const SymbolType& symbols, const std::vector<ColorType>& colors)
		: x(x), y(y), length(length), symbols(symbols), colors(colors) {
	}

	int getX() const { return x; }
	int getY() const { return y; }
	int getLength() const { return length; }
	const SymbolType& getSymbols() const { return symbols; }
	const std::vector<ColorType>& getColors() const { return colors; }

	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	void setLength(int newLength) { length = newLength; }
	void setSymbols(const SymbolType& newSymbols) { symbols = newSymbols; }
	void setColors(const std::vector<ColorType>& newColors) { colors = newColors; }

private:
	int x;
	int y;
	int length;
	SymbolType symbols;
	std::vector<ColorType> colors; // Store colors for each character
};

// Class to hold simulation parameters
class SimulationConfig {
public:
	SimulationConfig(int width, int height, int numRaindrops, int raindropLengthMin, int raindropLengthMax,
		int symbolLengthMin, int symbolLengthMax, int animationSpeed);

	int getWidth() const;
	int getHeight() const;
	int getNumRaindrops() const;
	int getRaindropLengthMin() const;
	int getRaindropLengthMax() const;
	int getSymbolLengthMin() const;
	int getSymbolLengthMax() const;
	int getAnimationSpeed() const;

private:
	int width;
	int height;
	int numRaindrops;
	int raindropLengthMin;
	int raindropLengthMax;
	int symbolLengthMin;
	int symbolLengthMax;
	int animationSpeed;
};

// Function declarations
int randomInt(int min, int max);
std::string randomChars(int length);
std::string randomColor();
std::vector<std::unique_ptr<Raindrop<std::string, std::string>>> generateRaindrops(const SimulationConfig& config); // Updated declaration
void updateScreen(std::vector<std::vector<char>>& screen, std::vector<std::vector<std::string>>& colorScreen, const std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops, int height); // Updated declaration
void moveRaindrops(std::vector<std::unique_ptr<Raindrop<std::string, std::string>>>& raindrops, const SimulationConfig& config); // Updated declaration
void simulateRainfall(const SimulationConfig& config);

#endif