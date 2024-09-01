#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class RewardModifier final : public Feature
	{
	public:
		explicit RewardModifier();
		~RewardModifier() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		int32_t OnGetInvestigationBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);

	private:
		std::shared_ptr<Setting> InvestigationBonusSetting;
	};
}
