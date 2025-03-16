#pragma once
#include "sdk.h"

namespace SDK
{
	enum class EvidenceType;

	struct PhotoValuesFields
	{
		void* Field; // ScriptableObject derived class field
		EvidenceType EvidenceType;
		EMFType EMFInteractionType; // EMFInteractionType
		String* LocalisedNameKey;
		String* LocalisedDescKey;
		int32_t OneStarValue;
		int32_t TwoStarValue;
		int32_t ThreeStarValue;
	};

	struct PhotoValues
	{
		void* Clazz;
		void* Monitor;
		PhotoValuesFields Fields;
	};
}
