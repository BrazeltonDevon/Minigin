#include "HighScoreScene.h"

#include <SDL_keycode.h>

#include "FPSComponent.h"
#include "InputManager.h"
#include "SceneCommands.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "ToggleSoundSysCommand.h"
#include "TypingKeyboardComponent.h"
#include "RenderComponent.h"

using namespace dae;

void HighScoreScene::Create()
{
	ServiceLocator::GetSoundSystem().ToggleMusic(false);

	auto& pSceneManager = SceneManager::GetInstance();
	auto* pGameScene = pSceneManager.GetCurrentScene();

	InputManager::GetInstance().RemoveAllInputs();
	InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	int totalHighScore{};
	for (auto& go : pGameScene->GetAllObjects())
	{
		const auto scoreDisplay = go->GetComponent<ScoreDisplayComponent>();
		if (scoreDisplay)
		{
			totalHighScore += scoreDisplay->GetScore();
		}
	}

	if (pGameScene)
	{
		pGameScene->RemoveAll();
		pGameScene->SetName("HighScore");
	}
	else
	{
		pGameScene = pSceneManager.CreateScene("HighScore");
	}

	pSceneManager.SetCurrentScene(pGameScene);

	InputManager::GetInstance().AddKeyboardCommand(SDLK_RETURN, InputManager::InputType::OnDown, std::make_unique<LeaveHighScoreSceneCommand>(totalHighScore));

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 36) };

	// BubbleBobble logo
	const auto pBG = pGameScene->CreateGameObject();
	const auto pGameLogoTexture{ ResourceManager::GetInstance().LoadTexture("BubbleBobbleLogo.png") };
	pBG->AddComponent<RenderComponent>()->SetTexture(pGameLogoTexture);
	pBG->GetTransform()->SetWorldPosition(1280.f / 2 - pGameLogoTexture->GetSize().x / 2, 20);

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<RenderComponent>();
	pFPSCounter->AddComponent<FPSComponent>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

	// Highscore
	const auto pScore = pGameScene->CreateGameObject();
	pScore->AddComponent<RenderComponent>();
	pScore->AddComponent<TextComponent>()->SetFont(pFont);
	pScore->GetComponent<TextComponent>()->SetText("Total score: " + std::to_string(totalHighScore));
	pScore->GetComponent<TextComponent>()->Update();
	pScore->GetTransform()->SetWorldPosition(1280.f / 2 - pScore->GetComponent<RenderComponent>()->GetTextureSize().x / 2, 350);
	
	// Enter name
	const auto pName = pGameScene->CreateGameObject();
	pName->AddComponent<RenderComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);
	pName->GetComponent<TextComponent>()->SetText("Enter your name: ");
	pName->GetComponent<TextComponent>()->Update();
	pName->GetTransform()->SetWorldPosition(1280.f / 2 - pName->GetComponent<RenderComponent>()->GetTextureSize().x / 2, 400);

	// Input
	const auto pTyper = pGameScene->CreateGameObject();
	pTyper->AddComponent<TypingKeyboardComponent>();
	pTyper->AddComponent<RenderComponent>();
	pTyper->AddComponent<TextComponent>()->SetFont(pFont);
	pTyper->GetComponent<TextComponent>()->SetColor(250, 50, 50);
	pTyper->GetTransform()->SetWorldPosition(500, 500);

	const auto pCap = pGameScene->CreateGameObject();
	pCap->AddComponent<RenderComponent>();
	pCap->AddComponent<TextComponent>()->SetFont(pFont);
	pCap->GetComponent<TextComponent>()->SetText("(max name length is 10 characters)");
	pCap->GetComponent<TextComponent>()->SetColor(150, 150, 150);
	pCap->GetComponent<TextComponent>()->Update();
	pCap->GetTransform()->SetWorldPosition(1280.f / 2 - pCap->GetComponent<RenderComponent>()->GetTextureSize().x / 2, 700);
}
