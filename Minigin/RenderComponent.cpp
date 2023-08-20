#include "RenderComponent.h"

#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Transform.h"

using namespace dae;

void RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}

void RenderComponent::Render() const
{
	if (!m_pTexture) return;

	// Render at position from transform
	const glm::vec2 pos = m_pOwner->GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

glm::vec2 RenderComponent::GetTextureSize() const
{
	return m_pTexture->GetSize();
}
