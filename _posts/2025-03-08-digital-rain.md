---
layout: post
title: Digital Rain Project
tags: cpp coding project
categories: demo
---

For my C++ Programming Module, I developed a Digital Rain project using modern C++.

<img src="https://raw.githubusercontent.com/Mikaela-D/Digital-Rain-Project/github-pages/assets/DigitalRainAnimation.gif" width="600" height="auto">

## Introduction

Digital Rain is the visual effect of vertically falling computer code [1], which appeared in the Matrix movies. Digital Rain has been used in numerous computer and video games and films since it was introduced and popularised by the now world-renowned "The Matrix" movie produced by Simon Whiteley and his wife. Digital Rain is a cascade of dropping lines of randomly combined characters simulating rain. 

When I started this project, I wanted to recreate the digital rain effect using modern C++. I explored methods to store arrays of random characters in vectors, which allowed me to efficiently process and print them as single strings. 
Also, I used ANSI escape codes for colour and cursor control, which made the rainfall effect more visually appealing by making the rainfall colourful and hiding or showing the cursor. 

---

## Design and Test

For this project, I designed the following features:

1. Characters inside the raindrops will be randomly selected from uppercase and lowercase letters (A-Z, a-z) and numbers (0-9).
2. Each character inside a raindrop will have a randomly assigned colour.
3. Raindrops will fall continuously and disappear gradually when hitting the 'ground'.
4. The simulation will allow customisation of screen size, number of raindrops, raindrop length, and animation speed.
5. The screen will be updated in each iteration to display falling raindrops without flickering.
6. A function to test the simulation works.

### 1. Random Characters
To generate random characters, I reused a function called randomInt that  generates a random integer within a given range between a minimum and a maximum number.
I learned how to make this function using [7].

std::random_device rd: Creates a random seed based on the system’s state, such as the system clock, providing a true random value for seeding the generator.
std::mt19937 gen(rd()): Initialises a pseudo-random number generator (Mersenne Twister), seeded with rd, ensuring different random numbers each time the program runs.
std::uniform_int_distribution<> dist(min, max): Defines a uniform distribution that generates random integers between min and max, ensuring all values in the range have an equal chance of being selected.
dist(gen): Uses the generator gen and the distribution dist to produce and return a random integer within the specified range.

```cpp
int randomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
```
The randomChars function generates a sequence of random characters.
It defines a string 'chars' containing uppercase and lowercase letters (A-Z, a-z) and numbers (0-9).  
A vector 'result' stores the random characters.  
A loop assigns each character in the vector a random character 'chars' by calling the randomInt function to get a random index.
Then, after filling the vector, the function returns the vector with random characters.

```cpp
std::vector<char> randomChars(int length) {
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::vector<char> result(length);
	for (char& c : result) {
		c = chars[randomInt(0, static_cast<int>(chars.size()) - 1)];
	}
	return result;
}
```

### 2. Randomly Assigned Colour

The randomColor function selects a random colour from the COLORS array and assigns it to a character.  
It works by generating a random index within the valid range of the COLORS array.  
Then, COLORS[...] retrieves the colour at the generated index and returns the selected colour as a string.

```cpp
std::string randomColor() {
	return COLORS[randomInt(0, static_cast<int>(std::size(COLORS)) - 1)];
}
```
### 3. Raindrops fall continuously and disappear gradually when hitting the 'ground'

I move the raindrops down by incrementing their y value using drop.y++.  
I use an if statement to check if the raindrop has gone past the bottom of the screen.
If the if statement is true, I reset the raindrop to the top and assign a new random x position to make it fall from a new location.
I randomise the length of the raindrop, generate new random characters, and assign random colours to each character in the raindrop using the for loop.

```cpp
void moveRaindrops(std::vector<Raindrop>& raindrops, int screenWidth, int screenHeight, int minLength, int maxLength) {
	for (Raindrop& drop : raindrops) {
		drop.y++;
		if (drop.y - drop.length >= screenHeight) {
			drop.y = 0;
			drop.x = randomInt(0, screenWidth - 1);
			drop.length = randomInt(minLength, maxLength);
			drop.symbols = randomChars(drop.length);
			drop.colors.resize(drop.length);
			for (std::string& color : drop.colors) {
				color = randomColor();
			}
		}
	}
}
```

### 4. Customisation of screen size, number of raindrops, raindrop length, and animation speed

I allow passing these values to simulateRainfall in its declaration.

```cpp
void simulateRainfall(int screenWidth, int screenHeight, int numRaindrops, int minLength, int maxLength, int animationSpeed);
```

This setup creates a 120x25 screen, with 15 raindrops, each having a random length between 10 and 15 characters, and an animation speed of 50 milliseconds per frame.

```cpp
int main() {
	simulateRainfall(120, 25, 15, 10, 15, 50);
	return 0;
}
```

5. Updating the Screen

The clearScreen function clears the screen so I can update it with the new positions and colors of the raindrops.
'screen' is a 2D array that holds the characters representing the screen. It clears the screen by setting all characters to ' '.
'colorScreen' is a 2D array that holds the colour codes for each character in the screen. It clears the colorScreen by setting all colours to the reset colour "\033[0m".

