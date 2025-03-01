#pragma once
#include "sdk.h"

namespace SDK
{
	enum class EvidenceType;

	struct PhotoValuesFields
	{
		void* Field; // ScriptableObject derived class field
		EvidenceType EvidenceType; // EvidenceType
		EMFType EMFInteractionType; // EMFInteractionType
		String* LocalisedNameKey; // string
		String* LocalisedDescKey; // string
		int32_t OneStarValue;
		int32_t TwoStarValue;
		int32_t ThreeStarValue;
	};

	struct PhotoValues
	{
		void* Clazz; // PhotonValuesClass
		void* Monitor; // MonitorData
		PhotoValuesFields Fields;
	};
}
