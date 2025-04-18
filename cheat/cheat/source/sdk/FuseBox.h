#pragma once
#include "sdk.h"

namespace SDK
{
	struct FuseBoxFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		int32_t FuseBoxType; // FuseBox.???
		void* Rends; // Renderer[]
		void* Lights; // Light[]
		void* VolumetricLights;
		void* LightPulse; // LightPulse[]
		void* RendsToTurnOff; // Renderer[]
		void* LightSourcesWithoutSwitches; // LightSource[]
		void* RotatingObjects;
		void* LoopSource; // AudioSource
		void* Noise; // Noise
		Transform* ParentObject;
		void* OnClip; // AudioClip
		void* OffClip; // AudioClip
		bool IsOn;
		void* Switches; // List<LightSwitch>
		void* PhotonInteract; // PhotonObjectInteract
		int CurrentOnLights;
		int MaxLights;
		Transform* MapIcon;
		Transform* ShakeObject;
		Transform* HandleObject;
		Vector3 HandleOnAngle;
		Vector3 HandleOffAngle;
		GameObject* BrokenFuseBoxObject;
		bool IsBroken;
		void* OnFuseBoxTrip; // FuseBox.FuseBoxTripEvent
	};

	struct FuseBox
	{
		void* Clazz;
		void* Monitor;
		FuseBoxFields Fields;
	};

	DECLARE_METHOD_POINTER(FuseBox_Start, void (*)(FuseBox* fuseBox, MethodInfo* methodInfo), "Assembly-CSharp", "", "FuseBox", "Start", 0);

	DECLARE_METHOD_POINTER(FuseBox_Use, void (*)(FuseBox* fuseBox, MethodInfo* methodInfo), "Assembly-CSharp", "", "FuseBox", "Use", 0);
}
