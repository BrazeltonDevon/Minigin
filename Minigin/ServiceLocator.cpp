#include "ServiceLocator.h"

#include "SDLSoundSystem.h"
#include "SoundSystem.h"

std::unique_ptr<dae::NullSoundSystem> dae::ServiceLocator::m_NullSoundSysmService{};
std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_SoundSysmService{ std::move(m_NullSoundSysmService) };

void dae::ServiceLocator::InitDefault()
{
	m_SoundSysmService = std::make_unique<SDLSoundSystem>();
}
