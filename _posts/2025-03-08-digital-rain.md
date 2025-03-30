---
layout: post
title: Digital Rain Project
tags: cpp coding project
categories: demo
---

For my C++ Programming Module, I developed a Digital Rain project using modern C++.

<img src="https://raw.githubusercontent.com/Mikaela-D/Digital-Rain-Project/github-pages/assets/DigitalRainAnimation.gif" width="600" height="auto">

## Introduction

People refer to cascading computer code as Digital Rain, which appeared on the Matrix movie screens. Digital Rain has been used in numerous computer and video games and films since it was introduced and popularised by the now world-renowned "The Matrix" movie produced by Simon Whiteley and his wife. Digital Rain is a cascade of dropping lines of randomly combined characters simulating rain. 

When I started this project, I wanted to recreate the digital rain effect using modern C++. I explored methods to store arrays of random characters in vectors, which allowed me to efficiently process and print them as single strings. This approach optimises both space and time, significantly improving the efficiency of the rain effect generation.  
Also, I used ANSI escape codes for colour and cursor control, which made the rainfall effect more visually appealing by making the rainfall colourful and hiding or showing the cursor. 

---

## Design and Test

For this project, I designed the following features:

1. Each character inside a raindrop will have a randomly assigned color.
2. Characters inside the raindrops will be randomly selected from uppercase and lowercase letters (A-Z, a-z) and numbers (0-9).
3. Raindrops will fall continuously and disappear gradually when hitting the 'ground'.


### Key Features:
**Customisable rain properties (speed, density, colour, symbols)**  
**Efficient use of the C++ Standard Library**  
**Multi-threaded rendering for smooth animation**  

---

## Algorithm
The rain effect is implemented using **randomised characters** and **falling movement simulation**.

```cpp
#include <iostream>
#include "DigitalRain.h"

int main() {
    int width = 120;
    int height = 25;
    int numRaindrops = 10;

    simulateRainfall(width, height, numRaindrops);
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

- Online resource on Matrix Rain algorithms: https://en.wikipedia.org/wiki/Matrix_digital_rain
- Matrix Digital Rain code example: https://github.com/Kevger/MatrixDigitalRain
- Digital Rain Project blog: https://sarahmatu.github.io/DigiRainProject/demo/2024/03/11/DigiRainProject.html
- Neo Matrix Digital Rain code: https://github.com/st3w/neo
- ANSI colour escape sequences: https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
- How to print coloured text: https://www.geeksforgeeks.org/how-to-print-colored-text-to-the-linux-terminal/
- Random number generation: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus

---
