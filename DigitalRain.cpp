// DigitalRain.cpp

#include "DigitalRain.h"
#include <thread>
#include <chrono>

constexpr const char* COLORS[] = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m" };

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
	return COLORS[randomInt(0, sizeof(COLORS) / sizeof(COLORS[0]) - 1)];
}

std::vector<Raindrop<char>> generateRaindrops(const SimulationConfig& config) {
	std::vector<Raindrop<char>> raindrops;
	raindrops.reserve(config.numRaindrops);
	for (int i = 0; i < config.numRaindrops; ++i) {
		int length = randomInt(config.raindropLengthMin, config.raindropLengthMax);
		auto symbols = randomChars(length);
		std::vector<std::string> colors(length);
		for (auto& color : colors) {
			color = randomColor();
		}
		raindrops.emplace_back(randomInt(0, config.width - 1), randomInt(0, config.height - 1), length, symbols, colors);
	}
	return raindrops;
}

void updateScreen(Matrix<char>& matrix, const std::vector<Raindrop<char>>& raindrops) {
	matrix.clear();
	for (const auto& drop : raindrops) {
		for (int i = 0; i < drop.length; ++i) {
			int y = drop.y - i;
			if (y >= 0 && y < matrix.height && i < static_cast<int>(drop.symbols.size()) && i < static_cast<int>(drop.colors.size())) {
				matrix.setCell(drop.x, y, drop.symbols[i], drop.colors[i]);
			}
		}
	}
}

void moveRaindrops(std::vector<Raindrop<char>>& raindrops, const SimulationConfig& config) {
	for (auto& drop : raindrops) {
		drop.y++;
		if (drop.y - drop.length >= config.height) {
			drop.y = 0;
			drop.x = randomInt(0, config.width - 1);
			drop.length = randomInt(config.raindropLengthMin, config.raindropLengthMax);
			drop.symbols = randomChars(drop.length);
			drop.colors.resize(drop.length);
			for (auto& color : drop.colors) {
				color = randomColor();
			}
		}
	}
}

void simulateRainfall(const SimulationConfig& config) {
	auto raindrops = generateRaindrops(config);
	Matrix<char> matrix(config.width, config.height);

	std::cout << "\033[?25l";  // Hide cursor
	while (true) {
		updateScreen(matrix, raindrops);
		matrix.print();
		moveRaindrops(raindrops, config);
		std::this_thread::sleep_for(std::chrono::milliseconds(config.animationSpeed));
		std::cout << "\033[H";  // Move cursor to home position
	}
	std::cout << "\033[?25h";  // Show cursor
}