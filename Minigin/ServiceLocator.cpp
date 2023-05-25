#include "ServiceLocator.h"

std::unique_ptr<dae::NullSoundSystem> dae::ServiceLocator::m_NullSoundSysmService{};
std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_SoundSysmService{ std::move(m_NullSoundSysmService) };