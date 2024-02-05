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
		void* LightPulse; // LightPulse[]
		void* RendsToTurnOff; // Renderer[]
		void* LightSourcesWithoutSwitches; // LightSource[]
		void* LoopSource; // AudioSource
		void* Noise; // Noise
		Transform* Field8; // Transform
		void* OnClip; // AudioClip
		void* OffClip; // AudioClip
		bool IsOn;
		void* Field12; // List<LightSwitch>
		void* PhotonInteract; // PhotonObjectInteract
		int Field14;
		int Field15;
		Transform* MapIcon; // Transform
		Transform* ShakeObject; // Transform
		Transform* HandleObject; // Transform
		Vector3 HandleOnAngle; // Vector3
		Vector3 HandleOffAngle; // Vector3
		void* BrokenFuseBoxObject; // GameObject
		bool Field22;
		void* Field23; // FuseBox.???
	};

	struct FuseBox
	{
		void* Clazz; // FuseBoxClass
		void* Monitor; // MonitorData
		FuseBoxFields Fields;
	};

	DECLARE_FUNCTION_POINTER(FuseBox_Start, void (*)(FuseBox* fuseBox, MethodInfo* methodInfo), 0x1BE8AA0);
}
