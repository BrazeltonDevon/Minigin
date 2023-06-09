#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"


namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		//void FixedUpdate();
		void Render();
		std::vector<std::shared_ptr<Scene>> GetAllScenes() const { return m_Scenes; }

		void SetCurrentScene(const std::string& name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_CurrentScene;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
