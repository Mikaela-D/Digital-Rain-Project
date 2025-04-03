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

When I started this project, I wanted to recreate the digital rain effect using modern C++. I viewed online resources to get inspiration for my project, such as [2], [3], [4], [19], and [22].  
I explored methods to store arrays of random characters in vectors, which allowed me to efficiently process and print them as single strings. 
Also, I used ANSI escape codes for colour and cursor control, which made the rainfall effect more visually appealing by making the rainfall colourful and hiding or showing the cursor. 

So, what my project does is it simulates the iconic falling code effect seen in movies like The Matrix. It randomly generates characters (letters and numbers) that fall from the top to the bottom of the screen, with each raindrop having different colours and lengths. The animation is customisable in terms of screen size, number of raindrops, and speed.

---

## Design and Test

For this project, I designed the following features:

1. Raindrop design.
2. Characters inside the raindrops will be randomly selected from uppercase and lowercase letters (A-Z, a-z) and numbers (0-9).
3. Each character inside a raindrop will have a randomly assigned colour.
4. Raindrops will fall continuously and disappear gradually when hitting the 'ground'.
5. The simulation will allow customisation of screen size, number of raindrops, raindrop length, and animation speed.
6. The screen will be updated in each iteration to display falling raindrops without flickering.
7. A function to test the simulation works.

Some general resources I used during the development are [9], [11], [12], [13] for generateRaindrops(), and [15]. I also used [16] for information about using classes and objects in C++.

### 1. Raindrop Design

Every raindrop in the simulation is represented as an object with specific properties (position, length, symbols, and colors). The function generateRaindrops() creates a collection of raindrops, each of them having random properties.  
How it works is: the function first determines the length of each raindrop by selecting a random value within a specified range (randomInt(minLength, maxLength)). Then it generates a sequence of random characters consisting of uppercase and lowercase letters (A-Z, a-z) and numbers (0-9). Also, every character inside the raindrop is assigned a random colour, making every raindrop different.  
The initial position of the raindrop is also randomly determined within the screen’s width and height (randomInt(0, screenWidth - 1) and randomInt(0, screenHeight - 1)), making sure the raindrop distribution is scattered across the display.

```cpp
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
```

### 2. Random Characters
To generate random characters, I reused a function called randomInt that  generates a random integer within a given range between a minimum and a maximum number.
I learned how to make this function using [7] and [17].

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
In this code, I use static_cast<int> to ensure that the size of the chars string is properly converted from std::string::size_type (which is an unsigned type) to int before using it as an index. This conversion is necessary because the randomInt function expects int values for its arguments, but chars.size() returns a value of type std::string::size_type, which could be an unsigned integer. I learned how to do this using [10]. 

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

### 3. Randomly Assigned Colour

The randomColor function selects a random colour from the COLORS array and assigns it to a character. I found the colour codes using [5] and [6].  
It works by generating a random index within the valid range of the COLORS array.  
Then, COLORS[...] retrieves the colour at the generated index and returns the selected colour as a string.

```cpp
std::string randomColor() {
	return COLORS[randomInt(0, static_cast<int>(std::size(COLORS)) - 1)];
}
```
### 4. Raindrops fall continuously and disappear gradually when hitting the 'ground'

I move the raindrops down by incrementing their y value using drop.y++. This means that with each function call, every raindrop's vertical position is increased, creating the falling effect.  
I use an if statement to check if the raindrop has gone beyond the bottom of the screen. The condition raindrop.getY() - raindrop.getLength() >= screenHeight makes sure that the entire length of the raindrop is off-screen before resetting its position.  
If the if statement is true, I reset the raindrop to the top and assign a new random x position to make it fall from a new location. The x-coordinate is randomised using randomInt(0, screenWidth - 1), making sure that each raindrop starts from a different horizontal position.  
I randomise the length of the raindrop, generate new random characters, and assign random colours to each character in the raindrop using the for loop. The length is determined using randomInt(minLength, maxLength), which adds variation in raindrop lengths. The characters are assigned using randomChars(raindrop.getLength()), making each raindrop have a unique set of characters. Also, a new vector of colours is created, and each character in the raindrop is assigned a random colour using randomColor().

```cpp
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
```

### 5. Customisation (Screen Size, Number of Raindrops, Raindrop Length, and Animation Speed)

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

### 6. Updating the Screen

