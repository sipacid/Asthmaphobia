#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class AutoKey final : public Feature
	{
	public:
		explicit AutoKey();
		~AutoKey() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		void OnKey_Start(SDK::Key* key, SDK::MethodInfo* methodInfo) const;
	};
}
