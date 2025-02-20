#include "source/common.h"
#include "source/feature/curseditems/forcecard/forcecard.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkTarotCard_SetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called TarotCard_SetCard");
	if (!globalRunning)
		return SDK::TarotCard_SetCard_ptr(tarotCard, type, methodInfo);

	dynamic_cast<Features::CursedItems::ForceCard*>(featureManager->GetFeatureByName("CursedItems::ForceCard"))->OnTarotCard_SetCard(tarotCard, type, methodInfo);
}
