#include "Component.h"
#include "GameObject.h"

//Component::Component(std::shared_ptr<dae::GameObject> pOwner)
//{
//	m_pGameObject = pOwner;
//}

//void Component::SetOwner(std::shared_ptr<dae::GameObject> go)
//{
//	m_pGameObject = go;
//}

Component::Component(dae::GameObject* pOwner)
	: m_pGameObject{pOwner}
{
}
