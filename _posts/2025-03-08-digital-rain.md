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

## Algorithm
The rain effect is implemented using **randomised characters** and **falling movement simulation**.

```cpp
#include <iostream>
#include "DigitalRain.h"

int main() {
    return 0;
}
```

---

## Problem Solving
Some challenges I faced during development:

- Efficiently rendering characters in the terminal.
- Generating random sequences that resemble falling rain.
- Balancing performance while maintaining smooth animation.

---

## Modern C++ Insight and Reflection
This project explores various modern C++ techniques:

- Random number generation using `std::random_device` and `std::mt19937`.
- Threading & performance optimisations using `std::this_thread::sleep_for`.
- Using ANSI escape codes for coloured terminal output.

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

---
