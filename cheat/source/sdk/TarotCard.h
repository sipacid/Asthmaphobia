#pragma once
#include "sdk.h"

namespace SDK
{
	struct TarotCard
	{
	};

	DECLARE_FUNCTION_POINTER(TarotCard_SetCard, void(*)(TarotCard* tarotCard, TarotCardType type, MethodInfo* methodInfo), 0x57A620);
}
