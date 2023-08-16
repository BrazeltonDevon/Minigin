#pragma once
#include "SceneManager.h"
#include <string>

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;

		std::string GetName() const { return m_Name; };
		std::vector<std::unique_ptr<GameObject>>& GetAllObjects() { return m_Objects; }


		void CleanUpObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::unique_ptr<GameObject>> m_Objects{};

	};

}
