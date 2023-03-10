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
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotationComponent.h"
#include "Scene.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	scene;


	// background game object
	auto background_go = std::make_shared<GameObject>();
	// transform component
	auto transform = new dae::TransformComponent(background_go);
	background_go->AddComponent(transform);
	// make render component
	auto back_render_comp = new dae::RenderComponent(background_go);
	back_render_comp->SetTexture("background.tga");
	background_go->AddComponent(back_render_comp);

	scene.Add(background_go);

	// logo
	auto logo_go = std::make_shared<GameObject>();
	// make render component
	auto logo_render_comp = new dae::RenderComponent(logo_go);
	transform = new dae::TransformComponent(logo_go);
	logo_go->AddComponent(transform);
	logo_render_comp->SetPosition(216.f, 180.f);
	logo_render_comp->SetTexture("logo.tga");
	logo_go->AddComponent(logo_render_comp);
	scene.Add(logo_go);

	// Prog 4 Text
	SDL_Color textColor{255,255,255};

	auto to = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	transform = new dae::TransformComponent(to);
	to->AddComponent(transform);
	auto text_comp = new dae::TextComponent(to, "Programming 4 Assignment", font, textColor);
	auto renderer = new dae::RenderComponent(to);
	to->AddComponent(renderer);
	// set renderer in text component
	text_comp->Init();
	text_comp->SetPosition(80.f, 50.f);
	to->AddComponent(text_comp);
	scene.Add(to);

	// FPS counter
	auto go = std::make_shared<dae::GameObject>();
	auto fpsComp = new dae::FPSComponent(go);
	renderer = new dae::RenderComponent(go);
	go->AddComponent(renderer);
	transform = new dae::TransformComponent(go);
	go->AddComponent(transform);
	renderer->SetPosition(0.f, 0.f);
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = new TextComponent(go, "0 FPS", font2, textColor);
	text->Init();
	go->AddComponent(text);
	go->AddComponent(fpsComp);
	scene.Add(go);

	// WEEK 2
	const float radius_pacman{ 20.f };
	const float rotSpeedPacman{ 3.f };

	auto pacman_go = std::make_shared<dae::GameObject>();
	transform = new dae::TransformComponent(pacman_go);
	pacman_go->AddComponent(transform);

	auto pacRender = new dae::RenderComponent(pacman_go);
	pacRender->SetTexture("pacman.png");
	pacRender->SetPosition(350.f, 350.f);
	pacman_go->AddComponent(pacRender);
	auto pacRotComp = new dae::RotationComponent(pacman_go, radius_pacman, rotSpeedPacman);
	pacman_go->AddComponent(pacRotComp);
	scene.Add(pacman_go);


	const float radius_ghost{ 20.f };
	const float rotSpeedGhost{ 9.f };

	auto ghost_go = std::make_shared<dae::GameObject>();
	transform = new dae::TransformComponent(ghost_go);
	ghost_go->AddComponent(transform);
	auto ghost_renderer = new dae::RenderComponent(ghost_go);
	ghost_renderer->SetTexture("ghost1.png");
	ghost_go->AddComponent(ghost_renderer);
	auto ghost_rot_comp = new dae::RotationComponent(ghost_go, radius_ghost, rotSpeedGhost);
	ghost_go->AddComponent(ghost_rot_comp);
	ghost_go->SetParent(pacman_go.get(), false);
	scene.Add(ghost_go);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}