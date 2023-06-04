#pragma once
#include "Command.h"
#include "Enums.h"

namespace dae
{
	class MoveCommandOld : public Command {
		glm::vec3 m_Dir{};
		float m_Speed{};
	public:
		MoveCommandOld(GameObject* pOwner, float speed) : Command(pOwner), m_Dir{}, m_Speed{ speed } {};
		MoveCommandOld(GameObject* pOwner, glm::vec3 dir, float speed) : Command(pOwner), m_Dir{ dir }, m_Speed{ speed } {};
		virtual void Execute() override;
		virtual void Execute(glm::vec3 dir) override;
	};

	class DieCommand : public Command {
	
	private:

	public:
		DieCommand(GameObject* pOwner) : Command(pOwner) {};
		virtual void Execute() override;
	};

	class MoveCommand : public Command {
		Direction m_Dir{};
	public:
		MoveCommand(GameObject* pOwner, Direction dir) : Command(pOwner), m_Dir{ dir } {};
		virtual void Execute() override;

	};


}