The clearScreen function clears the screen so I can update it with the new positions and colors of the raindrops.
'screen' is a 2D array [20] that holds the characters representing the screen. It clears the screen by setting all characters to ' '. It uses std::fill [21] to quickly set all elements of each row to a blank space.
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
	for (const Raindrop& raindrop : raindrops) {
		for (int i = 0; i < raindrop.getLength(); ++i) {
			int y = raindrop.getY() - i;
			if (y >= 0 && y < screen.getScreenHeight()) {
				screen.drawSymbol(raindrop.getX(), y, raindrop.getSymbols()[i], raindrop.getColors()[i]);
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
### 7. Testing Function

I added a simple testing function testSimulateRainfall to test that the simulateRainfall function works correctly.  
In the testSimulateRainfall function, I call simulateRainfall with specific parameters that I set.  
I make the test function work by commenting out the simulateRainfall function in main.cpp and adding testSimulateRainfall instead.  
While developing, I used AI [8] for error detection and debugging.

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
main.cpp File  
I also included a basic try-catch to catch and print any errors. Referenced [14] for learning.
```cpp
int main() {
	try {
		//simulateRainfall(120, 25, 15, 10, 15, 50);
		testSimulateRainfall();
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
	return 0;
}
```

## Algorithm

To create the algorithm to simulate the digital rain, I decided I wanted to have random characters and random colours for each raindrop.  
Also, random lengths for each raindrop. I already explained how I achieved those effects in the Design and Test, so here I will explain the main algorithm part for the simulateRainfall function. 

The function begins by generating a list of raindrops with random properties (position, length, symbols, and colors) using the generateRaindrops function. These properties make sure that each raindrop is unique, adding variation to the digital rain effect. Then, a Screen object is created to represent the display area, with the specified width and height, which sets the boundaries for the animation. 
To improve the visual experience and remove distractions, the terminal cursor is hidden at the beginning of the animation using the escape sequence \033[?25l. In the main loop, the updateScreen function is called to update the screen with the current positions and symbols of the raindrops, and the screen is printed to display the updated raindrops. The moveRaindrops function moves the raindrops down the screen. When a raindrop moves off the bottom of the screen, it restarts at the top with new random properties, keeping the animation dynamic.  
To control the speed of the rain effect, the animation pauses for a short period using sleep_for(): [18] and the animationSpeed variable, which controls how fast each frame of the animation is displayed. After each frame, the cursor is moved back to the top-left corner of the terminal using the escape sequence \033[H, preventing the animation from stacking up. When the animation ends, the cursor is made visible again using the escape sequence \033[?25h.

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

The biggest challenges I faced during development were the raindrop movements and random selection for the characters, colours, and length.  
The main challenge with raindrop movement was making sure they fall smoothly from top to bottom and reset when they hit the bottom. I had to carefully update their position and redraw them at the new location while clearing the screen in between to keep the animation fluid.  
The challenge with randomising raindrop properties (characters, colours, and length) was making sure each raindrop was unique. I used a random number generator to assign different characters and colours to each raindrop.  
I also faced a challenge clearing the screen; if I simply used system("cls"), I saw a flickering on the screen that reduced the quality of the animation. I solved it by adding the clearScreen function.

The challenge I encountered when designing the raindrop movements was making raindrops move smoothly while resetting them correctly after hitting the bottom. Initially, some raindrops disappeared too soon or overlapped unexpectedly.

To fix it, I made sure each raindrop's y position increased (drop.y++) every frame and added a check to reset raindrops only when their full length had exited the screen.

```cpp
if (raindrop.getY() - raindrop.getLength() >= screenHeight) {
	raindrop.setY(0);
	raindrop.setX(randomInt(0, screenWidth - 1));
	raindrop.setLength(randomInt(minLength, maxLength));
	raindrop.setSymbols(randomChars(raindrop.getLength()));
```

---

## Modern C++ Insight and Reflection

In my digital rain project, modern C++ tools like std::vector and std::mt19937 played an important role in simplifying the implementation.  
I used std::vector to store and manage the properties of each raindrop, such as the characters and colours, making the data handling more organised and flexible.  
For adding variety and randomness, I used std::mt19937 to generate random values for each raindrop, making sure they appeared unique and dynamic.  
These C++ features made the coding process much easier and faster, allowing me to focus more on the main ideas of the project instead of getting caught up in complex data structures.

---

## References
These are the resources I used while working on the project:

[1] Wikipedia, "Matrix Rain Algorithms", [Online]. Available: <a href="https://en.wikipedia.org/wiki/Matrix_digital_rain" target="_blank">https://en.wikipedia.org/wiki/Matrix_digital_rain</a>  
[2] GitHub, "Matrix Digital Rain", [Online]. Available: <a href="https://github.com/Kevger/MatrixDigitalRain" target="_blank">https://github.com/Kevger/MatrixDigitalRain</a>  
[3] GitHub, "Digital Rain Project in C++", [Online]. Available: <a href="https://sarahmatu.github.io/DigiRainProject/demo/2024/03/11/DigiRainProject.html" target="_blank">https://sarahmatu.github.io/DigiRainProject/demo/2024/03/11/DigiRainProject.html</a>  
[4] GitHub, "Neo Matrix Digital Rain", [Online]. Available: <a href="https://github.com/st3w/neo" target="_blank">https://github.com/st3w/neo</a>  
[5] Stack Overflow, "List of ANSI color escape sequences", [Online]. Available: <a href="https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences" target="_blank">https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences</a>  
[6] Geeks for Geeks, "How to Print Colored Text to the Linux Terminal", [Online]. Available: <a href="https://www.geeksforgeeks.org/how-to-print-colored-text-to-the-linux-terminal/" target="_blank">https://www.geeksforgeeks.org/how-to-print-colored-text-to-the-linux-terminal/</a>  
[7] Geeks for Geeks, "How to Generate Random Number in Range in C++?", [Online]. Available: <a href="https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/" target="_blank">https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/</a>  
[8] ChatGPT. (GPT-4). Open AI. [Online]. Available: <a href="https://chatgpt.com/" target="_blank">https://chatgpt.com/</a>  
[9] Learn C++, "Learn C++", [Online]. Available: <a href="https://www.learncpp.com/" target="_blank">https://www.learncpp.com/</a>  
[10] Stack Overflow, "What's the best strategy to get rid of "warning C4267 possible loss of data"?", [Online]. Available: <a href="https://stackoverflow.com/questions/36834799/whats-the-best-strategy-to-get-rid-of-warning-c4267-possible-loss-of-data" target="_blank">https://stackoverflow.com/questions/36834799/whats-the-best-strategy-to-get-rid-of-warning-c4267-possible-loss-of-data</a>  
[11] DevDocs, "C++ documentation", [Online]. Available: <a href="https://devdocs.io/cpp/" target="_blank">https://devdocs.io/cpp/</a>  
[12] Cppreference, "C++ reference", [Online]. Available: <a href="https://en.cppreference.com/w/" target="_blank">https://en.cppreference.com/w/</a>  
[13] Geeks for Geeks, "Vector push_back() in C++ STL", [Online]. Available: <a href="https://www.geeksforgeeks.org/vector-push-back-cpp-stl/" target="_blank">https://www.geeksforgeeks.org/vector-push-back-cpp-stl/</a>  
[14] W3Schools, "C++ Exceptions", [Online]. Available: <a href="https://www.w3schools.com/cpp/cpp_exceptions.asp" target="_blank">https://www.w3schools.com/cpp/cpp_exceptions.asp</a>  
[15] W3Schools, "C++ Tutorial", [Online]. Available: <a href="https://www.w3schools.com/cpp/default.asp" target="_blank">https://www.w3schools.com/cpp/default.asp</a>  
[16] Medium, "C++ Classes and Objects", [Online]. Available: <a href="https://medium.com/@pawan2505/c-classes-and-objects-4c60de81aa2d" target="_blank">https://medium.com/@pawan2505/c-classes-and-objects-4c60de81aa2d</a>  
[17] Learn C++, "Generating random numbers using Mersenne Twister", [Online]. Available: <a href="https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/" target="_blank">https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/</a>  
[18] Geeks for Geeks, "Sleep Function in C++", [Online]. Available: <a href="https://www.geeksforgeeks.org/sleep-function-in-cpp/" target="_blank">https://www.geeksforgeeks.org/sleep-function-in-cpp/</a>  
[19] Geeks for Geeks, "Implementation of a Falling Matrix", [Online]. Available: <a href="https://www.geeksforgeeks.org/implementation-falling-matrix/" target="_blank">https://www.geeksforgeeks.org/implementation-falling-matrix/</a>  
[20] Geeks for Geeks, "2D Vector in C++", [Online]. Available: <a href="https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/" target="_blank">https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/</a>  
[21] Cppreference, "std::fill", [Online]. Available: <a href="https://en.cppreference.com/w/cpp/algorithm/fill" target="_blank">https://en.cppreference.com/w/cpp/algorithm/fill</a>  
[22] Stack Overflow, "Creating rain drops", [Online]. Available: <a href="https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences" target="_blank">https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences</a>
