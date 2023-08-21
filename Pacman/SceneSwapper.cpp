#include "SceneSwapper.h"

#include "AvatarComponent.h"
#include "BubbleComponent.h"
#include "EnemyComponent.h"
#include "EventQueue.h"
#include "FoodComponent.h"
#include "LivesDisplayComponent.h"
#include "HighScoreScene.h"
#include "LevelCreator.h"
#include "MainMenuScene.h"
#include "SceneManager.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

using namespace dae;

void SceneSwapper::Init()
{
	MainMenuScene::Create();

	EventQueue::GetInstance().AddListener(this);
}


void SceneSwapper::SkipLevel()
{
	if (m_State == GameState::SinglePlayer ||
		m_State == GameState::Coop ||
		m_State == GameState::Versus)
	{
		auto& sceneManager = SceneManager::GetInstance();
		auto* pGameScene = sceneManager.GetCurrentScene();
		auto& name = pGameScene->GetName();

		auto& objVec = pGameScene->GetAllObjects();
		objVec.erase(std::remove_if(objVec.begin(), objVec.end(), [](std::unique_ptr<dae::GameObject>& go) {
			return (go->GetComponent<AvatarComponent>() == nullptr &&
				go->GetComponent<ScoreDisplayComponent>() == nullptr &&
				go->GetComponent<LivesDisplayComponent>() == nullptr);
			}), objVec.end());

		if (std::isdigit(name[0]))
		{
			int levelNr = std::stoi(name);

			if (levelNr < 3)
			{
				pGameScene->SetName(std::to_string(levelNr + 1));

				sceneManager.SetCurrentScene(pGameScene);

				LevelCreator::LoadLevel(pGameScene, levelNr + 1);
			}
			else
			{
				if (m_State == GameState::SinglePlayer || m_State == GameState::Coop)
				{
					HighScoreScene::Create();
					m_State = GameState::SetHighScore;
				}
				else
				{
					MainMenuScene::Create();
					m_State = GameState::Menu;
				}
			}
		}
	}
}

void SceneSwapper::OnEvent(const dae::Event& e)
{
	if (e.name == "PlayerDied")
	{
		dae::ServiceLocator::GetSoundSystem().ToggleMusic(false);

		if (m_State == GameState::SinglePlayer || m_State == GameState::Coop)
		{
			HighScoreScene::Create();
			m_State = GameState::SetHighScore;
		}
		else
		{
			MainMenuScene::Create();
			m_State = GameState::Menu;
		}
	}


	else if (e.name == "FoodCompDestroyed")
	{
		if (m_State == GameState::Coop || m_State == GameState::SinglePlayer)
		{
			bool canChangeLevel{ true };
			for (auto& object : dae::SceneManager::GetInstance().GetCurrentScene()->GetAllObjects())
			{
				if (object->HasComponent<EnemyComponent>())
				{
					canChangeLevel = false;
					break;
				}

				if (object->HasComponent<FoodComponent>())
				{
					canChangeLevel = false;
					break;
				}

				if (object->HasComponent<BubbleComponent>())
				{
					auto bubbleComponent = object->GetComponent<BubbleComponent>();
					if (bubbleComponent->GetState() == BubbleComponent::BubbleState::EnemyDying ||
						bubbleComponent->HasEnemyInside())
					{
						canChangeLevel = false;
						break;
					}
				}
			}

			if (canChangeLevel)
			{
				SkipLevel();
			}
		}
	}


}

