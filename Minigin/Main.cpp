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
	auto background_go = std::make_shared<GameObject>("background");
	// make render component
	auto back_render_comp = new dae::RenderComponent(background_go.get());
	back_render_comp->SetTexture("background.tga");
	background_go->AddComponent(back_render_comp);
	scene.Add(background_go);

	// logo
	auto logo_go = std::make_shared<GameObject>("logo");
	// make render component
	auto logo_render_comp = new dae::RenderComponent(logo_go.get());
	logo_render_comp->SetPosition(216.f, 180.f);
	logo_render_comp->SetTexture("logo.tga");
	logo_go->AddComponent(logo_render_comp);
	scene.Add(logo_go);

	// Prog 4 Text
	auto to = std::make_shared<dae::GameObject>("text");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text_comp = new dae::TextComponent(to.get(), "Programming 4 Assignment", font);
	text_comp->SetPosition(80.f, 50.f);
	to->AddComponent(text_comp);
	scene.Add(to);

	// FPS counter
	auto go = std::make_shared<dae::GameObject>("fps");
	auto fpsComp = new dae::FPSComponent(go.get());
	go->SetPosition(80.f, 20.f);
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = new TextComponent(go.get(), "0 FPS", font2);
	go->AddComponent(text);
	go->AddComponent(fpsComp);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}