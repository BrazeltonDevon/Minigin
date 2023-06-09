#pragma once
#include "Singleton.h"
#include <vector>

// Singleton manager for all colliders
// In collider components, will check for any other
// colliders to see if they are colliding

namespace dae
{
	class ColliderComponent;

	class CollisionManager final: public Singleton<CollisionManager>
	{
	public:
		CollisionManager();
		~CollisionManager() = default;
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);
		const std::vector<ColliderComponent*>& GetColliders() const;

	private:
		std::vector<ColliderComponent*> m_pColliders;
	};
}


