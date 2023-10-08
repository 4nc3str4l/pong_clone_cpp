#pragma once
#include <SFML/System/Time.hpp>

class Time {
private:
    inline static sf::Clock m_Clock;
    inline static sf::Clock m_TimeSinceStartClock;
    inline static float m_DeltaTime = 0;
    inline static float m_ScaledDeltaTime = 0;
    inline static float m_TimeScale = 1;
    inline static float m_TimeSinceStart = 0;

public:
    inline static float GetDeltaTime() { return m_ScaledDeltaTime; }
    inline static float GetTimeScale() { return m_TimeScale; }
    inline static void SetTimeScale(float scale) { 
        m_TimeScale = scale; 
        m_ScaledDeltaTime = m_DeltaTime * m_TimeScale;
    }
    static void Update() { 
        m_DeltaTime = m_Clock.restart().asSeconds();
        m_ScaledDeltaTime = m_DeltaTime * m_TimeScale;
        m_TimeSinceStart = m_TimeSinceStartClock.getElapsedTime().asSeconds();
    }
    static float GetTimeSinceStart() { return m_TimeSinceStart; }
};
