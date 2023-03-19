#include <stdexcept>
#include "Renderer.h"
#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl2.h>
#include <imgui_plot.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	Transform* transform{};
	int ID{};

	~GameObject3DAlt()
	{
		delete transform;
	}

};


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}


void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

}

void dae::Renderer::GetDataEx1(int steps)
{
	int* obj = new int[m_Array_Size] {};

	m_TimesEx1.clear();


	for (int stepSize = 1; stepSize <= (1024 * steps); stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < m_Array_Size; i += stepSize)
		{
			obj[i] *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		m_TimesEx1.push_back(static_cast<float>(elapsedTime));
	}

	m_DataSizeEx1 = static_cast<int>(m_TimesEx1.size());

	delete[] obj;
}

void dae::Renderer::GetDataEx2(int steps)
{
	GameObject3D* obj = new GameObject3D[m_Array_Size]{};

	m_TimesEx2.clear();

	for (int stepSize = 1; stepSize <= (1024 * steps); stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < m_Array_Size; i += stepSize)
		{
			obj[i].ID *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		m_TimesEx2.push_back(static_cast<float>(elapsedTime));
	}

	m_DataSizeEx2 = static_cast<int>(m_TimesEx2.size());

	delete[] obj;
}

void dae::Renderer::GetDataEx2Alt(int steps)
{
	GameObject3DAlt* obj = new GameObject3DAlt[m_Array_Size]{};

	m_TimesEx2Alt.clear();



	for (int stepSize = 1; stepSize <= (1024 * steps); stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < m_Array_Size; i += stepSize)
		{
			obj[i].ID *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		m_TimesEx2Alt.push_back(static_cast<float>(elapsedTime));
	}

	m_DataSizeEx2Alt = static_cast<int>(m_TimesEx2Alt.size());

	delete[] obj;
}

void RenderData(const std::vector<float>& times, int vals, ImU32& color, int count = 1)
{
	auto minIt = std::min_element(times.begin(), times.end());
	auto maxIt = std::max_element(times.begin(), times.end());
	float min = *minIt;
	float max = *maxIt;

	const float* dataFl[]{ {&times[0]} };
	ImU32 colors[1]{ {color} };

	ImGui::PlotConfig conf;
	conf.values.ys_list = dataFl;
	conf.values.ys_count = count;
	conf.values.count = vals;
	conf.line_thickness = 2.f;
	conf.values.colors = colors;
	conf.scale.min = min;
	conf.scale.max = max;
	conf.tooltip.show = true;
	conf.frame_size = ImVec2(250, 100.f);
	conf.line_thickness = 2.f;

	ImGui::Plot("plot", conf);
}

void RenderData(float min, float max, const float** data, int values, ImU32* colors, int count = 1)
{
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.ys_list = data;
	conf.values.ys_count = count;
	conf.values.count = values;
	conf.line_thickness = 2.f;
	conf.values.colors = colors;
	conf.scale.min = min;
	conf.scale.max = max;
	conf.tooltip.show = true;
	conf.frame_size = ImVec2(250, 100.f);
	conf.line_thickness = 2.f;

	ImGui::Plot("plot", conf);
}

void dae::Renderer::DrawPlotEx1()
{
	ImGui::Begin("Ex 1", nullptr, ImGuiWindowFlags_None);
	static int sample_size = 100;
	static int inputStep = 1;

	ImGui::InputScalar("samples", ImGuiDataType_U32, &sample_size, &inputStep, NULL, "%u");
	const char* buttonText = "Trash the cache";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_DataSizeEx1 = 0;
		GetDataEx1(sample_size);
	}

	if (m_DataSizeEx1 > 0)
	{
		ImU32 colorOrange = { ImColor{195,165,0} };
		RenderData(m_TimesEx1, m_DataSizeEx1, colorOrange);
	}

	ImGui::End();
}

void dae::Renderer::DrawPlotEx2()
{
	static int sample_size = 100;
	static int inputStep = 1;
	ImU32 colorGreen = { ImColor{0,255,0} };
	ImU32 colorPink = { ImColor{255,0,255} };

	// check if the graphs have values yet
	const bool ex2HasValues = m_DataSizeEx2 > 0;
	const bool ex2AltHasValues = m_DataSizeEx2Alt > 0;

	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);
	ImGui::InputScalar("samples", ImGuiDataType_U32, &sample_size, &inputStep, NULL, "%u");

	const char* buttonText = "Trash the cache with GameObject3D";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_DataSizeEx2 = 0;
		GetDataEx2(sample_size);
	}

	if (ex2HasValues)
	{
		RenderData(m_TimesEx2, m_DataSizeEx2, colorGreen);
	}

	buttonText = "Trash the cache With GameObject3DAlt";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
	
		m_DataSizeEx2Alt = 0;
		GetDataEx2Alt(sample_size);
		
	}

	if (ex2AltHasValues)
	{
		RenderData(m_TimesEx2Alt, m_DataSizeEx2Alt, colorPink);
	}

	if (ex2HasValues && ex2AltHasValues)
	{
		float min3D = *std::min_element(m_TimesEx2.begin(), m_TimesEx2.end());
		float max3D = *std::max_element(m_TimesEx2.begin(), m_TimesEx2.end());
		float min3DAlt = *std::min_element(m_TimesEx2Alt.begin(), m_TimesEx2Alt.end());
		float max3DAlt = *std::max_element(m_TimesEx2Alt.begin(), m_TimesEx2Alt.end());

		float min = min3D < min3DAlt ? min3D : min3DAlt;
		float max = max3D > max3DAlt ? max3D : max3DAlt;
		const int totalAllowdArrayValues{ 2 };
		const float* dataFl[totalAllowdArrayValues]{ &m_TimesEx2[0],&m_TimesEx2Alt[0] };
		ImU32 colors[totalAllowdArrayValues]{ colorGreen,colorPink };

		RenderData(min, max, dataFl, 10, colors, 2);
	}
	ImGui::End();
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	// Draw code here
	DrawPlotEx1();
	DrawPlotEx2();

	if (m_ShowDemo)
	{
		ImGui::ShowDemoWindow(&m_ShowDemo);
	}


	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();


	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}


}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
