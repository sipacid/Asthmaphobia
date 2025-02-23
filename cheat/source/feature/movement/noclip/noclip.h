#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Movement
{
	class NoClip final : public Feature
	{
	public:
		explicit NoClip();
		~NoClip() override = default;

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

	private:
		std::shared_ptr<Setting> SpeedSetting;
	};
}
