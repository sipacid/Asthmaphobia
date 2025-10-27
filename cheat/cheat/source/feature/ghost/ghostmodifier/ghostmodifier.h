#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Ghost
{
	class GhostModifier final : public Feature
	{
	public:
		explicit GhostModifier();
		~GhostModifier() override = default;

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

		void OnGhostAIUpdate(SDK::GhostAI* ghost, SDK::MethodInfo* methodInfo);

	private:
		std::shared_ptr<Setting> GhostSpeedSetting;
		std::shared_ptr<Setting> ForcedStateSetting;

		bool ForceAppear = false;
		bool ForceState = false;
	};
}
