#pragma once
#include <SDL.h>
#include "Singleton.h"
#include <vector>

//class ImU32;

namespace dae
{
	class Texture2D;

	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
		bool m_ShowDemo{ false };

		// Trash the cache
		void DrawPlotEx1();
		void DrawPlotEx2();

		void GetDataEx1(int steps);
		void GetDataEx2(int steps);
		void GetDataEx2Alt(int steps);

		//void RenderData(const std::vector<float>& times, int vals, ImU32& color, int count);
		
		//int m_Steps{};
		int m_Array_Size = 200000;
		std::vector<float> m_TimesEx1{};
		std::vector<float> m_TimesEx2{};
		std::vector<float> m_TimesEx2Alt{};

		// for plot function
		int m_DataSizeEx1{};
		int m_DataSizeEx2{};
		int m_DataSizeEx2Alt{};


	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }



	};
}

