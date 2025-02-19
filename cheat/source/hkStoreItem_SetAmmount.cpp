#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkStoreItem_set_amountOwned(SDK::StoreItem* storeItem, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called StoreItem_Setammount");
	if (!globalRunning)
		return SDK::StoreItem_SetAmmount_ptr(storeItem, 99, methodInfo);

	

	SDK::StoreItem_SetAmmount_ptr(storeItem, 99, methodInfo);
}
