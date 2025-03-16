#pragma once
#include "sdk.h"

namespace SDK
{
	struct EvidenceControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		ListEvidence* EvidenceList;
		void* Field2; // LevelRoom[]
		void* Field3; // PhotonView
		void* Field4; // DNAEvidence
		Transform* GhostOrb;
		void* Field6; // ParticleSystemRenderer
		LevelController* Field7;
		bool Field8;
		float Field9;
		void* Field10; // List<Fingerprint>
		float Field11; // const 0.015f
		void* Field12; // Color
	};

	struct EvidenceController
	{
		void* Clazz;
		void* Monitor;
		EvidenceControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(EvidenceController_Start, void(*)(EvidenceController* evidenceController, MethodInfo* methodInfo), "Assembly-CSharp", "", "EvidenceController", "Start",
	                       0);
}
