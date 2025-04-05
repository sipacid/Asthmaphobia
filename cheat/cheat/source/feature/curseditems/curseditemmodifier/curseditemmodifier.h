#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::CursedItems
{
	class CursedItemModifier final : public Feature
	{
	public:
		explicit CursedItemModifier();
		~CursedItemModifier() override = default;

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
		static bool DoesCursedItemExist(SDK::CursedItemType cursedItemType);
		bool SendOuijaBoardMessage = false;
		std::shared_ptr<Setting> CustomMessageSetting;
		char MessageBuffer[128] = "";
	};
}
