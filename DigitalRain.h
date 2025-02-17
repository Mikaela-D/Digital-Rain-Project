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
};

int randomInt(int min, int max);
std::string randomChars(int length);
void simulateRainfall(int width, int height, int numRaindrops);

#endif
