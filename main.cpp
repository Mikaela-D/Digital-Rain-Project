/*


              _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
    `:-._,------' ` _,`--` -: `_ , ` ,' :
       `---..__,,--'            ` -'. -'

Mikaela Diaz
*/

#include <iostream>
#include "DigitalRain.h"

int main() {
    SimulationConfig config = {
        120, // width
        25,  // height
        10,  // numRaindrops
        10,  // raindropLengthMin
        15,  // raindropLengthMax
        3,   // symbolLengthMin
        5,   // symbolLengthMax
        50   // animationSpeed (milliseconds)
    };

    simulateRainfall(config);

    return 0;
}
