/*
			  _,-'/-'/
  .      __,-; ,'( '/
   \.    `-.__`-._`:_,-._       _ , . ``
	`:-._,------' ` _,`--` -: `_ , ` ,' :
	   `---..__,,--'            ` -'. -'

Mikaela Diaz
DigitalRain.cpp
*/

#include "DigitalRain.h"
#include <thread>
#include <chrono>
#include <array>

constexpr std::array<const char*, 7> COLORS = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m" };

int randomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

std::string randomChars(int length) {
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string result(length, '\0');
	for (char& c : result) {
		c = chars[randomInt(0, static_cast<int>(chars.size()) - 1)]; // Proper type conversion
	}
	return result;
}

std::string randomColor() {
	return COLORS[randomInt(0, static_cast<int>(COLORS.size()) - 1)]; // Proper type conversion
}

std::vector<Raindrop> generateRaindrops(const SimulationConfig& config) {
	std::vector<Raindrop> raindrops;
	for (int i = 0; i < config.numRaindrops; ++i) {
		auto symbols = randomChars(randomInt(3, 5));
		std::vector<std::string> colors(symbols.size(), randomColor());
		raindrops.emplace_back(randomInt(0, config.width - 1), randomInt(0, config.height - 1),
			randomInt(config.raindropLengthMin, config.raindropLengthMax), symbols, colors);
	}
	return raindrops;
}

void updateScreen(Matrix& matrix, const std::vector<Raindrop>& raindrops) {
	matrix.clear();
	for (const auto& drop : raindrops) {
		for (int i = 0; i < drop.length; ++i) {
			int y = drop.y - i;
			if (y >= 0 && y < matrix.height) {
				int index = i % static_cast<int>(drop.symbols.length()); // Proper type conversion
				matrix.setCell(drop.x, y, drop.symbols[index], drop.colors[index]);
			}
		}
	}
}

void moveRaindrops(std::vector<Raindrop>& raindrops, const SimulationConfig& config) {
	for (auto& drop : raindrops) {
		drop.y++;
		if (drop.y - drop.length >= config.height) {
			drop.y = 0;
			drop.x = randomInt(0, config.width - 1);
			drop.length = randomInt(config.raindropLengthMin, config.raindropLengthMax);
			drop.symbols = randomChars(randomInt(3, 5));
			drop.colors = std::vector<std::string>(drop.symbols.size(), randomColor());
		}
	}
}

void simulateRainfall(const SimulationConfig& config) {
	auto raindrops = generateRaindrops(config);
	Matrix matrix(config.width, config.height);

	std::cout << "\033[?25l";
	while (true) {
		updateScreen(matrix, raindrops);
		matrix.print();
		moveRaindrops(raindrops, config);
		std::this_thread::sleep_for(std::chrono::milliseconds(config.animationSpeed));
		std::cout << "\033[H";
	}
	std::cout << "\033[?25h";
}