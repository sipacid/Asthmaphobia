#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::CursedItems
{
	class CursedItemModifier final : public Feature
	{
	public:
		explicit CursedItemModifier();
		~CursedItemModifier() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		static bool DoesCursedItemExist(SDK::CursedItemType cursedItemType);
	};
}
