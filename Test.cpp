/*
			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz
*/

#include "DigitalRain.h"
#include "Test.h"

void testSimulateRainfall() {
	int screenWidth = 80;
	int screenHeight = 20;
	int numRaindrops = 5;
	int minLength = 5;
	int maxLength = 10;
	int animationSpeed = 10;

	simulateRainfall(screenWidth, screenHeight, numRaindrops, minLength, maxLength, animationSpeed);
}

