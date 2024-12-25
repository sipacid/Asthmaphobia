#pragma once
#include "sdk.h"

namespace SDK
{
	struct EvidenceControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		ListEvidence* EvidenceList; // List<Evidence>
		void* Field2; // LevelRoom[]
		void* Field3; // PhotonView
		void* Field4; // DNAEvidence
		Transform* GhostOrb; // Transform
		void* Field6; // ParticleSystemRenderer
		void* Field7; // LevelController
		bool Field8;
		float Field9;
		void* Field10; // List<Fingerprint>
		float Field11; // const 0.015f
		void* Field12; // Color
	};

	struct EvidenceController
	{
		void* Clazz; // EvidenceControllerClass
		void* Monitor; // MonitorData
		EvidenceControllerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(EvidenceController_Start, void(*)(EvidenceController* evidenceController, MethodInfo* methodInfo), 0x1C4F1B0);
}
