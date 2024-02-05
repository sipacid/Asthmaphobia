#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Movement
{
	class Teleport final : public Feature
	{
	public:
		explicit Teleport();
		~Teleport() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		enum class Target : int32_t
		{
			Ghost,
			DeathRoom,
			Truck,
			Player
		};

		std::shared_ptr<Setting> TargetSetting;

		void Run(const SDK::Player* player) const;
	};
}
