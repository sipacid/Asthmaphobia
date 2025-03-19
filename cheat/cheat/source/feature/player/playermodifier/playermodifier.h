#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Player
{
	class PlayerModifier final : public Feature
	{
	public:
		explicit PlayerModifier();
		~PlayerModifier() override = default;

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
		int SanityArray[4] = {100, 100, 100, 100};
	};
}
