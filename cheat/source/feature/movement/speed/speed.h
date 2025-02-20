#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Movement
{
	class Speed final : public Feature
	{
	public:
		explicit Speed();
		~Speed() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		void OnFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo);

	private:
		const float DefaultWalkSpeed = 1.6f;
		const float DefaultRunSpeed = 3.0f;

		bool WasEnabled = false;

		std::shared_ptr<Setting> WalkSpeedSetting;
		std::shared_ptr<Setting> RunSpeedSetting;
	};
}
