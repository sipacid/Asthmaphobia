#pragma once
#include "sdk.h"

namespace SDK
{
	struct TarotCard
	{
	};

	DECLARE_METHOD_POINTER(TarotCard_SetCard, void(*)(TarotCard* tarotCard, TarotCardType type, MethodInfo* methodInfo), "Assembly-CSharp", "", "TarotCard", "SetCard", 1);
}
