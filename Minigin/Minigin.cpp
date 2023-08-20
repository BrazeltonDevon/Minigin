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

//**************************************
// DEFINE FIXED UPDATE USE
// IF NEEDED FOR PHYSICS &|| NETWORKING
//**************************************

#define USE_FIXED_UPDATE

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
	//load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = GTime::GetInstance();

	bool doContinue = true;

#ifdef USE_FIXED_UPDATE
	float lag = 0.0f;
#endif //USE_FIXED_UPDATE

	while (doContinue)
	{
		time.Update();

		const auto currentTime = std::chrono::high_resolution_clock::now();
		doContinue = input.ProcessInput();

#ifdef USE_FIXED_UPDATE
		lag += time.GetDeltaTime();

		while (lag >= Minigin::MsPerFrame)
		{
			sceneManager.FixedUpdate();
			lag -= Minigin::MsPerFrame;
		}
#endif //USE_FIXED_UPDATE

		sceneManager.Update();
		renderer.Render();

		const auto sleepTime = currentTime + std::chrono::milliseconds(Minigin::MsPerFrame) - std::chrono::high_resolution_clock::now();
		this_thread::sleep_for(sleepTime);
	}
}
