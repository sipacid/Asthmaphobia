#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class GodMode final : public Feature
	{
	public:
		GodMode();
		~GodMode() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		std::nullptr_t OnPlayerStartKillingPlayerNetworked(SDK::Player* player, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo) const;
	};
}
