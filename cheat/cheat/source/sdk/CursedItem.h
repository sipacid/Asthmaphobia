#pragma once
#include "sdk.h"

namespace SDK
{
	struct CursedItem
	{
	};

	DECLARE_FUNCTION_POINTER(CursedItem_Use, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), 0x1FF60B0);
	DECLARE_FUNCTION_POINTER(CursedItem_BreakItem, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), 0x1FF44A0);
}
