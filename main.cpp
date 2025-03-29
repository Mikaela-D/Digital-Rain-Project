// main.cpp

#include "DigitalRain.h"
#include "Test.h"

int main() {
	SimulationConfig config(120, 25, 10, 10, 15, 50);
	simulateRainfall(config);
	return 0;
}