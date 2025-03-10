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
#include <stdexcept> // Include for exception handling
#include <algorithm> // Include for std::for_each

// Generate random integer
int randomInt(int min, int max) {
    if (min > max) {
        throw std::invalid_argument("min should not be greater than max");
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Generate a string of random characters
std::string randomChars(int length) {
    if (length <= 0) {
        throw std::invalid_argument("length should be greater than 0");
    }
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%^&*()[]{}|<>";
    std::string result;
    result.reserve(length);
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

// Function to generate raindrops
std::vector<Raindrop> generateRaindrops(const SimulationConfig& config) {
    std::vector<Raindrop> raindrops;
    raindrops.reserve(config.numRaindrops);
    for (int i = 0; i < config.numRaindrops; ++i) {
        std::string symbols = randomChars(randomInt(config.symbolLengthMin, config.symbolLengthMax));
        std::vector<std::string> colors;
        colors.reserve(symbols.length());
        for (char c : symbols) {
            colors.push_back(randomColor());
        }
        raindrops.push_back({ randomInt(0, config.width - 1), randomInt(0, config.height - 1), randomInt(config.raindropLengthMin, config.raindropLengthMax), symbols, colors });
    }
    return raindrops;
}

// Function to update the screen and color data
void updateScreen(std::vector<std::vector<char>>& screen, std::vector<std::vector<std::string>>& colorScreen, const std::vector<Raindrop>& raindrops, int height) {
    std::for_each(raindrops.begin(), raindrops.end(), [&](const Raindrop& drop) {
        for (int i = 0; i < drop.length; ++i) {
            int y = drop.y - i;
            if (y >= 0 && y < height) {
                int index = i % drop.symbols.length();
                screen[y][drop.x] = drop.symbols[index];
                colorScreen[y][drop.x] = drop.colors[index];
            }
        }
    });
}

// Function to move raindrops downwards
void moveRaindrops(std::vector<Raindrop>& raindrops, const SimulationConfig& config) {
    std::for_each(raindrops.begin(), raindrops.end(), [&](Raindrop& drop) {
        drop.y++;
        if (drop.y - drop.length >= config.height) {
            drop.y = 0;
            drop.x = randomInt(0, config.width - 1);
            drop.length = randomInt(config.raindropLengthMin, config.raindropLengthMax); // Assign a new random length to the raindrop
            drop.symbols = randomChars(randomInt(config.symbolLengthMin, config.symbolLengthMax)); // New random symbols for each raindrop
            drop.colors.clear();
            for (char c : drop.symbols) {
                drop.colors.push_back(randomColor());
            }
        }
    });
}

// Function to simulate rainfall
void simulateRainfall(const SimulationConfig& config) {
    if (config.width <= 0 || config.height <= 0 || config.numRaindrops <= 0) {
        throw std::invalid_argument("width, height, and numRaindrops should be greater than 0");
    }

    std::vector<Raindrop> raindrops = generateRaindrops(config);

    std::cout << "\033[?25l";  // Hide cursor 

    while (true) {
        std::vector<std::vector<char>> screen(config.height, std::vector<char>(config.width, ' '));
        std::vector<std::vector<std::string>> colorScreen(config.height, std::vector<std::string>(config.width, "\033[0m"));

        updateScreen(screen, colorScreen, raindrops, config.height);

        for (int y = 0; y < config.height; ++y) {
            for (int x = 0; x < config.width; ++x) {
                std::cout << colorScreen[y][x] << screen[y][x];
            }
            std::cout << "\033[0m" << std::endl; // Reset color at the end of each line
        }

        // Print the ground line
        std::cout << std::string(config.width, '_') << std::endl;

        moveRaindrops(raindrops, config);

        std::this_thread::sleep_for(std::chrono::milliseconds(config.animationSpeed)); // Speed of the animation

        std::cout << "\033[H"; // Move the cursor back to the top-left corner
    }

    std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}