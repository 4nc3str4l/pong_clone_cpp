#pragma once

#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline std::mt19937 mt;
inline std::uniform_real_distribution<float> dis(0.0, 1.0);


float randomFloat(float min, float max) {
    return min + dis(mt) * (max - min);
}


sf::Vector2f randomDirection2D() {
    float angle = randomFloat(0.0f, 2.0f * M_PI);
    return {std::cos(angle), std::sin(angle)};
}