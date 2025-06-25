#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Player
{
	class GodMode final : public Feature
	{
	public:
		GodMode();
		~GodMode() override = default;

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

		std::nullptr_t OnPlayerStartKillingPlayerNetworked(SDK::Player* player, bool revive, void* photonMessageInfo, SDK::MethodInfo* methodInfo) const;
	};
}
