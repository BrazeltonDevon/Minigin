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
#include "Scene.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	scene;


	// background game object
	auto background_go = std::make_shared<GameObject>();
	// transform component
	auto transform = new dae::TransformComponent(background_go.get());
	background_go->AddComponent(transform);
	// make render component
	auto back_render_comp = new dae::RenderComponent(background_go.get());
	back_render_comp->SetTexture("background.tga");
	background_go->AddComponent(back_render_comp);

	scene.Add(background_go);

	// logo
	auto logo_go = std::make_shared<GameObject>();
	// make render component
	auto logo_render_comp = new dae::RenderComponent(logo_go.get());
	transform = new dae::TransformComponent(logo_go.get());
	logo_go->AddComponent(transform);
	logo_render_comp->SetPosition(216.f, 180.f);
	logo_render_comp->SetTexture("logo.tga");
	logo_go->AddComponent(logo_render_comp);
	scene.Add(logo_go);

	// Prog 4 Text
	SDL_Color textColor{255,255,255};

	auto to = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	transform = new dae::TransformComponent(to.get());
	to->AddComponent(transform);
	auto text_comp = new dae::TextComponent(to.get(), "Programming 4 Assignment", font, textColor);
	auto renderer = new dae::RenderComponent(to.get());
	to->AddComponent(renderer);
	// set renderer in text component
	text_comp->Init();
	text_comp->SetPosition(80.f, 50.f);
	to->AddComponent(text_comp);
	scene.Add(to);

	// FPS counter
	auto go = std::make_shared<dae::GameObject>();
	auto fpsComp = new dae::FPSComponent(go.get());
	renderer = new dae::RenderComponent(go.get());
	go->AddComponent(renderer);
	transform = new dae::TransformComponent(go.get());
	go->AddComponent(transform);
	renderer->SetPosition(0.f, 0.f);
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = new TextComponent(go.get(), "0 FPS", font2, textColor);
	text->Init();
	go->AddComponent(text);
	go->AddComponent(fpsComp);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}