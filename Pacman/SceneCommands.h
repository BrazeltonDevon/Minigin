#pragma once
#include "Command.h"

class SkipLevelCommand final : public dae::Command
{
public:
	explicit SkipLevelCommand()
	{}

	void Execute() override;
private:

};

class LeaveHighScoreSceneCommand final : public dae::Command
{
public:
	explicit LeaveHighScoreSceneCommand(int score)
		:m_Score{ score }
	{}

	void Execute() override;
private:
	int m_Score{};
};

class StartCoopCommand final : public dae::Command
{
public:
	StartCoopCommand() = default;

	void Execute() override;
private:
};

class StartSinglePlayerCommand final : public dae::Command
{
public:
	StartSinglePlayerCommand() = default;

	void Execute() override;
private:
};

class StartVersusCommand final : public dae::Command
{
public:
	StartVersusCommand() = default;

	void Execute() override;
private:
};