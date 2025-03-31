/*
			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz
*/

#include "DigitalRain.h"
#include <thread>       // std::this_thread::sleep_for
#include <chrono>       // std::chrono::milliseconds
#include <algorithm>    // std::fill

constexpr const char* COLORS[] = {
	"\033[31m", // Red
	"\033[32m", // Green
	"\033[33m", // Yellow
	"\033[34m", // Blue
	"\033[35m", // Magenta
	"\033[36m", // Cyan
	"\033[37m"  // White
};

Raindrop::Raindrop(int xPosition, int yPosition, int dropLength, const std::vector<char>& dropSymbols, const std::vector<std::string>& dropColors)
	: x(xPosition), y(yPosition), length(dropLength), symbols(dropSymbols), colors(dropColors) {
}

int Raindrop::getX() const { return x; }
int Raindrop::getY() const { return y; }
int Raindrop::getLength() const { return length; }
const std::vector<char>& Raindrop::getSymbols() const { return symbols; }
const std::vector<std::string>& Raindrop::getColors() const { return colors; }
void Raindrop::setY(int newY) { y = newY; }
void Raindrop::setX(int newX) { x = newX; }
void Raindrop::setLength(int newLength) { length = newLength; }
void Raindrop::setSymbols(const std::vector<char>& newSymbols) { symbols = newSymbols; }
void Raindrop::setColors(const std::vector<std::string>& newColors) { colors = newColors; }

Screen::Screen(int screenWidth, int screenHeight)
	: screenWidth(screenWidth), screenHeight(screenHeight),
	screen(screenHeight, std::vector<char>(screenWidth, ' ')),
	colorScreen(screenHeight, std::vector<std::string>(screenWidth, "\033[0m")) {
}

int Screen::getScreenWidth() const { return screenWidth; }
int Screen::getScreenHeight() const { return screenHeight; }

void Screen::clearScreen() {
	for (std::vector<char>& row : screen) {
		std::fill(row.begin(), row.end(), ' ');
	}
	for (std::vector<std::string>& row : colorScreen) {
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
		c = chars[randomInt(0, static_cast<int>(chars.size()) - 1)];
	}
	return result;
}

std::string randomColor() {
	return COLORS[randomInt(0, static_cast<int>(std::size(COLORS)) - 1)];
}

// Main Functions
std::vector<Raindrop> generateRaindrops(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength) {
	std::vector<Raindrop> raindrops;
	for (int i = 0; i < numRaindrops; ++i) {
		int length = randomInt(minLength, maxLength);
		std::vector<char> symbols = randomChars(length);
		std::vector<std::string> colors(length);
		for (std::string& color : colors) {
			color = randomColor();
		}
		Raindrop raindrop(randomInt(0, screenWidth - 1), randomInt(0, screenHeight - 1), length, symbols, colors);
		raindrops.push_back(raindrop);
	}
	return raindrops;
}

void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops) {
	screen.clearScreen();
	for (const Raindrop& raindrop : raindrops) {
		for (int i = 0; i < raindrop.getLength(); ++i) {
			int y = raindrop.getY() - i;
			if (y >= 0 && y < screen.getScreenHeight()) {
				screen.drawSymbol(raindrop.getX(), y, raindrop.getSymbols()[i], raindrop.getColors()[i]);
			}
		}
	}
}

void moveRaindrops(std::vector<Raindrop>& raindrops, int screenWidth, int screenHeight, int minLength, int maxLength) {
	for (Raindrop& raindrop : raindrops) {
		raindrop.setY(raindrop.getY() + 1);
		if (raindrop.getY() - raindrop.getLength() >= screenHeight) {
			raindrop.setY(0);
			raindrop.setX(randomInt(0, screenWidth - 1));
			raindrop.setLength(randomInt(minLength, maxLength));
			raindrop.setSymbols(randomChars(raindrop.getLength()));
			std::vector<std::string> newColors(raindrop.getLength());
			for (std::string& color : newColors) {
				color = randomColor();
			}
			raindrop.setColors(newColors);
		}
	}
}

void simulateRainfall(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength, int animationSpeed) {
	std::vector<Raindrop> raindrops = generateRaindrops(screenWidth, screenHeight, numRaindrops, minLength, maxLength);
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