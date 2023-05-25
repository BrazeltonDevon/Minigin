#pragma once
#include "Command.h"

namespace dae
{
	class MoveCommand : public Command {
		glm::vec3 m_Dir{};
		float m_Speed{};
	public:
		MoveCommand(GameObject* pOwner, float speed) : Command(pOwner), m_Dir{}, m_Speed{ speed } {};
		MoveCommand(GameObject* pOwner, glm::vec3 dir, float speed) : Command(pOwner), m_Dir{ dir }, m_Speed{ speed } {};
		virtual void Execute() override;
		virtual void Execute(glm::vec3 dir) override;
	};

	class DieCommand : public Command {
	
	private:

	public:
		DieCommand(GameObject* pOwner) : Command(pOwner) {};
		virtual void Execute() override;
	};


}


