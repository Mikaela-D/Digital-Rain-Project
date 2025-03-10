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

// Structure to represent a raindrop
struct Raindrop {
    int x;
    int y;
    int length;
    std::string symbols;
    std::vector<std::string> colors; // Store colors for each character
};

// Structure to hold simulation parameters
struct SimulationConfig {
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
