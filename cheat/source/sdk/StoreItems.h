#pragma once
#include "sdk.h"

namespace SDK
{
	struct StoreItemFields
	{
		int equipmentType;
		int tier;
		struct System_String_o* itemName;
		struct System_String_o* descriptionID;
		struct System_String_o* loreID;
		int cost;
		int upgradeCost;
		int requiredLevel;
		int defaultAmount;
		int maxAmount;
		bool isConsumable;
		struct UnityEngine_Sprite_o* icon;
		struct UnityEngine_Sprite_o* blueprintSprite;
		struct UnityEngine_Sprite_o* unlockSprite;
		struct StoreItem_StoreItemFeature_array* features;
		struct EquipmentInfo_o* equipment;
		int m_amountOwned;
		struct StoreItem___________o* _________;

	};


	struct StoreItem {
		void* klass;
		void* monitor;
		StoreItemFields fields;
	};

	DECLARE_FUNCTION_POINTER(StoreItem_SetAmmount, void(*)(StoreItem* storeItem, int ammount, MethodInfo* methodInfo), 0x1998510);
}
