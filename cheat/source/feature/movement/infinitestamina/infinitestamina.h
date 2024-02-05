#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Movement
{
	class InfiniteStamina final : public Feature
	{
	public:
		InfiniteStamina();
		~InfiniteStamina() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		void OnPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo) const;
	};
}
