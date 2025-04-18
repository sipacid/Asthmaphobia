#pragma once
#include "sdk.h"

namespace SDK
{
	struct EvidenceControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		ListEvidence* EvidenceInLevel;
		void* RoomsToSpawnDNAEvidenceInside; // LevelRoom[]
		void* View; // PhotonView
		void* Bone; // DNAEvidence
		Transform* GhostOrb;
		void* GhostOrbRenderer; // ParticleSystemRenderer
		LevelController* LevelController;
		bool IsFreezingTemperatureGhost;
		float DotsCheckTimer;
		void* ActiveFingerprints; // List<Fingerprint>
		void* FoggyOrbColor; // Color
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
