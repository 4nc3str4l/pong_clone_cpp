#pragma once

#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>
#include <optional>

namespace ls
{
	using Instant = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using Milliseconds = std::chrono::milliseconds;

	inline Instant getCurrentTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	inline const uint32_t INFINITE = 0;

	enum TaskStatus
	{
		ACTIVE,
		PAUSED,
		DELETED
	};

	struct Task
	{
		uint32_t id;
		std::function<void()> callback;
		TaskStatus status;
	};

	struct TimeoutTask
	{
		Task task;
		Instant timeout;
	};

	struct RepeatedTask
	{
		TimeoutTask task;
		Milliseconds rate;
		uint32_t repeatTimes;
		std::optional<std::function<void()>> onComplete;
	};

	struct RepeatedTaskUntil
	{
		TimeoutTask task;
		Milliseconds rate;
		std::optional<std::function<void()>> onComplete;
	};

	class Scheduler
	{
	public:
		static void Tick();
		static void AddOneShotTask(std::function<void()>&& callback, Milliseconds delay);
		static void AddRepeatedTask(std::function<void()>&& callback, Milliseconds rate, uint32_t repeatTimes = INFINITE, std::optional<std::function<void()>>&& onComplete = {});
		static void AddRepeatedTaskUntil(std::function<void()>&& callback, Milliseconds rate, Milliseconds until, std::optional<std::function<void()>>&& onComplete = {});

	private:
		inline static std::vector<TimeoutTask> m_OneShotTasks;
		inline static std::vector<RepeatedTask> m_RepeatedTasks;
		inline static std::vector<RepeatedTaskUntil> m_RepeatedTasksUntil;
		inline static uint32_t m_NextId = 0;
	};

	inline void Scheduler::Tick()
	{
		Instant currentTime = getCurrentTime();

		m_OneShotTasks.erase(std::remove_if(m_OneShotTasks.begin(), m_OneShotTasks.end(), [&](const TimeoutTask& t)
			{
				if (t.task.status == ACTIVE && t.timeout <= currentTime) {
					t.task.callback();
					return true;
				}
				return false; }),
			m_OneShotTasks.end());

		for (auto& rtask : m_RepeatedTasks)
		{
			if (rtask.task.task.status == ACTIVE && rtask.task.timeout <= currentTime)
			{
				rtask.task.task.callback();
				if (rtask.repeatTimes != INFINITE)
				{
					if (--rtask.repeatTimes == 0)
					{
						if (rtask.onComplete) {
							rtask.onComplete.value()();
						}
						rtask.task.task.status = DELETED;
						continue;
					}
				}
				rtask.task.timeout = currentTime + rtask.rate;
			}
		}
		m_RepeatedTasks.erase(std::remove_if(m_RepeatedTasks.begin(), m_RepeatedTasks.end(), [](const RepeatedTask& rtask)
			{
				return rtask.task.task.status == DELETED;
			}), m_RepeatedTasks.end());

		for (auto& rtask : m_RepeatedTasksUntil)
		{
			if (rtask.task.task.status == ACTIVE && rtask.task.timeout <= currentTime)
			{
				rtask.task.task.callback();
				rtask.task.timeout = currentTime + rtask.rate;

				if (rtask.task.timeout >= (currentTime + rtask.rate))
				{
					if (rtask.onComplete) {
						rtask.onComplete.value()();
					}
					rtask.task.task.status = DELETED;
				}
			}
		}
		m_RepeatedTasksUntil.erase(std::remove_if(m_RepeatedTasksUntil.begin(), m_RepeatedTasksUntil.end(), [](const RepeatedTaskUntil& rtask)
			{
				return rtask.task.task.status == DELETED;
			}),
			m_RepeatedTasksUntil.end());
	}
}
