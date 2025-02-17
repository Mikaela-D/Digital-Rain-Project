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

struct Raindrop {
    int x;
    int y;
    int length;
};

int randomInt(int min, int max);
void simulateRainfall(int width, int height, int numRaindrops);

#endif
