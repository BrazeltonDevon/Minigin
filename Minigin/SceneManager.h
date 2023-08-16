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
		Scene* CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void Render();
		//std::vector<std::shared_ptr<Scene>> GetAllScenes() const { return m_Scenes; }

		void SetCurrentScene(const std::string& name);
		void SetCurrentScene(const Scene* pScene);
		Scene* GetCurrentScene() const;

		void CleanUpObjects();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneId{ -1 };
	};
}
