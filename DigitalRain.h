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

struct Raindrop {
    int x;
    int y;
    int length;
    std::string symbols;
    std::vector<std::string> colors; // Add a vector to store colors for each character
};

int randomInt(int min, int max);
std::string randomChars(int length);
void simulateRainfall(int width, int height, int numRaindrops);

#endif
