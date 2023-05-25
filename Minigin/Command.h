#pragma once
#include <glm/glm.hpp>

// Base class for commands

namespace dae {
	class GameObject;
	class Command {
		GameObject* m_pOwner;
	protected:
		GameObject* GetOwner() const { return m_pOwner; }
	public:
		Command(GameObject* actor);
		virtual void Execute() {};
		virtual void Execute(glm::vec3) {};
	};


}