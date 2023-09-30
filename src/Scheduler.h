#pragma once

#include <vector>
#include <functional>

struct Task 
{
    uint32_t id;
    std::function<void()> callback;
};

class Scheduler
{
public:
    void Tick();
private:
    std::vector<Task> tasks {100};
}