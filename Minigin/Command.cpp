#include "Command.h"
#include "GameObject.h"
#include <glm/fwd.hpp>
#include "GTime.h"

dae::Command::Command(GameObject* actor) :
	m_pOwner{ actor }
{
}