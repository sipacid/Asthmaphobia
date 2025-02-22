#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class DoorModifier final : public Feature
	{
	public:
		explicit DoorModifier();
		~DoorModifier() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		enum class Mode : uint8_t
		{
			ToggleDoorCollision,
			ToggleDoorInteraction,
			ToggleDoorLock
		};

		static void DoorLoop(Mode mode, bool enabled, SDK::DoorArray* doorArray);
		static void Run(Mode mode, bool enabled);
		static void Test();
	};
}
