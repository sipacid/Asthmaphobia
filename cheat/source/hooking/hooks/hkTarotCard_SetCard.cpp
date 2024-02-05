#include "source/common.h"
#include "source/feature/curseditems/tarotcardmodifier/tarotcardmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkTarotCard_SetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called TarotCard_SetCard");
	if (!globalRunning)
		return SDK::TarotCard_SetCard_ptr(tarotCard, type, methodInfo);

	dynamic_cast<Features::CursedItems::TarotCardModifier*>(featureManager->GetFeatureByName("CursedItems::TarotCardModifier"))->OnTarotCard_SetCard(tarotCard, type, methodInfo);
}
