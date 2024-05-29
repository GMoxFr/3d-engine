#pragma once

#include <cmath>

#include "myVector3.hpp"

//////////////////////////
// CONSTANTS DEFINITION //
//////////////////////////

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr double EPSILON = 1e-10;

constexpr double DPI = 2 * M_PI;
constexpr double PI = M_PI;
constexpr double PI2 = M_PI / 2;
constexpr double PI4 = M_PI / 4;

constexpr double PRECISION = 0.003;

constexpr auto CRED = "\033[1;31m";
constexpr auto CGREEN = "\033[1;32m";
constexpr auto CYELLOW = "\033[1;33m";
constexpr auto CBLUE = "\033[1;34m";
constexpr auto CPURPLE = "\033[1;35m";
constexpr auto CCYAN = "\033[1;36m";
constexpr auto CWHITE = "\033[1;37m";
constexpr auto CBLACK = "\033[1;30m";
constexpr auto CRESET = "\033[0m";