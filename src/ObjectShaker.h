
#pragma once

#include "Scheduler.h"
#include <SFML/Graphics.hpp>

using namespace ls;

struct ShakeTask 
{
	float startShakeTime;
	float endShakeTime;
	float scale = 1.0f;
	sf::Transformable* object;
	float shakeScale;
};

class ObjectShaker
{
public:
	static void ShakeObject(sf::Transformable& object,
		float duration, float shakeScale);
};