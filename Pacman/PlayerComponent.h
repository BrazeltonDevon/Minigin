#pragma region _oldcode
//#pragma once
//#include "Component.h"
//#include "Subject.h"
//#include "TextComponent.h"
//#include "Enums.h"
//
//namespace dae
//{
//
//	class PlayerComponent : public Component
//	{
//	public:
//		PlayerComponent(GameObject* owner, bool isGhost, int playerNr);
//		~PlayerComponent();
//
//		void Update() override;
//		void Initialize();
//		void SetDirection(Direction direction);
//
//		//bool GhostCollision(glm::vec3 pos);
//		bool IsPoweredUp() { return m_IsPoweredUp; }
//		int GetLives() { return m_Lives; }
//		int GetScore() { return m_Score; }
//		bool IsGhost() { return m_IsGhost; }
//		void AddObserver(Observer* obs);
//
//		void AddScore(int amount) { m_Score += amount; };
//
//		void Start();
//		void Die();
//
//	private:
//		void Respawn();
//		bool CollidesInTargetDir();
//
//		Direction m_Direction = Direction::NONE;
//		Direction m_TargetDirection = Direction::NONE;
//
//		//score
//		int m_Score = 0;
//		TextComponent* m_pScoreText = nullptr;
//		bool m_IsGhost = false;
//		bool m_IsPoweredUp = false;
//		float m_PowerupTimer = 0;
//
//		glm::vec3 m_StartPosition = glm::vec3(-50, -50, -50);
//
//		int m_Lives = 3;
//		std::vector <std::shared_ptr<dae::GameObject>>  m_LivesArr;
//
//		float m_RespawnTimer = 2;
//		float m_MovementSpeed = 50.f;
//
//		std::unique_ptr<Subject> m_PlayerSubject;
//
//	};
//
//
//}
#pragma endregion _oldcode

