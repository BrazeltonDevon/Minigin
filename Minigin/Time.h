#pragma once
#include <chrono>

#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		Time() = default;
		~Time() override = default;

		Time(const Time& other) = delete;
		Time(Time&& other) noexcept = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) noexcept = delete;

		// resets the clock
		void Reset();
		// updates the time
		void Update();

		// gets the elapsed time aka delta time
		float GetDeltaTime() const { return  m_ElapsedGameTime; }
		// gets the total elapsed time since the clock has started
		float GetTotal() const { return m_TotalGameTime; }
		// get the frames per second
		int GetFPS() const { return m_FPS; }
		// 
		void ForceElapsedUpperbound(bool force, float upperBound = 0.03f) { m_ForceElapsedUpperBound = force; m_ElapsedUpperBound = upperBound; }
		bool IsRunning() const { return !m_IsStopped; }

		void Start();
		void Stop();
	protected:
		float m_TotalGameTime{};
		float m_ElapsedGameTime{};
		bool m_ForceElapsedUpperBound{};
		float m_ElapsedUpperBound{ 0.03f };

		std::chrono::high_resolution_clock::time_point m_BaseTime{};
		std::chrono::high_resolution_clock::time_point m_StopTime{};
		std::chrono::high_resolution_clock::time_point m_PrevTime{};
		std::chrono::high_resolution_clock::time_point m_CurrTime{};
		std::chrono::high_resolution_clock::duration m_PausedDuration{};

		bool m_IsStopped{ true };

		int m_FPS{};
		float m_FpsTimer{};
		int m_FpsCount{};
	};
}

