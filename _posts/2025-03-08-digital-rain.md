---
layout: post
title: Digital Rain Project
tags: cpp coding project
categories: demo
---

For my **C++ Programming Module**, I developed a **Digital Rain** project using **modern C++**.

<img src="https://raw.githubusercontent.com/Mikaela-D/Digital-Rain-Project/github-pages/assets/DigitalRain.gif" width="400" height="auto">

## Introduction

People refer to cascading computer code as Digital Rain, and that is what appeared on the Matrix movie screens. Digital Rain has been used in numerous computer and video games and films since it was introduced and popularised by the now world-renowned "The Matrix" movie produced by Simon Whiteley and his wife. Digital Rain is basically a cascade of dropping lines of randomly combined characters simulating rain.

When I accepted this assignment, I did some extensive study of how to recreate this effect using C++. I studied whether one could store arrays of random characters in vectors and then process them and print them as single strings. Not only was it space and time optimised, but it made the rain effect generation extremely efficient. I also studied the Windows Console API so that I can manipulate the console window to create better visuals.

This blog chronicles my experience, from **testing and design** to **algorithm creation** and **problem-solving**.

---

## Design and Testing
The project follows **Object-Oriented Design**, using **modular code** with reusable components.

### Key Features:
**Customisable rain properties (speed, density, colour, symbols)**  
**Efficient use of the C++ Standard Library**  
**Multi-threaded rendering for smooth animation**  

---

## Algorithm Development
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

## Modern C++
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
