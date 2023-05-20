#pragma once
#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		virtual void Update() = 0;
		virtual void PlaySound(int soundID) = 0;
		virtual void PauseSound() = 0;
		virtual void UnpauseSound() = 0;
		virtual void IncreaseVolume() = 0;
		virtual void DecreaseVolume() = 0;
		virtual void AddSound(const std::string& filename) = 0;

		SoundSystem(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator= (const SoundSystem&) = delete;
		SoundSystem& operator= (const SoundSystem&&) = delete;
	};
}


