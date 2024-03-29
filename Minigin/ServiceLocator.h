#pragma once
#include "SoundSystem.h"
#include "NullSoundSystem.h"
#include <memory>

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_SoundSysmService; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& system)
		{
			m_SoundSysmService = std::move(system);
			if (m_SoundSysmService == nullptr)
				m_SoundSysmService = std::move(m_NullSoundSysmService);
		}

		static void InitDefault();
	private:
		static std::unique_ptr<SoundSystem> m_SoundSysmService;
		static std::unique_ptr<NullSoundSystem> m_NullSoundSysmService;
	};
}
