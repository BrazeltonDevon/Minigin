#pragma once
#include "EnemyPlayerComponent.h"
#include "Scene.h"

class AvatarComponent;

class DisplayHUD final
{
public:
	static dae::GameObject* CreateHUD(dae::Scene* pScene, AvatarComponent* avatarComp, EnemyPlayerComponent* maitaComp = nullptr);
};
