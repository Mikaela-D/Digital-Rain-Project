﻿/*


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

// Class to represent a raindrop
class Raindrop {
public:
    Raindrop(int x, int y, int length, const std::string& symbols, const std::vector<std::string>& colors);

    int getX() const;
    int getY() const;
    int getLength() const;
    const std::string& getSymbols() const;
    const std::vector<std::string>& getColors() const;

    void setX(int newX);
    void setY(int newY);
    void setLength(int newLength);
    void setSymbols(const std::string& newSymbols);
    void setColors(const std::vector<std::string>& newColors);

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
void simulateRainfall(const SimulationConfig& config);

#endif
