// DigitalRain.cpp

#include "DigitalRain.h"
#include <thread>
#include <chrono>

constexpr const char* COLORS[] = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m" };

// Class Definitions
Raindrop::Raindrop(int xPosition, int yPosition, int dropLength, const std::vector<char>& dropSymbols, const std::vector<std::string>& dropColors)
	: x(xPosition), y(yPosition), length(dropLength), symbols(dropSymbols), colors(dropColors) {
}

Screen::Screen(int screenWidth, int screenHeight)
	: screenWidth(screenWidth), screenHeight(screenHeight),
	screen(screenHeight, std::vector<char>(screenWidth, ' ')),
	colorScreen(screenHeight, std::vector<std::string>(screenWidth, "\033[0m")) {
}

void Screen::clearScreen() {
	for (auto& row : screen) {
		std::fill(row.begin(), row.end(), ' ');
	}
	for (auto& row : colorScreen) {
		std::fill(row.begin(), row.end(), "\033[0m");
	}
}

void Screen::drawSymbol(int x, int y, char symbol, const std::string& color) {
	if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
		screen[y][x] = symbol;
		colorScreen[y][x] = color;
	}
}

void Screen::print() const {
	for (int y = 0; y < screenHeight; ++y) {
		for (int x = 0; x < screenWidth; ++x) {
			std::cout << colorScreen[y][x] << screen[y][x];
		}
		std::cout << "\033[0m" << std::endl;
	}
	std::cout << std::string(screenWidth, '_') << std::endl;
}

// Utility Functions
int randomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

std::vector<char> randomChars(int length) {
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::vector<char> result(length);
	for (char& c : result) {
		c = chars[randomInt(0, static_cast<int>(chars.size()) - 1)]; // Fixed warning C4267
	}
	return result;
}

std::string randomColor() {
	return COLORS[randomInt(0, static_cast<int>(std::size(COLORS)) - 1)]; // Fixed warning C4267
}

// Main Functions
std::vector<Raindrop> generateRaindrops(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength) {
	std::vector<Raindrop> raindrops;
	raindrops.reserve(numRaindrops);
	for (int i = 0; i < numRaindrops; ++i) {
		int length = randomInt(minLength, maxLength);
		auto symbols = randomChars(length);
		std::vector<std::string> colors(length);
		for (auto& color : colors) {
			color = randomColor();
		}
		raindrops.emplace_back(randomInt(0, screenWidth - 1), randomInt(0, screenHeight - 1), length, symbols, colors);
	}
	return raindrops;
}

void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops) {
	screen.clearScreen();
	for (const auto& drop : raindrops) {
		for (int i = 0; i < drop.length; ++i) {
			int y = drop.y - i;
			if (y >= 0 && y < screen.screenHeight) {
				screen.drawSymbol(drop.x, y, drop.symbols[i], drop.colors[i]);
			}
		}
	}
}

void moveRaindrops(std::vector<Raindrop>& raindrops, int screenWidth, int screenHeight, int minLength, int maxLength) {
	for (auto& drop : raindrops) {
		drop.y++;
		if (drop.y - drop.length >= screenHeight) {
			drop.y = 0;
			drop.x = randomInt(0, screenWidth - 1);
			drop.length = randomInt(minLength, maxLength);
			drop.symbols = randomChars(drop.length);
			drop.colors.resize(drop.length);
			for (auto& color : drop.colors) {
				color = randomColor();
			}
		}
	}
}

void simulateRainfall(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength, int animationSpeed) {
	auto raindrops = generateRaindrops(screenWidth, screenHeight, numRaindrops, minLength, maxLength);
	Screen screen(screenWidth, screenHeight);

	std::cout << "\033[?25l";  // Hide cursor
	while (true) {
		updateScreen(screen, raindrops);
		screen.print();
		moveRaindrops(raindrops, screenWidth, screenHeight, minLength, maxLength);
		std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
		std::cout << "\033[H";  // Move cursor to home position
	}
	std::cout << "\033[?25h";  // Show cursor
}