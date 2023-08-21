#include "LevelCreator.h"

#include <string>
#include <fstream>
#include <SDL_keycode.h>

#include "Avatar.h"
#include "AvatarComponent.h"
#include "Block.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "Maita.h"
#include "TextComponent.h"
#include "Platform.h"
#include "EnemyPlayerComponent.h"
#include "ResourceManager.h"
#include "SceneCommands.h"
#include "ZenChan.h"

using namespace dae;

void LevelCreator::LoadLevel(Scene* pScene, int number)
{
	//set player avatar positions
	for (auto& go : pScene->GetAllObjects())
	{
		const auto avatarComp = go->GetComponent<AvatarComponent>();
		const auto maitaComp = go->GetComponent<EnemyPlayerComponent>();
		if (avatarComp)
		{
			if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
			{

				go->GetTransform()->SetWorldPosition(300, 703);
				std::cout << "set player pos\n";
				std::cout << "player pos is " << go->GetTransform()->GetLocalPosition().x << " , " << go->GetTransform()->GetLocalPosition().y << std::endl;
			}
			else
				go->GetTransform()->SetWorldPosition(850, 703);
		}
		else if (maitaComp)
		{
			go->GetTransform()->SetWorldPosition(850, 703);
		}
	}

	// load level from file
	std::string line;
	std::string fileName{ "../Data/Level" };
	fileName += std::to_string(number);
	fileName += ".txt";
	std::ifstream myfile(fileName);

	int posX{};
	int posY{};

	constexpr int blockSize{ 32 };

	// offset so collision doesn't occur immediately upon spawning
	constexpr float offset{ 1.f };

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (char letter : line)
			{
				glm::vec2 spawnPos{ blockSize * posX, blockSize * posY };

				switch (letter)
				{
				case '1':
				{
					Block::CreateBlock(pScene, spawnPos, number);
					break;
				}
				case '2':
				{
					Platform::CreatePlatform(pScene, spawnPos, number);
					break;
				}
				case '3':
				{
					spawnPos.y += offset;
					Maita::CreateMaita(pScene, spawnPos);
					//std::cout << "created maita " << spawnPos.x << " , " << spawnPos.y << " \n";
					break;
				}
				case '4':
				{
					spawnPos.y += offset;
					ZenChan::CreateZenChan(pScene, spawnPos);
					//std::cout << "created zenchan at " << spawnPos.x << " , " << spawnPos.y << " \n";
					break;
				}
				default:
					break;
				}

				++posX;
			}
			++posY;
			posX = 0;
		}
		myfile.close();
	}

	// FPS COUNTER
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 36) };
	const auto pFPSCounter = pScene->CreateGameObject();
	pFPSCounter->AddComponent<RenderComponent>();
	pFPSCounter->AddComponent<FPSComponent>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

	//F1
	InputManager::GetInstance().AddKeyboardCommand(SDLK_F1, InputManager::InputType::OnDown, std::make_unique<SkipLevelCommand>());

}
