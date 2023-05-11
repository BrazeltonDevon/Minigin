#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class GTime final : public Singleton<GTime>
	{
	public:
		GTime() = default;
		~GTime() override = default;

		GTime(const GTime& other) = delete;
		GTime(GTime&& other) noexcept = delete;
		GTime& operator=(const GTime& other) = delete;
		GTime& operator=(GTime&& other) noexcept = delete;

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

