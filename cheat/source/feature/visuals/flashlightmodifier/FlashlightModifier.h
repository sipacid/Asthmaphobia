#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class FlashlightModifier final : public Feature
	{
	public:
		explicit FlashlightModifier();
		~FlashlightModifier() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		void OnPCDisablePlayerComponents_Start(SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo);
		void OnPCFlashlight_Update(SDK::PCFlashlight* pcFlashLight, SDK::MethodInfo* methodInfo);
		void OnTorch_Update(SDK::Torch* torch, SDK::MethodInfo* methodInfo);

	private:
		std::shared_ptr<Setting> ShoulderLightEnabledSetting;
		std::shared_ptr<Setting> FlashlightEnabledSetting;
		std::shared_ptr<Setting> IntensitySetting;
		std::shared_ptr<Setting> BounceIntensitySetting;
		std::shared_ptr<Setting> ColorSetting;
		std::shared_ptr<Setting> SpotAngleSetting;
		std::shared_ptr<Setting> RangeSetting;
		std::shared_ptr<Setting> ShadowStrengthSetting;

		std::map<SDK::Light*, SDK::LightSettings> LightSettings;

		void SetLightSettings(SDK::Light* light) const;
		static void SetLightSettings(SDK::Light* light, const SDK::LightSettings& lightSettings);
		static SDK::LightSettings GetLightSettings(SDK::Light* light);
	};
}
