#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class FullBright final : public Feature
	{
	public:
		explicit FullBright();
		~FullBright() override = default;

		void OnEnable() override;

		void OnDisable() override;

		void OnDraw() override
		{
		}

		void OnMenu() override;

		void OnPCDisableComponentsStart(const SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo) const;
	};
}