```cpp
void Screen::clearScreen() {
	for (std::vector<char>& row : screen) {
		std::fill(row.begin(), row.end(), ' ');
	}
	for (std::vector<std::string>& row : colorScreen) {
		std::fill(row.begin(), row.end(), "\033[0m");
	}
}
```
After clearing the screen, I use the updateScreen function to update it with the new positions and colours of the raindrops.
The outer loop is used to access each raindrop, and the inner loop is used to handle each character within the raindrop.
The y position of each character within a raindrop is calculated by subtracting i from drop.y. This means that the raindrop's bottom will be higher (more negative y-coordinates), and the head will be lower.

```cpp
void updateScreen(Screen& screen, const std::vector<Raindrop>& raindrops) {
	screen.clearScreen();
	for (const Raindrop& drop : raindrops) {
		for (int i = 0; i < drop.length; ++i) {
			int y = drop.y - i;
			if (y >= 0 && y < screen.screenHeight) {
				screen.drawSymbol(drop.x, y, drop.symbols[i], drop.colors[i]);
			}
		}
	}
}
```

Lastly, I use the drawSymbol function to place the character and its colour on the screen.
The if statement checks if the given coordinates (x, y) are within the screen's bounds to avoid accessing out-of-bound elements.
If the position is valid, it updates the corresponding screen array with the symbol and the colorScreen array with the color.

```cpp
void Screen::drawSymbol(int x, int y, char symbol, const std::string& color) {
	if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
		screen[y][x] = symbol;
		colorScreen[y][x] = color;
	}
}
```
### Testing Function

I added a simple testing function testSimulateRainfall to test that the simulateRainfall function works correctly.  
In the testSimulateRainfall function, I call simulateRainfall with specific parameters that I set.  
I make the test function work by commenting out the simulateRainfall function in main.cpp and adding testSimulateRainfall instead.

Test.h File
```cpp
#ifndef TEST_H
#define TEST_H

void testSimulateRainfall();

#endif // TEST_H
```

Test.cpp File
```cpp
#include "DigitalRain.h"
#include "Test.h"

void testSimulateRainfall() {
	int screenWidth = 80;
	int screenHeight = 20;
	int numRaindrops = 5;
	int minLength = 5;
	int maxLength = 10;
	int animationSpeed = 10;

	simulateRainfall(screenWidth, screenHeight, numRaindrops, minLength, maxLength, animationSpeed);
}
```

## Algorithm

To create the algorithm to simulate the digital rain, I decided I wanted to have random characters and random colours for each raindrop. Also, random lengths for each raindrop. I already explained how I achieved those effects in the Design and Test, so here I will explain the main algorithm part for the simulateRainfall function. 

It first generates a list of raindrops with random properties (position, length, symbols, and colors) using generateRaindrops.  
Then, a Screen object is created to represent the display area with the specified width and height.  
I hide the terminal cursor to avoid visual distraction during the animation.  
In the while loop, the updateScreen function updates the screen with the current raindrop positions and symbols, and the screen is printed, showing the updated raindrops.  
The moveRaindrops function moves the raindrops down the screen. If they go off the bottom, they restart at the top with new random properties.  
The animation pauses for a short period (controlled using the animationSpeed variable) to control the speed of the rain effect.  
After printing, the cursor is moved back to the top-left corner to avoid the animation from stacking up.  
When the animation ends, the cursor is made visible again.

```cpp
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
```

---

## Problem Solving
Some challenges I faced during development:

The biggest challenges I faced during development were the raindrop movements and the random selection for the characters, colours, and length.  
The main challenge with raindrop movement was making sure they fall smoothly from top to bottom and reset when they hit the bottom. I had to carefully update their position and redraw them at the new location while clearing the screen in between to keep the animation fluid.  
The challenge with randomising raindrop properties (characters, colours, and length) was making sure each raindrop was unique. I used a random number generator to assign different characters and colours to each raindrop.

---

## Modern C++ Insight and Reflection

Modern C++ tools, like std::vector and std::mt19937, were essential for simplifying my project. I used std::vector to manage the raindrop properties like characters and colours. For randomness, I used std::mt19937 to generate random values, making sure that each raindrop was unique.  
These modern C++ features made the implementation smoother and more efficient than I expected.

---

## References
These are the resources I used while working on the project:

[1] Wikipedia, " Matrix Rain Algorithms", [Online]. Available: https://en.wikipedia.org/wiki/Matrix_digital_rain  
[2] GitHub, "Matrix Digital Rain", [Online]. Available: https://github.com/Kevger/MatrixDigitalRain  
[3] GitHub, "Digital Rain Project in C++", [Online]. Available: https://sarahmatu.github.io/DigiRainProject/demo/2024/03/11/DigiRainProject.html  
[4] GitHub, "Neo Matrix Digital Rain", [Online]. Available: https://github.com/st3w/neo  
[5] Stack Overflow, "List of ANSI color escape sequences", [Online]. Available: https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences  
[6] Geeks for Geeks, "How to Print Colored Text to the Linux Terminal", [Online]. Available: https://www.geeksforgeeks.org/how-to-print-colored-text-to-the-linux-terminal/  
[7] Geeks for Geeks, "How to Generate Random Number in Range in C++?", [Online]. Available: https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/  
[8] ChatGPT. (GPT-4). Open AI. [Online]. Available: https://chatgpt.com/
