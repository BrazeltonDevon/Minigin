#include "MainMenuScene.h"

#include <SDL_keycode.h>

#include "FPSComponent.h"
#include "HighScoreLoader.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SceneCommands.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "ToggleSoundSysCommand.h"
#include "RenderComponent.h"

using namespace dae;

void MainMenuScene::Create()
{
	ServiceLocator::GetSoundSystem().ToggleMusic(false);

	auto& pSceneManager = SceneManager::GetInstance();
	auto* pGameScene = pSceneManager.GetCurrentScene();

	InputManager::GetInstance().RemoveAllInputs();
	InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	if (pGameScene)
	{
		pGameScene->RemoveAll();
		pGameScene->SetName("MainMenu");
	}
	else
	{
		pGameScene = pSceneManager.CreateScene("MainMenu");
	}
	pSceneManager.SetCurrentScene(pGameScene);


	//Add commands to start the game
	InputManager::GetInstance().AddKeyboardCommand('1', InputManager::InputType::OnDown, std::make_unique<StartSinglePlayerCommand>());
	InputManager::GetInstance().AddKeyboardCommand('2', InputManager::InputType::OnDown, std::make_unique<StartCoopCommand>());
	InputManager::GetInstance().AddKeyboardCommand('3', InputManager::InputType::OnDown, std::make_unique<StartVersusCommand>());

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 30) };

	// BubbleBobble logo
	const auto pBG = pGameScene->CreateGameObject();
	const auto pGameLogoTexture{ ResourceManager::GetInstance().LoadTexture("BubbleBobbleLogo.png") };
	pBG->AddComponent<RenderComponent>()->SetTexture(pGameLogoTexture);
	pBG->GetTransform()->SetWorldPosition(1280.f / 2 - pGameLogoTexture->GetSize().x / 2, 20);

	// DAE LOGO
	const auto pLogo = pGameScene->CreateGameObject();
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };
	pLogo->AddComponent<RenderComponent>()->SetTexture(pLogoTexture);
	pLogo->AddComponent<FPSComponent>();
	pLogo->GetTransform()->SetWorldPosition(1280.f - pLogoTexture->GetSize().x * 1.1f, 50);

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<RenderComponent>();
	pFPSCounter->AddComponent<FPSComponent>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);


	// SinglePlayer
	const auto pSinglePlayer = pGameScene->CreateGameObject();
	pSinglePlayer->AddComponent<RenderComponent>();
	pSinglePlayer->AddComponent<TextComponent>()->SetFont(pFont);
	pSinglePlayer->GetComponent<TextComponent>()->SetText("Singleplayer - Press 1");
	pSinglePlayer->GetComponent<TextComponent>()->SetColor(255, 255, 255);
	pSinglePlayer->GetComponent<TextComponent>()->Update();
	pSinglePlayer->GetTransform()->SetWorldPosition(pSinglePlayer->GetComponent<RenderComponent>()->GetTextureSize().x * 0.1f, 540.f);

	// Coop
	const auto pCoop = pGameScene->CreateGameObject();
	pCoop->AddComponent<RenderComponent>();
	pCoop->AddComponent<TextComponent>()->SetFont(pFont);
	pCoop->GetComponent<TextComponent>()->SetText("Co-op mode - Press 2");
	pCoop->GetComponent<TextComponent>()->SetColor(255, 255, 255);
	pCoop->GetComponent<TextComponent>()->Update();
	pCoop->GetTransform()->SetWorldPosition(pSinglePlayer->GetComponent<RenderComponent>()->GetTextureSize().x * 0.1f, 610.f);

	// Versus
	const auto pVersus = pGameScene->CreateGameObject();
	pVersus->AddComponent<RenderComponent>();
	pVersus->AddComponent<TextComponent>()->SetFont(pFont);
	pVersus->GetComponent<TextComponent>()->SetText("Versus mode - Press 3");
	pVersus->GetComponent<TextComponent>()->SetColor(255, 255, 255);
	pVersus->GetComponent<TextComponent>()->Update();
	pVersus->GetTransform()->SetWorldPosition(pSinglePlayer->GetComponent<RenderComponent>()->GetTextureSize().x * 0.1f, 680.f);

	// Highscores
	const auto pHighScore = pGameScene->CreateGameObject();
	pHighScore->AddComponent<RenderComponent>();
	pHighScore->AddComponent<TextComponent>()->SetFont(pFont);
	pHighScore->GetComponent<TextComponent>()->SetText("Highscores:");
	pHighScore->GetComponent<TextComponent>()->SetColor(255, 255, 255);
	pHighScore->GetComponent<TextComponent>()->Update();
	pHighScore->GetTransform()->SetWorldPosition(1280.f / 2.f - 100.f, 350);

	HighScoreLoader::LoadHighScores("HighScores.json");
	const auto highScores = HighScoreLoader::GetTopFive();
	for (unsigned int i{}; i < highScores.size(); ++i)
	{
		const auto pScore = pGameScene->CreateGameObject();
		pScore->AddComponent<RenderComponent>();
		pScore->AddComponent<TextComponent>()->SetFont(pFont);
		pScore->GetComponent<TextComponent>()->SetText(highScores[i].first + " - " + std::to_string(highScores[i].second));
		pScore->GetComponent<TextComponent>()->SetColor(255, 255, 255);
		pScore->GetComponent<TextComponent>()->Update();
		pScore->GetTransform()->SetWorldPosition(1280.f / 2.f - 100.f, 360.f + 30.f * (static_cast<float>(i) + 1.f));
	}
}
