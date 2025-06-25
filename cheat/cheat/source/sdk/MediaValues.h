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
		int32_t CapturableMedia; // Enum Photo = 1; Video = 2; Sound = 4;
		String* LocalisedNameKey;
		String* LocalisedDescKey;
		int32_t UniqueValue;
		int32_t DuplicateValue;
	};

	struct MediaValues
	{
		void* Clazz;
		void* Monitor;
		PhotoValuesFields Fields;
	};
}
