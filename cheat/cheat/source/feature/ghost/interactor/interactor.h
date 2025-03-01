#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Ghost
{
	class Interactor final : public Feature
	{
	public:
		Interactor();
		~Interactor() override = default;

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

		void OnGhostAIUpdate(const SDK::GhostAI* ghost, SDK::MethodInfo* methodInfo);

	private:
		bool ForceInteractWithProp = false;
		bool ForceAbility = false;
		bool ForceInteract = false;
		bool ForceInteractWithRandomDoor = false;
		bool ForceInteractWithRandomProp = false;
		bool ForceNormalInteraction = false;
		bool ForceTwinInteraction = false;
	};
}
