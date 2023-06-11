#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotationComponent.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameCommands.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "PlayerComponent.h"
#include "ColliderComponent.h"

#include "LevelCreator.h"


using namespace dae;

void LoadBackground(dae::Scene& scene);
void RotationComponentScene(dae::Scene& scene);
void CommandsScene(dae::Scene& scene);
void LivesScene(dae::Scene& scene);
void MakePlayer1(dae::Scene& scene);

void load()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	scene;

	//LoadBackground(scene);
	//RotationComponentScene(scene);
	//CommandsScene(scene);
	LivesScene(scene);
	//MakePlayer1(scene);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

void RotationComponentScene(dae::Scene& scene)
{
	const float radius_pacman{ 20.f };
	const float rotSpeedPacman{ 3.f };

	auto pacman_go = std::make_shared<dae::GameObject>();

	auto transform = pacman_go->AddComponent<Transform>();
	transform->SetLocalPosition({ 350.f, 350.f, 0.f });

	auto pacRender = pacman_go->AddComponent<RenderComponent>();
	pacRender->SetTexture("pacman.png");

	pacman_go->AddComponent<RotationComponent>(radius_pacman, rotSpeedPacman);
	scene.Add(pacman_go);

	const float radius_ghost{ 20.f };
	const float rotSpeedGhost{ 9.f };

	auto ghost_go = std::make_shared<dae::GameObject>();

	transform = ghost_go->AddComponent<Transform>();

	auto ghost_renderer = ghost_go->AddComponent<RenderComponent>();
	ghost_renderer->SetTexture("ghost1.png");

	ghost_go->AddComponent<RotationComponent>(radius_ghost, rotSpeedGhost);

	ghost_go->SetParent(pacman_go.get(), false);
	scene.Add(ghost_go);
}

void LoadBackground(dae::Scene& scene)
{

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("background.tga");
	auto transform = go->AddComponent<dae::Transform>();
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("logo.tga");
	transform = go->AddComponent<dae::Transform>();
	transform->SetLocalPosition({ 216, 180,0 });
	scene.Add(go);

	// Prog 4 Text
	SDL_Color textColor{ 255,255,255 };

	auto to = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	transform = to->AddComponent<Transform>();
	transform->SetLocalPosition({ 80.f, 70.f, 0.f });

	// Make sure to add the render component before the text component!
	auto renderer = to->AddComponent<RenderComponent>();

	auto text_comp = to->AddComponent<TextComponent>("Programming 4 Assignment", font, textColor);
	text_comp->Init();

	scene.Add(to);

	textColor = { 0, 255, 0 };

	//// FPS counter
	auto fpsGo = std::make_shared<dae::GameObject>();
	renderer = fpsGo->AddComponent<RenderComponent>();

	transform = fpsGo->AddComponent<Transform>();
	transform->SetLocalPosition({ 0.f,0.f,0.f });

	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = fpsGo->AddComponent<TextComponent>("0 FPS", font2, textColor);
	text->Init();

	auto fpsComp = fpsGo->AddComponent<FPSComponent>();
	fpsComp->Init();

	scene.Add(fpsGo);

}

