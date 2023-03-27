#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotationComponent.h"
#include "Transform.h"
#include "Scene.h"

using namespace dae;

void LoadBackground(dae::Scene& scene);
void RotationComponentScene(dae::Scene& scene);

void load()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	scene;

	LoadBackground(scene);
	//RotationComponentScene(scene);
}

int main(int, char*[]) {
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
	transform->SetLocalPosition({ 80.f, 50.f, 0.f });

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



