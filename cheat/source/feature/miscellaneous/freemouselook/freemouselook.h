#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class FreeMouseLook final : public Feature
	{
	public:
		FreeMouseLook();
		~FreeMouseLook() override = default;

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

		void OnFirstPersonController_Update(const SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo) const;
	};
}
