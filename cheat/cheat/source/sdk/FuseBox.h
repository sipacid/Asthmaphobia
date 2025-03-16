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
		Transform* Transform0;
		void* OnClip; // AudioClip
		void* OffClip; // AudioClip
		bool IsOn;
		void* Field12; // List<LightSwitch>
		void* PhotonInteract; // PhotonObjectInteract
		int Field14;
		int Field15;
		Transform* MapIcon;
		Transform* ShakeObject;
		Transform* HandleObject;
		Vector3 HandleOnAngle;
		Vector3 HandleOffAngle;
		GameObject* BrokenFuseBoxObject;
		bool Field22;
		void* Field23; // FuseBox.???
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
