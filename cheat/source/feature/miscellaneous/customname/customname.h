#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class CustomName final : public Feature
	{
	public:
		explicit CustomName();
		~CustomName() override = default;

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

	private:
		std::shared_ptr<Setting> NickNameSetting;
		char NickNameBuffer[128];
	};
}
