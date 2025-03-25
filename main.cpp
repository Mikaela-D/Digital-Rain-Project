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
	SimulationConfig config(120, 25, 10, 10, 15, 3, 5, 50);

	simulateRainfall(config);

	//runAllTests();

	return 0;
}
