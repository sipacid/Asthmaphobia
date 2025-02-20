#pragma once
#include "sdk.h"

namespace SDK
{
	struct CursedItem
	{
	};

	DECLARE_FUNCTION_POINTER(CursedItem_Use, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), 0x205DDC0);
	DECLARE_FUNCTION_POINTER(CursedItem_BreakItem, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), 0x205B130);
}