void CommandsScene(dae::Scene& scene)
{
	using namespace dae;

	// Movement directions
	glm::vec3 up = { 0.f,-1.f,0.f };
	glm::vec3 down = { 0.f,1.f,0.f };
	glm::vec3 right = { 1.f,0.f,0.f };
	glm::vec3 left = { -1.f,0.f,0.f };

	InputManager::GetInstance().AddPlayer();

	auto pacman_go = std::make_shared<GameObject>();
	auto transform = pacman_go->AddComponent<Transform>();
	transform->SetLocalPosition({ 350.f, 350.f, 0.f });
	auto pacRender = pacman_go->AddComponent<RenderComponent>();
	pacRender->SetTexture("pacman.png");

	float moveSpeed = 100.f;

	auto moveUp = std::make_shared<MoveCommandOld>(pacman_go.get(), up, moveSpeed);
	auto moveDown = std::make_shared<MoveCommandOld>(pacman_go.get(), down, moveSpeed);
	auto moveLeft = std::make_shared<MoveCommandOld>(pacman_go.get(), left, moveSpeed);
	auto moveRight = std::make_shared<MoveCommandOld>(pacman_go.get(), right, moveSpeed);

	// UP
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADUp, SDL_SCANCODE_W, moveUp, 0, InputManager::KeyState::Down);
	// DOWN
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADDown, SDL_SCANCODE_S, moveDown, 0, InputManager::KeyState::Down);
	// RIGHT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADRight, SDL_SCANCODE_D, moveRight, 0, InputManager::KeyState::Down);
	// LEFT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADLeft, SDL_SCANCODE_A, moveLeft, 0, InputManager::KeyState::Down);

	scene.Add(pacman_go);

	InputManager::GetInstance().AddPlayer();

	auto mspacman_go = std::make_shared<GameObject>();
	auto transform2 = mspacman_go->AddComponent<Transform>();
	transform2->SetLocalPosition({ 450.f, 350.f, 0.f });
	auto mspacRender = mspacman_go->AddComponent<RenderComponent>();
	mspacRender->SetTexture("mspacman.png");

	moveSpeed = 200.f;

	auto moveUp2 = std::make_shared<MoveCommandOld>(mspacman_go.get(), up, moveSpeed);
	auto moveDown2 = std::make_shared<MoveCommandOld>(mspacman_go.get(), down, moveSpeed);
	auto moveLeft2 = std::make_shared<MoveCommandOld>(mspacman_go.get(), left, moveSpeed);
	auto moveRight2 = std::make_shared<MoveCommandOld>(mspacman_go.get(), right, moveSpeed);

	// check if can set a keyboard or controller key to nullptr for optional!

	// UP
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADUp, SDL_SCANCODE_UP, moveUp2, 1, InputManager::KeyState::Down);
	// DOWN
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADDown, SDL_SCANCODE_DOWN, moveDown2, 1, InputManager::KeyState::Down);
	// RIGHT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADRight, SDL_SCANCODE_RIGHT, moveRight2, 1, InputManager::KeyState::Down);
	// LEFT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADLeft, SDL_SCANCODE_LEFT, moveLeft2, 1, InputManager::KeyState::Down);

	scene.Add(mspacman_go);

}

