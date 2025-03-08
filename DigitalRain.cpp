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
#include <vector>
#include <string>

// Generate random integer
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

std::string randomChars(int length) {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%^&*()[]{}|<>";
    std::string result = "";
    for (int i = 0; i < length; ++i) {
        result += chars[randomInt(0, chars.length() - 1)];
    }
    return result;
}

// Function to generate a random color code
std::string randomColor() {
    const std::string colors[] = {
        "\033[31m", // Red
        "\033[32m", // Green
        "\033[33m", // Yellow
        "\033[34m", // Blue
        "\033[35m", // Magenta
        "\033[36m", // Cyan
        "\033[37m"  // White
    };
    return colors[randomInt(0, 6)];
}

void simulateRainfall(int width, int height, int numRaindrops) {
    std::vector<Raindrop> raindrops;
    for (int i = 0; i < numRaindrops; ++i) {
        raindrops.push_back({ randomInt(0, width - 1), randomInt(0, height - 1), randomInt(10, 15), randomChars(randomInt(3, 5)) });
    }

    std::cout << "\033[?25l";  // Hide cursor 

    while (true) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                bool printedRaindrop = false;
                for (const auto& drop : raindrops) {
                    if (x == drop.x && y >= drop.y - drop.length + 1 && y <= drop.y) {
                        std::cout << randomColor() << drop.symbols[(y - drop.y + drop.length - 1) % drop.symbols.length()];  // Print character with random color
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
                drop.length = randomInt(10, 15); // Assign a new random length to the raindrop
                drop.symbols = randomChars(randomInt(3, 5)); // New random symbols for each raindrop
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Speed of the animation

        std::cout << "\033[H"; // Move the cursor back to the top-left corner
    }

    std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}