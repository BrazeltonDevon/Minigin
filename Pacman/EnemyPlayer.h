#pragma once
#include "Scene.h"

class EnemyPlayer final
{
public:
	static dae::GameObject* CreateMaita(dae::Scene* pScene, const glm::vec2& spawnPos);
};

