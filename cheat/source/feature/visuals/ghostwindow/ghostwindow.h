#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class GhostWindow final : public Feature
	{
	public:
		GhostWindow();
		~GhostWindow() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		static std::string GetGhostEvidenceString();
	};
}
