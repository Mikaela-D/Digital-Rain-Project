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
        std::string symbols = randomChars(randomInt(3, 5));
        std::vector<std::string> colors;
        for (char c : symbols) {
            colors.push_back(randomColor());
        }
        raindrops.push_back({ randomInt(0, width - 1), randomInt(0, height - 1), randomInt(10, 15), symbols, colors });
    }

    std::cout << "\033[?25l";  // Hide cursor 

    while (true) {
        std::vector<std::vector<char>> screen(height, std::vector<char>(width, ' '));
        std::vector<std::vector<std::string>> colorScreen(height, std::vector<std::string>(width, "\033[0m"));

        for (auto& drop : raindrops) {
            for (int i = 0; i < drop.length; ++i) {
                int y = drop.y - i;
                if (y >= 0 && y < height) {
                    int index = i % drop.symbols.length();
                    screen[y][drop.x] = drop.symbols[index];
                    colorScreen[y][drop.x] = drop.colors[index];
                }
            }
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << colorScreen[y][x] << screen[y][x];
            }
            std::cout << "\033[0m" << std::endl; // Reset color at the end of each line
        }

        // Print the ground line
        std::cout << std::string(width, '_') << std::endl;

        // Move each raindrop downwards
        for (auto& drop : raindrops) {
            drop.y++;
            if (drop.y - drop.length >= height) {
                drop.y = 0;
                drop.x = randomInt(0, width - 1);
                drop.length = randomInt(10, 15); // Assign a new random length to the raindrop
                drop.symbols = randomChars(randomInt(3, 5)); // New random symbols for each raindrop
                drop.colors.clear();
                for (char c : drop.symbols) {
                    drop.colors.push_back(randomColor());
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Speed of the animation

        std::cout << "\033[H"; // Move the cursor back to the top-left corner
    }

    std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}