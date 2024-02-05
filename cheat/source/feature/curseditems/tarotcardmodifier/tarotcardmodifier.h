#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::CursedItems
{
	class TarotCardModifier final : public Feature
	{
	public:
		explicit TarotCardModifier();
		~TarotCardModifier() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		void OnTarotCard_SetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo) const;

	private:
		std::shared_ptr<Setting> ForceTypeSetting;
		std::shared_ptr<Setting> ForcedTypeSetting;
	};
}
