#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class Pickup final : public Feature
	{
	public:
		explicit Pickup();
		~Pickup() override = default;

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

		void OnPhotonObjectInteract_Start(SDK::PhotonObjectInteract* photonObjectInteract, SDK::MethodInfo* methodInfo) const;
	};
}
