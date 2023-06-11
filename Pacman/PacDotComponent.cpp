#include "PacDotComponent.h"
#include "LevelCreator.h"
#include "PlayerComponent.h"

dae::PacDotComponent::PacDotComponent(GameObject* owner)
	: Component{owner}
{
	m_pDotSubject = std::make_unique<Subject>();
}

void dae::PacDotComponent::AddPoints()
{
	auto player = LevelCreator::GetInstance().GetPlayer1();
	player->GetComponent<PlayerComponent>()->AddScore(m_PointAmnt);

	m_pDotSubject->Notify(Event::AddPoints, player);
}
