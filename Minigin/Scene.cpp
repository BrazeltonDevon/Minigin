#pragma region _oldcode
//#include "Scene.h"
//
//using namespace dae;
//
//Scene::Scene(const std::string& name) : m_Name(name) {}
//
//void dae::Scene::CleanUpObjects()
//{
//	// Remove game objects marked for delete
//	m_Objects.erase(std::remove_if(begin(m_Objects), end(m_Objects), [](const auto& pGameObject)
//		{
//			return pGameObject->IsMarkedForDelete();
//		}), end(m_Objects));
//}
//
//Scene::~Scene() = default;
//
//void Scene::Add(std::shared_ptr<GameObject> object)
//{
//	m_Objects.emplace_back(std::move(object));
//}
//
//void Scene::Remove(std::shared_ptr<GameObject> object)
//{
//	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
//}
//
//void Scene::RemoveAll()
//{
//	m_Objects.clear();
//}
//
//void Scene::Update()
//{
//	for(auto& object : m_Objects)
//	{
//		object->Update();
//	}
//}
//
//void dae::Scene::FixedUpdate()
//{
//	for (auto& object : m_Objects)
//	{
//		object->FixedUpdate();
//	}
//}
//
//void Scene::Render() const
//{
//	for (const auto& object : m_Objects)
//	{
//		object->Render();
//	}
//}
//
#pragma endregion _oldcode

#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

GameObject* Scene::CreateGameObject()
{
	auto pGameObject{ std::make_unique<GameObject>() };
	pGameObject->Init();

	GameObject* pGameObjectPtr{ pGameObject.get() };

	Add(std::move(pGameObject));
	return pGameObjectPtr;
}

void Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for (auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::CleanUpObjects()
{
	// Remove gameobjects from their container if they are marked as dead
	m_objects.erase(std::remove_if(begin(m_objects), end(m_objects), [](const auto& pGameObject)
		{
			return pGameObject->IsMarkedForDelete();
		}), end(m_objects));
}

const std::string& dae::Scene::GetName() const
{
	return m_name;
}

void dae::Scene::SetName(const std::string& name)
{
	m_name = name;
}
