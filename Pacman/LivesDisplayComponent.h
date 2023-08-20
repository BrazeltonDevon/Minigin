#pragma once
#include "FoodComponent.h"
#include "Subject.h"

namespace dae
{
	class TextComponent;
}

class AvatarComponent;

class LivesDisplayComponent final : public dae::Component, public dae::Observer<int>
{
public:
	LivesDisplayComponent() = default;
	~LivesDisplayComponent() override;

	LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
	LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
	LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
	LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

	void Initialize() override;
	void SetSubject(dae::Subject<int>* healthSubj);
	int GetHP() const;

private:

	void OnNotify(int healthDelta) override;
	void OnSubjectDestroy() override;
	void UpdateText();

	int m_HP{};
	dae::Subject<int>* m_pSubject{};

	dae::TextComponent* m_pText{};
};

