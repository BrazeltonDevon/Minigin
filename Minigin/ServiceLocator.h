#pragma once
#include "SoundSystem.h"
#include "NullSoundSystem.h"
#include <memory>

namespace dae
{
	class ServiceLocator final
	{
	public:
		static std::unique_ptr<SoundSystem>& GetSoundSystem() { return m_SoundSysmService; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& system)
		{
			m_SoundSysmService = std::move(system);
			if (m_SoundSysmService == nullptr)
				m_SoundSysmService = std::move(m_NullSoundSysmService);
		}
	private:
		static std::unique_ptr<SoundSystem> m_SoundSysmService;
		static std::unique_ptr<NullSoundSystem> m_NullSoundSysmService;
	};
}
