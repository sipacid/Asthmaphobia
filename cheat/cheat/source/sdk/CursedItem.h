#pragma once
#include "sdk.h"

namespace SDK
{
	struct CursedItem
	{
	};

	DECLARE_METHOD_POINTER(CursedItem_Use, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), "Assembly-CSharp", "", "CursedItem", "Use", 0);

	DECLARE_METHOD_POINTER(CursedItem_BreakItem, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), "Assembly-CSharp", "", "CursedItem", "BreakItem", 0);
}
