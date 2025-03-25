/*


			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz

main.cpp
*/

#include "DigitalRain.h"
#include "Test.h"
#include <iostream>        // cout, endl

int main() {
	// Create a simulation configuration with specific parameters
	SimulationConfig config(120, 25, 10, 10, 15, 3, 5, 50);

	// Start the rainfall simulation
	simulateRainfall(config);

	//runAllTests();

	return 0;
}

