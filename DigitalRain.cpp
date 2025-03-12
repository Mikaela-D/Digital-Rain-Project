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

// Constants for color codes
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

const std::string COLORS[] = { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
const int NUM_COLORS = sizeof(COLORS) / sizeof(COLORS[0]);

// Generate random integer
int randomInt(int min, int max) {
    if (min > max) {
        throw std::invalid_argument("min should not be greater than max");
    }
    thread_local std::random_device rd;
    thread_local std::mt19937 gen(rd());
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
    return COLORS[randomInt(0, NUM_COLORS - 1)];
}

// Function to generate raindrops
std::vector<Raindrop> generateRaindrops(const SimulationConfig& config) {
    std::vector<Raindrop> raindrops;
    raindrops.reserve(config.getNumRaindrops());
    for (int i = 0; i < config.getNumRaindrops(); ++i) {
        std::string symbols = randomChars(randomInt(config.getSymbolLengthMin(), config.getSymbolLengthMax()));
        std::vector<std::string> colors;
        colors.reserve(symbols.length());
        for (char c : symbols) {
            colors.push_back(randomColor());
        }
        raindrops.emplace_back(randomInt(0, config.getWidth() - 1), randomInt(0, config.getHeight() - 1), randomInt(config.getRaindropLengthMin(), config.getRaindropLengthMax()), symbols, colors);
    }
    return raindrops;
}

// Function to update the screen and color data
void updateScreen(std::vector<std::vector<char>>& screen, std::vector<std::vector<std::string>>& colorScreen, const std::vector<Raindrop>& raindrops, int height) {
    std::for_each(raindrops.begin(), raindrops.end(), [&](const Raindrop& drop) {
        for (int i = 0; i < drop.getLength(); ++i) {
            int y = drop.getY() - i;
            if (y >= 0 && y < height) {
                int index = i % drop.getSymbols().length();
                screen[y][drop.getX()] = drop.getSymbols()[index];
                colorScreen[y][drop.getX()] = drop.getColors()[index];
            }
        }
    });
}

// Function to move raindrops downwards
void moveRaindrops(std::vector<Raindrop>& raindrops, const SimulationConfig& config) {
    std::for_each(raindrops.begin(), raindrops.end(), [&](Raindrop& drop) {
        drop.setY(drop.getY() + 1);
        if (drop.getY() - drop.getLength() >= config.getHeight()) {
            drop.setY(0);
            drop.setX(randomInt(0, config.getWidth() - 1));
            drop.setLength(randomInt(config.getRaindropLengthMin(), config.getRaindropLengthMax())); // Assign a new random length to the raindrop
            drop.setSymbols(randomChars(randomInt(config.getSymbolLengthMin(), config.getSymbolLengthMax()))); // New random symbols for each raindrop
            std::vector<std::string> newColors;
            for (char c : drop.getSymbols()) {
                newColors.push_back(randomColor());
            }
            drop.setColors(newColors);
        }
    });
}

// Function to simulate rainfall
void simulateRainfall(const SimulationConfig& config) {
    if (config.getWidth() <= 0 || config.getHeight() <= 0 || config.getNumRaindrops() <= 0) {
        throw std::invalid_argument("width, height, and numRaindrops should be greater than 0");
    }

    std::vector<Raindrop> raindrops = generateRaindrops(config);

    std::cout << "\033[?25l";  // Hide cursor 

    try {
        while (true) {
            std::vector<std::vector<char>> screen(config.getHeight(), std::vector<char>(config.getWidth(), ' '));
            std::vector<std::vector<std::string>> colorScreen(config.getHeight(), std::vector<std::string>(config.getWidth(), "\033[0m"));

            updateScreen(screen, colorScreen, raindrops, config.getHeight());

            for (int y = 0; y < config.getHeight(); ++y) {
                for (int x = 0; x < config.getWidth(); ++x) {
                    std::cout << colorScreen[y][x] << screen[y][x];
                }
                std::cout << "\033[0m" << std::endl; // Reset color at the end of each line
            }

            // Print the ground line
            std::cout << std::string(config.getWidth(), '_') << std::endl;

            moveRaindrops(raindrops, config);

            std::this_thread::sleep_for(std::chrono::milliseconds(config.getAnimationSpeed())); // Speed of the animation

            std::cout << "\033[H"; // Move the cursor back to the top-left corner
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\033[?25h";  // Show the cursor again when the simulation ends
}