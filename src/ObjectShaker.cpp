#include "ObjectShaker.h"

void ObjectShaker::ShakeObject(sf::Transformable& object, Milliseconds duration)
{
	//float missingShaketime = 0.0f;
	//float shakeTime = 0.0f;
	//float scale = 1.0f;
	//sf::Transformable* objectPtr = &object;

	//ShakeTask* t = new ShakeTask{
	//	missingShaketime,
	//	shakeTime,
	//	scale,
	//	objectPtr
	//};

	//Scheduler::AddRepeatedTaskUntil([t]() {
	//	
	//	}, Milliseconds{ 15 }, 
	//	duration, 
	//	[t]() {
	//		delete t;
	//	}
	//);

	// TODO: On complete I need to delete the ShakeTask as it would be a memory leak.<
}