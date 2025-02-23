#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class LeavePeople final : public Feature
	{
	public:
		LeavePeople();
		~LeavePeople() override = default;

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

		bool OnExitLevelThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo) const;
	};
}
