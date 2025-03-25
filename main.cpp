/*


			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz

main.cpp
*/

#include <iostream>
#include "DigitalRain.h"
#include "Test.h"

int main() {
	// Create a simulation configuration with specific parameters
	SimulationConfig config(120, 25, 10, 10, 15, 3, 5, 50);

	// Start the rainfall simulation
	simulateRainfall(config);

	//runAllTests();

	return 0;
}

