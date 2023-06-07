#pragma once
#include <string>
#include "Singleton.h"

namespace dae
{
	class Scene;

	class LevelCreator : public Singleton<LevelCreator>
	{
	public:
		static bool CreateLevel(const std::wstring& filePath, Scene* scene);
	};
}