void LivesScene(dae::Scene& scene)
{
	using namespace dae;

	// Movement directions
	glm::vec3 up = { 0.f,-1.f,0.f };
	glm::vec3 down = { 0.f,1.f,0.f };
	glm::vec3 right = { 1.f,0.f,0.f };
	glm::vec3 left = { -1.f,0.f,0.f };

	SDL_Color textColor{ 255,255,255 };
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto livesFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	// LIVES
	auto livesdisplay = std::make_shared<GameObject>();
	auto transform = livesdisplay->AddComponent<Transform>();
	transform->SetLocalPosition({ 0.f, 15.f, 0.f });

	// Make sure to add the render component before the text component!
	auto renderer = livesdisplay->AddComponent<RenderComponent>();
	auto text_comp = livesdisplay->AddComponent<TextComponent>("Lives: ", livesFont, textColor);
	text_comp->Init();
	livesdisplay->AddComponent<LivesDisplayComponent>();
	scene.Add(livesdisplay);

	auto scoreDisplay = std::make_shared<GameObject>();
	transform = scoreDisplay->AddComponent<Transform>();
	transform->SetLocalPosition({ 150.f, 15.f, 0.f });

	renderer = scoreDisplay->AddComponent<RenderComponent>();
	text_comp = scoreDisplay->AddComponent<TextComponent>("Score: ", livesFont, textColor);
	text_comp->Init();
	scoreDisplay->AddComponent<ScoreDisplayComponent>();
	scene.Add(scoreDisplay);

	float playX{ 347.f }, playY{ 50.f };
	InputManager::GetInstance().AddPlayer();
	auto pacman_go = std::make_shared<GameObject>();
	transform = pacman_go->AddComponent<Transform>();
	transform->SetLocalPosition({ playX, playY, 0.f });
	auto pacRender = pacman_go->AddComponent<RenderComponent>();
	pacRender->SetTexture("pacman.png");
	auto playerComponent = pacman_go->AddComponent<PlayerComponent>(false, 0);
	auto playerCollider = pacman_go->AddComponent<ColliderComponent>("PLAYER");
	playerCollider->SetDimensions(playX, playY, 15.2f, 15.2f);

	playerComponent->AddObserver(livesdisplay->GetComponent<LivesDisplayComponent>());
	playerComponent->AddObserver(scoreDisplay->GetComponent<ScoreDisplayComponent>());
	playerComponent->Start();

	auto moveUp = std::make_shared<MoveCommand>(pacman_go.get(), Direction::UP);
	auto moveDown = std::make_shared<MoveCommand>(pacman_go.get(), Direction::DOWN);
	auto moveRight = std::make_shared<MoveCommand>(pacman_go.get(), Direction::RIGHT);
	auto moveLeft = std::make_shared<MoveCommand>(pacman_go.get(), Direction::LEFT);

	auto dieCommand = std::make_shared<DieCommand>(pacman_go.get());

	// UP
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADUp, SDL_SCANCODE_W, moveUp, 0, InputManager::KeyState::Down);
	// DOWN
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADDown, SDL_SCANCODE_S, moveDown, 0, InputManager::KeyState::Down);
	// RIGHT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADRight, SDL_SCANCODE_D, moveRight, 0, InputManager::KeyState::Down);
	// LEFT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADLeft, SDL_SCANCODE_A, moveLeft, 0, InputManager::KeyState::Down);

	// DIE
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::ButtonA, SDL_SCANCODE_E, dieCommand, 0, InputManager::KeyState::Down);

	scene.Add(pacman_go);

	LevelCreator::GetInstance().CreateLevel(L"../Data/level1.json", &scene);

}

void MakePlayer1(dae::Scene& scene)
{
	using namespace dae;

	// Movement directions
	glm::vec3 up = { 0.f,-1.f,0.f };
	glm::vec3 down = { 0.f,1.f,0.f };
	glm::vec3 right = { 1.f,0.f,0.f };
	glm::vec3 left = { -1.f,0.f,0.f };

	InputManager::GetInstance().AddPlayer();
	auto pacman_go = std::make_shared<GameObject>();
	auto transform = pacman_go->AddComponent<Transform>();
	transform->SetLocalPosition({ 350.f, 350.f, 0.f });
	auto pacRender = pacman_go->AddComponent<RenderComponent>();
	pacRender->SetTexture("pacman.png");
	auto playerComponent = pacman_go->AddComponent<PlayerComponent>(false, 0);

	playerComponent->Start();

	auto moveUp = std::make_shared<MoveCommand>(pacman_go.get(), Direction::UP);
	auto moveDown = std::make_shared<MoveCommand>(pacman_go.get(), Direction::DOWN);
	auto moveRight = std::make_shared<MoveCommand>(pacman_go.get(), Direction::RIGHT);
	auto moveLeft = std::make_shared<MoveCommand>(pacman_go.get(), Direction::LEFT);

	auto dieCommand = std::make_shared<DieCommand>(pacman_go.get());

	// UP
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADUp, SDL_SCANCODE_W, moveUp, 0, InputManager::KeyState::Down);
	// DOWN
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADDown, SDL_SCANCODE_S, moveDown, 0, InputManager::KeyState::Down);
	// RIGHT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADRight, SDL_SCANCODE_D, moveRight, 0, InputManager::KeyState::Down);
	// LEFT
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::DPADLeft, SDL_SCANCODE_A, moveLeft, 0, InputManager::KeyState::Down);

	// DIE
	InputManager::GetInstance().AddCommand(Xbox360Controller::Button::ButtonA, SDL_SCANCODE_E, dieCommand, 0, InputManager::KeyState::Down);

	scene.Add(pacman_go);

}