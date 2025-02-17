/*


              _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
    `:-._,------' ` _,`--` -: `_ , ` ,' :
       `---..__,,--'            ` -'. -'

Mikaela Diaz
*/

#include "DigitalRain.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <random>

// Generate random integer
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void simulateRainfall(int width, int height, int numRaindrops) {
    std::vector<Raindrop> raindrops;
    for (int i = 0; i < numRaindrops; ++i) {
        raindrops.push_back({ randomInt(0, width - 1), randomInt(0, height - 1), randomInt(10, 15) });
    }

    std::cout << "\033[?25l";

    while (true) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                bool printedRaindrop = false;
                for (const auto& drop : raindrops) {
                    if (x == drop.x && y >= drop.y - drop.length + 1 && y <= drop.y) {
                        std::cout << "*";
                        printedRaindrop = true; // Mark that a raindrop is printed here
                        break;
                    }
                }
                if (!printedRaindrop) {
                    std::cout << " "; // Print a space
                }
            }
            std::cout << std::endl; // Move to the next line
        }
        // Move each raindrop downwards
        for (auto& drop : raindrops) {
            drop.y++;
            if (drop.y >= height) {
                drop.y = 0;
                drop.x = randomInt(0, width - 1);
                drop.length = randomInt(10, 15);  // Assign a new random length to the raindrop
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "\033[H"; // Move the cursor back to the top-left corner
    }

    std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}