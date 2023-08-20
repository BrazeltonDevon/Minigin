#include "SceneCommands.h"

#include "HighScoreLoader.h"
#include "SceneManager.h"
#include "SceneSwapper.h"
#include "MainMenuScene.h"
#include "Scene.h"
#include "TypingKeyboardComponent.h"

#include <SDL_keycode.h>

#include "Avatar.h"
#include "DisplayHUD.h"
#include "InputManager.h"
#include "LevelCreator.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "AvatarComponent.h"
#include "ToggleSoundSysCommand.h"

#include "EnemyComponent.h"
#include "EnemyPlayer.h"


void LeaveHighScoreSceneCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetCurrentScene();

	//get name that was input
	std::string name{};
	for (auto& go : scene->GetAllObjects())
	{
		const auto typer = go->GetComponent<TypingKeyboardComponent>();
		if (typer)
			name = typer->GetInput();
	}

	//save highscore
	HighScoreLoader::AddHighScore(name, m_Score);

	//Load main menu
	MainMenuScene::Create();

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Menu;
}

void SkipLevelCommand::Execute()
{
	SceneSwapper::GetInstance().SkipLevel();
}


void StartCoopCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetCurrentScene();

	dae::InputManager::GetInstance().RemoveAllInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, dae::InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	scene->RemoveAll();
	LevelCreator::LoadLevel(scene, 1);
	scene->SetName("1");

	auto avatar1 = Avatar::CreateAvatar(scene, glm::vec2{ 100, 700 }, true, true);
	auto avatar2 = Avatar::CreateAvatar(scene, glm::vec2{ 850, 700 }, false, false);

	DisplayHUD::CreateHUD(scene, avatar1->GetComponent<AvatarComponent>());
	DisplayHUD::CreateHUD(scene, avatar2->GetComponent<AvatarComponent>());

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Coop;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 100, -1);
	dae::ServiceLocator::GetSoundSystem().ToggleMusic(true);
}

void StartSinglePlayerCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetCurrentScene();

	dae::InputManager::GetInstance().RemoveAllInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, dae::InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	scene->RemoveAll();
	LevelCreator::LoadLevel(scene, 1);
	scene->SetName("1");

	auto avatar = Avatar::CreateAvatar(sceneManager.GetCurrentScene(), glm::vec2{100, 700}, true, false);

	DisplayHUD::CreateHUD(scene, avatar->GetComponent<AvatarComponent>());


	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::SinglePlayer;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 100, -1);
	dae::ServiceLocator::GetSoundSystem().ToggleMusic(true);
}

void StartVersusCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetCurrentScene();

	dae::InputManager::GetInstance().RemoveAllInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, dae::InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	//load level
	scene->RemoveAll();
	LevelCreator::LoadLevel(scene, 1);
	scene->SetName("1");

	//remove all enemies, since we dont want other enemies in versus mode
	for (auto& go : scene->GetAllObjects())
	{
		if (go->GetComponent<EnemyComponent>())
			go->MarkForDelete();
	}

	auto avatar = Avatar::CreateAvatar(scene, glm::vec2{ 100, 700 }, true, true);
	auto maita = EnemyPlayer::CreateMaita(scene, glm::vec2{ 850, 700 });

	DisplayHUD::CreateHUD(scene, avatar->GetComponent<AvatarComponent>(), maita->GetComponent<EnemyPlayerComponent>());

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Versus;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 100, -1);
	dae::ServiceLocator::GetSoundSystem().ToggleMusic(true);
}