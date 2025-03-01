#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class EvidenceESP final : public Feature
	{
	public:
		explicit EvidenceESP();
		~EvidenceESP() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override;
		void OnMenu() override;

	private:
		struct EvidenceInfo
		{
			std::string_view Text;
			bool IsCursedItem;
		};

		static const std::unordered_map<SDK::EvidenceType, EvidenceInfo> EVIDENCE_INFO_MAP_;

		std::shared_ptr<Setting> CursedItemEnabledSetting;
		std::shared_ptr<Setting> DNAEvidenceEnabledSetting;
		std::shared_ptr<Setting> CursedItemColorSetting;
		std::shared_ptr<Setting> DNAEvidenceColorSetting;
	};
}
