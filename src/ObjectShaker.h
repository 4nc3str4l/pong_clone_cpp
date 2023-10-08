
#pragma once

#include "Scheduler.h"
#include <SFML/Graphics.hpp>

using namespace ls;

struct ShakeTask 
{
	float missingShakeTime;	
	float shakeTime;
	float scale = 1.0f;
	sf::Transformable* object;
};

class ObjectShaker
{
public:
	static void ShakeObject(sf::Transformable& object,
		Milliseconds duration);
};