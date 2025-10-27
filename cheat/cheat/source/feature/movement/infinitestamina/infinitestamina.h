#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Movement
{
	class InfiniteStamina final : public Feature
	{
	public:
		explicit InfiniteStamina();
		~InfiniteStamina() override = default;

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

		void OnPlayerStaminaUpdate(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo) const;
	};
}
