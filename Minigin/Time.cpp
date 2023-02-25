#include "Time.h"

void dae::Time::Reset()
{
	std::chrono::steady_clock::time_point currTime{ std::chrono::steady_clock::now() };
	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = {};
	m_FpsTimer = {};
	m_FpsCount = {};
	m_IsStopped = false;
}

void dae::Time::Update()
{
	//
	if (m_IsStopped)
	{
		m_FPS = 0;
		m_ElapsedGameTime = 0.0f;

		//calc time game is running - paused time
		std::chrono::high_resolution_clock::duration baseTillNow{ m_CurrTime - m_BaseTime };
		std::chrono::high_resolution_clock::duration totalGameTime{ baseTillNow - m_PausedDuration };
		m_TotalGameTime = std::chrono::duration<float>(totalGameTime).count();

		return;
	}

	// Current time is updated to the current
	m_CurrTime = std::chrono::steady_clock::now();

	// Elapsed game time aka Delta time is equal to the current time - the previous frame's time
	m_ElapsedGameTime = std::chrono::duration<float>(m_CurrTime - m_PrevTime).count();

	// after calculating the delta time, previous frame time is updated to current time for next frame calculation
	m_PrevTime = m_CurrTime;

	// avoid negative time
	if (m_ElapsedGameTime < 0.0f)
		m_ElapsedGameTime = 0.0f;

	// avoid huge time gaps by forcing an elapsed time upper bound
	if (m_ForceElapsedUpperBound && m_ElapsedGameTime > m_ElapsedUpperBound)
	{
		m_ElapsedGameTime = m_ElapsedUpperBound;
	}

	//calculate the total time the clock has been running
	// by using the BASE TIME aka when the clock was first started upon creation
	// minus the current time
	// gives the total elapsed time
	
	// (even if the clock is stopped and reset this code should work)
	// (if you were to use a single float variable for elapsed time and the clock
	// were to be stopped, the value would not be accurate)
	std::chrono::high_resolution_clock::duration baseTillNow{ m_CurrTime - m_BaseTime };
	std::chrono::high_resolution_clock::duration totalGameTime{ baseTillNow - m_PausedDuration };
	m_TotalGameTime = std::chrono::duration<float>(totalGameTime).count();

	//FPS LOGIC
	m_FpsTimer += m_ElapsedGameTime;
	++m_FpsCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FpsCount / m_FpsCount;
		m_FpsCount = 0;
		//m_FpsTimer -= 1.0f;
	}
}

void dae::Time::Start()
{
	if (m_IsStopped)
	{
		std::chrono::steady_clock::time_point startTime{ std::chrono::steady_clock::now() };
		m_PausedDuration += (startTime - m_StopTime);

		m_PrevTime = startTime;
		m_StopTime = {};
		m_IsStopped = false;
	}
}

void dae::Time::Stop()
{
	if (!m_IsStopped)
	{
		std::chrono::steady_clock::time_point currTime{ std::chrono::steady_clock::now() };
		m_StopTime = currTime;
		m_IsStopped = true;
	}
}
