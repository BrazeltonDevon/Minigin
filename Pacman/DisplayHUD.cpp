#include "DisplayHUD.h"

#include "ResourceManager.h"
#include "AvatarComponent.h"
#include "LivesDisplayComponent.h"
#include "EnemyPlayerComponent.h"
#include "ScoreDisplayComponent.h"
#include "TextComponent.h"

using namespace dae;

GameObject* DisplayHUD::CreateHUD(Scene* pScene, AvatarComponent* avatarComp, EnemyPlayerComponent* maitaComp)
{
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 30) };

	// ScoreDisplay
	const auto pScore = pScene->CreateGameObject();
	pScore->AddComponent<RenderComponent>();
	pScore->AddComponent<TextComponent>()->SetFont(pFont);
	pScore->AddComponent<ScoreDisplayComponent>()->SetPlayer(avatarComp);

	// HealthDisplay
	const auto pHealth = pScene->CreateGameObject();
	pHealth->AddComponent<RenderComponent>();
	pHealth->AddComponent<TextComponent>()->SetFont(pFont);
	pHealth->AddComponent<LivesDisplayComponent>()->SetSubject(&avatarComp->m_HealthChange);


	if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
	{
		pHealth->GetTransform()->SetWorldPosition(1045, 610);
		pScore->GetTransform()->SetWorldPosition(1045, 670);
		pHealth->GetComponent<TextComponent>()->SetColor(50, 255, 50);
		pScore->GetComponent<TextComponent>()->SetColor(50, 255, 50);
	}
	else
	{
		pHealth->GetTransform()->SetWorldPosition(1045, 210);
		pScore->GetTransform()->SetWorldPosition(1045, 270);
		pHealth->GetComponent<TextComponent>()->SetColor(50, 50, 255);
		pScore->GetComponent<TextComponent>()->SetColor(50, 50, 255);
	}

	//Maita UI
	if (maitaComp)
	{
		pScore->MarkForDelete();

		// HealthDisplay
		const auto pMaitaHealth = pScene->CreateGameObject();
		pMaitaHealth->AddComponent<RenderComponent>();
		pMaitaHealth->AddComponent<TextComponent>()->SetFont(pFont);
		pMaitaHealth->AddComponent<LivesDisplayComponent>()->SetSubject(&maitaComp->m_HealthChange);
		pMaitaHealth->GetTransform()->SetWorldPosition(1045, 210);
	}

	return pScore;
}
