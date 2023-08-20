#pragma region _oldcode
//#pragma once
//#include "SceneManager.h"
//#include <string>
//#include "GameObject.h"
//
//namespace dae
//{
//	class Scene final
//	{
//	public:
//		void Add(std::shared_ptr<GameObject> object);
//		void Remove(std::shared_ptr<GameObject> object);
//		void RemoveAll();
//
//		void Update();
//		void FixedUpdate();
//		void Render() const;
//
//		std::string GetName() const { return m_Name; };
//		std::vector<std::unique_ptr<GameObject>>& GetAllObjects() { return m_Objects; }
//
//
//		void CleanUpObjects();
//
//		~Scene();
//		Scene(const Scene& other) = delete;
//		Scene(Scene&& other) = delete;
//		Scene& operator=(const Scene& other) = delete;
//		Scene& operator=(Scene&& other) = delete;
//
//	private: 
//		explicit Scene(const std::string& name);
//
//		std::string m_Name;
//		std::vector <std::unique_ptr<GameObject>> m_Objects{};
//
//	};
//
//}
#pragma endregion _oldcode

#pragma once
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		GameObject* CreateGameObject();

		void FixedUpdate();
		void Update();
		void Render() const;

		void CleanUpObjects();

		const std::string& GetName() const;
		void SetName(const std::string& name);

		std::vector<std::unique_ptr<GameObject>>& GetAllObjects() { return m_objects; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;
	};

}
