#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	/*for(auto& scene : m_Scenes)
	{
		scene->Update();
	}*/

	m_CurrentScene->Update();
}

//void dae::SceneManager::FixedUpdate()
//{
//	for (auto& scene : m_scenes)
//	{
//		scene->FixedUpdate();
//	}
//}

void dae::SceneManager::Render()
{
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}

	m_CurrentScene->Render();
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	// find scene with given name and set active scene to it
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_CurrentScene = scene;
			return;
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	if (!m_CurrentScene)m_CurrentScene = scene;

	return *scene;
}
