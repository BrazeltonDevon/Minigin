#pragma once
#include "Component.h"
#include "Subject.h"
#include "TextComponent.h"
#include "Enums.h"

namespace dae
{

	class PlayerComponent : public Component
	{
	public:
		PlayerComponent(bool isGhost, int playerNr, GameObject* owner);
		~PlayerComponent();

		void Update() override;
		void SetDirection(Direction direction);

		//bool GhostCollision(glm::vec3 pos);
		bool IsPoweredUp() { return m_IsPoweredUp; }
		int GetLives() { return m_Lives; }
		bool IsGhost() { return m_IsGhost; }

	private:
		//void UpdateMovement(float deltaTime);
		//void Respawn();

		Direction m_Direction = Direction::RIGHT;
		Direction m_TargetDirection = Direction::RIGHT;

		//score
		int m_Score = 0;
		TextComponent* m_pScoreText = nullptr;
		bool m_IsGhost = false;
		bool m_IsPoweredUp = false;
		float m_PowerupTimer = 0;

		glm::vec3 m_StartPosition = glm::vec3(-50, -50, -50);
		int m_Lives = 3;
		std::vector <std::shared_ptr<dae::GameObject>>  m_LivesArr;

		float m_RespawnTimer = 2;

		std::unique_ptr<Subject> m_PlayerSubject;

	};


}