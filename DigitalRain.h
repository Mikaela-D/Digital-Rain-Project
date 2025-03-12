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

#include <vector>
#include <string>
#include <stdexcept> // Include for exception handling

// Class to represent a raindrop
class Raindrop {
public:
    Raindrop(int x, int y, int length, const std::string& symbols, const std::vector<std::string>& colors)
        : x(x), y(y), length(length), symbols(symbols), colors(colors) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getLength() const { return length; }
    const std::string& getSymbols() const { return symbols; }
    const std::vector<std::string>& getColors() const { return colors; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setLength(int newLength) { length = newLength; }
    void setSymbols(const std::string& newSymbols) { symbols = newSymbols; }
    void setColors(const std::vector<std::string>& newColors) { colors = newColors; }

private:
    int x;
    int y;
    int length;
    std::string symbols;
    std::vector<std::string> colors; // Store colors for each character
};

// Class to hold simulation parameters
class SimulationConfig {
public:
    SimulationConfig(int width, int height, int numRaindrops, int raindropLengthMin, int raindropLengthMax,
                     int symbolLengthMin, int symbolLengthMax, int animationSpeed)
        : width(width), height(height), numRaindrops(numRaindrops), raindropLengthMin(raindropLengthMin),
          raindropLengthMax(raindropLengthMax), symbolLengthMin(symbolLengthMin), symbolLengthMax(symbolLengthMax),
          animationSpeed(animationSpeed) {}

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getNumRaindrops() const { return numRaindrops; }
    int getRaindropLengthMin() const { return raindropLengthMin; }
    int getRaindropLengthMax() const { return raindropLengthMax; }
    int getSymbolLengthMin() const { return symbolLengthMin; }
    int getSymbolLengthMax() const { return symbolLengthMax; }
    int getAnimationSpeed() const { return animationSpeed; }

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
void simulateRainfall(const SimulationConfig& config);

#endif
