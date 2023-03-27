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
		virtual void Execute(glm::vec3&) {};
	};

// Commands inherited from base command

	class MoveCommand : public Command {
		glm::vec3 m_Dir{};
		float m_Speed{};
	public:
		MoveCommand(GameObject* pOwner, float speed) : Command(pOwner), m_Dir{}, m_Speed{speed} {};
		MoveCommand(GameObject* pOwner, glm::vec3& dir, float speed) : Command(pOwner), m_Dir{ dir }, m_Speed{speed} {};
		virtual void Execute() override;
		virtual void Execute(glm::vec3& dir) override;
	};
}