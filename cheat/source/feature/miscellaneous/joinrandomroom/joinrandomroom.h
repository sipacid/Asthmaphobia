#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class JoinRandomRoom final : public Feature
	{
	public:
		explicit JoinRandomRoom();
		~JoinRandomRoom() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		static void Run();
	};
}
