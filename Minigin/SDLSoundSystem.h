#pragma once

#include "SoundSystem.h"
#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>
#include <map>
#include <SDL_mixer.h>
#include <unordered_map>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{

	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem() override;
		void Update() override;
		void PlaySound(int soundID) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;

		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;
		void AddSound(const std::string& filename) override;

	private:
		enum class SoundType {
			Sound,
			Music

		};

		struct Event {
			SoundType type;
			int soundId;
		};

		std::unordered_map<int, Mix_Chunk*> m_SoundList;
		std::vector<Mix_Chunk*> m_SoundsToPlay;
		std::mutex m_Mutex;
		std::condition_variable m_ConditionVariable;
		std::queue<Event> m_EventQueue;
		bool m_Quit = false;
		std::jthread m_Thread;
		int m_Volume;

		
	};
}



