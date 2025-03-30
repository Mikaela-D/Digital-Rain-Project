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

1. Random Characters
```cpp
#include <iostream>
#include "DigitalRain.h"

int main() {
    return 0;
}
```

---

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
