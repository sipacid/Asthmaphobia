#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Miscellaneous
{
	class AntiKick final : public Feature
	{
	public:
		AntiKick();
		~AntiKick() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

		void OnServerManagerKickPlayerNetworked(SDK::ServerManager* serverManager, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo) const;
	};
}
