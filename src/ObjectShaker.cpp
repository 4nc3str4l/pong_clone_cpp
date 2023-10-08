#include "ObjectShaker.h"
#include "Time.h"

void ObjectShaker::ShakeObject(sf::Transformable& object, float duration,
	float shakeScale)
{

	ShakeTask* task = new ShakeTask{
		Time::GetTimeSinceStart(),
		Time::GetTimeSinceStart() + duration,
		1.0f,
		&object,
		shakeScale
	};

	//Scheduler::AddRepeatedTaskUntil([task]() {
	//	float missing = task->endShakeTime - Time::GetTimeSinceStart();
	//	float t = missing / (task->endShakeTime - task->startShakeTime);
	//	if (missing > 0) 
	//	{
	//		if (t > 0.5f)
	//		{
	//			task->scale = t;
	//		}
	//		else
	//		{
	//			task->scale = 1.1f - t;
	//		}
	//		task->scale *= task->shakeScale;
	//	}
	//	}, Milliseconds{ 15 },
	//	Milliseconds{ static_cast<long long>(1000 * duration) },
	//	[task]() {
	//		task->object->setScale(1.0f, 1.0f);
	//		delete task;
	//	}
	//);

}