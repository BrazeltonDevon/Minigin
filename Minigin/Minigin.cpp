#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <ctime>
#include <thread>
#include "GTime.h"
#include <chrono>
#include "EventQueue.h"

//**************************************
// DEFINE FIXED UPDATE USE
// IF NEEDED FOR PHYSICS &|| NETWORKING
//**************************************

//#define USE_FIXED_UPDATE

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		800,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	GTime::GetInstance().Start();
	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

using namespace std;
void dae::Minigin::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = GTime::GetInstance();
	auto& events = EventQueue::GetInstance();

	bool doContinue = true;
	constexpr float fixedTimeStep{ 0.005f }; // 0.005f
	constexpr float maxFrameTime{ 0.01f };
	float lag{};
	time.SetFixedTimeStep(fixedTimeStep);

	while (doContinue)
	{
		const auto frameStart{ std::chrono::high_resolution_clock::now() };

		time.Update();
		lag += time.GetDeltaTime();

		doContinue = input.ProcessInput();

		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate();
			sceneManager.CleanUpObjects();
			lag -= fixedTimeStep;
		}

		sceneManager.Update();
		events.NotifyListeners();
		sceneManager.CleanUpObjects();

		renderer.Render();

		const float frameTime{ std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - frameStart).count() };
		const float sleepTime{ maxFrameTime - frameTime };

		if (sleepTime > 0.f)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<LONGLONG>(sleepTime * 1000)));
		}
	}
}
