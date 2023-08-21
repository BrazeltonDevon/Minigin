#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	if (m_ActiveSceneId >= 0)
	{
		m_Scenes[m_ActiveSceneId]->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	if (m_ActiveSceneId >= 0)
	{
		m_Scenes[m_ActiveSceneId]->FixedUpdate();
	}
}

void dae::SceneManager::Render()
{
	if (m_ActiveSceneId >= 0)
	{
		m_Scenes[m_ActiveSceneId]->Render();
	}

}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	// find scene with given name and set active scene to it

	for (size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetName() == name)
		{
			m_ActiveSceneId = static_cast<int>(i);
		}
	}
}

void dae::SceneManager::SetCurrentScene(const Scene* pScene)
{
	for (size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i].get() == pScene)
			m_ActiveSceneId = static_cast<int>(i);
	}
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	if (m_Scenes.size() != 0 && m_ActiveSceneId != -1)
	{
		return m_Scenes[m_ActiveSceneId].get();
	}
	else
	{
		return nullptr;
	}
}

void dae::SceneManager::CleanUpObjects()
{
	//std::cout << "cleaning up objects\n";
	if (m_ActiveSceneId >= 0)
	{
		m_Scenes[m_ActiveSceneId]->CleanUpObjects();
	}
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::make_shared<Scene>(name);
	m_Scenes.push_back(scene);
	return scene.get();
}
