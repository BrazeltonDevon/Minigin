#pragma once
#include <string>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class GameObject;

	class LevelCreator : public Singleton<LevelCreator>
	{
	public:
		static bool CreateLevel(const std::wstring& filePath, Scene* scene);
		GameObject* GetPlayer1() { return m_pPlayer1; };
		void SetPlayer1(GameObject* player1) { m_pPlayer1 = player1; };
	private:
		void CreateWall(Scene* scene, float xPos, float yPos);
		GameObject* m_pPlayer1 = nullptr;
	};
}


