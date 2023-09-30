#pragma once

#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>

namespace lostsocket {

    using Instant = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using Milliseconds = std::chrono::milliseconds;

    inline Instant getCurrentTime() {
        return std::chrono::high_resolution_clock::now();
    }

    inline const uint32_t INFINITE = 0;

    enum TaskStatus {
        ACTIVE,
        PAUSED,
        DELETED
    };

    struct Task {
        uint32_t id;
        std::function<void()> callback;
        TaskStatus status;
    };

    struct TimeoutTask {
        Task task;
        Instant timeout;
    };

    struct RepeatedTask {
        TimeoutTask task;
        Milliseconds rate;
        uint32_t repeatTimes;
    };

    class Scheduler {
    public:
        static void Tick();
        static void AddOneShotTask(uint32_t id, std::function<void()> callback, Milliseconds delay);
        static void AddRepeatedTask(uint32_t id, std::function<void()> callback, Milliseconds rate, uint32_t repeatTimes = INFINITE);
    private:
        inline static std::vector<TimeoutTask> m_OneShotTasks;
        inline static std::vector<RepeatedTask> m_RepeatedTasks;
    };

    inline void Scheduler::AddOneShotTask(uint32_t id, std::function<void()> callback, Milliseconds delay) {
        m_OneShotTasks.push_back({ {id, callback, ACTIVE}, getCurrentTime() + delay });
    }

    inline void Scheduler::AddRepeatedTask(uint32_t id, std::function<void()> callback, Milliseconds rate, uint32_t repeatTimes) {
        m_RepeatedTasks.push_back({ { {id, callback, ACTIVE}, getCurrentTime() + rate }, rate, repeatTimes });
    }

    inline void Scheduler::Tick() {
        Instant currentTime = getCurrentTime();

        // Handle one-shot tasks
        m_OneShotTasks.erase(std::remove_if(m_OneShotTasks.begin(), m_OneShotTasks.end(), [&](const TimeoutTask& t) {
            if (t.task.status == ACTIVE && t.timeout <= currentTime) {
                t.task.callback();
                return true;
            }
            return false;
            }), m_OneShotTasks.end());

        for (auto& rtask : m_RepeatedTasks) {
            if (rtask.task.task.status == ACTIVE && rtask.task.timeout <= currentTime) {
                rtask.task.task.callback();
                if (rtask.repeatTimes != INFINITE) {
                    if (--rtask.repeatTimes == 0) {
                        rtask.task.task.status = DELETED;
                        continue;
                    }
                }
                rtask.task.timeout = currentTime + rtask.rate;
            }
        }
        m_RepeatedTasks.erase(std::remove_if(m_RepeatedTasks.begin(), m_RepeatedTasks.end(), [](const RepeatedTask& rtask) {
            return rtask.task.task.status == DELETED;
            }), m_RepeatedTasks.end());
    }

}
