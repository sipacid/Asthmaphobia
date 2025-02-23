#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class FuseBoxESP final : public Feature
	{
	public:
		explicit FuseBoxESP();
		~FuseBoxESP() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override;
		void OnMenu() override;

	private:
		std::shared_ptr<Setting> ShowStatusSetting;
		std::shared_ptr<Setting> ColorSetting;

		std::string TextBuffer;
		static constexpr size_t INITIAL_BUFFER_SIZE = 32;
	};
}
