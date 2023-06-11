#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class PacDotComponent : public Component
	{
	public:
		PacDotComponent(GameObject* owner);
		void AddPoints();
	private:
		int m_PointAmnt{ 10 };
		std::unique_ptr<Subject> m_pDotSubject;
	};

}

