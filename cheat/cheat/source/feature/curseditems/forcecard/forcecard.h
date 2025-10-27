#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::CursedItems
{
	class ForceCard final : public Feature
	{
	public:
		explicit ForceCard();
		~ForceCard() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override
		{
		}

		void OnMenu() override;

		void OnTarotCardSetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo) const;

	private:
		std::shared_ptr<Setting> ForcedTypeSetting;
	};
}
