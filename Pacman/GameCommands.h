#pragma once
#include "Command.h"
#include "GameObject.h"
#include "GTime.h"

class JumpCommand final : public dae::Command
{
public:
	explicit JumpCommand(dae::GameObject* go, float speed)
		:m_pGo{ go }
		, m_Speed{ speed }
	{}

	void Execute() override;
private:
	dae::GameObject* m_pGo{};
	float m_Speed{};
};

class MoveLeftCommand final : public dae::Command
{
public:
	explicit MoveLeftCommand(dae::GameObject* go, float speed)
		:m_pGo{ go }
		, m_Speed{ speed }
	{}

	void Execute() override;
private:
	void Move();

	dae::GameObject* m_pGo{};
	float m_Speed{};
};

class MoveRightCommand final : public dae::Command
{
public:
	explicit MoveRightCommand(dae::GameObject* go, float speed)
		:m_pGo{ go }
		, m_Speed{ speed }
	{}

	void Execute() override;
private:
	void Move();

	dae::GameObject* m_pGo{};
	float m_Speed{};
};

class ShootBubbleCommand final : public dae::Command
{
public:
	explicit ShootBubbleCommand(dae::GameObject* go)
		: m_pGo{ go }
	{}

	void Execute() override;
private:
	dae::GameObject* m_pGo{};
};

class ThrowRockCommand final : public dae::Command
{
public:
	explicit ThrowRockCommand(dae::GameObject* go)
		: m_pGo{ go }
	{
		m_LastTimeThrew = dae::GTime::GetInstance().GetTotal();
	}

	void Execute() override;
private:
	dae::GameObject* m_pGo{};

	float m_LastTimeThrew;
};
