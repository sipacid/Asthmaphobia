#pragma once
#include "sdk.h"

namespace SDK
{
	struct FirstPersonControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		bool CanMove;
		bool CanTurn;
		bool IsWalking;
		bool CanSprint;
		float RunstepLength; // range 0 - 1
		float StickToGroundForce;
		float GravityMultiplier;
		void* MouseLook; // MouseLook
		bool UseFovKick;
		void* FovKick; // FOVKick
		bool UseHeadBob;
		bool ToggleSprint;
		void* HeadBob; // CurveControlledBob
		float StepInterval;
		Camera* Camera; // Camera
		Vector2 Input; // Vector2
		Vector3 MoveDir; // Vector3
		void* CharacterController; // CharacterController
		int32_t CollisionFlags; // CollisionFlags
		float StepCycle;
		float NextStep;
		bool Crouching;
		bool WasWalking;
		float CurrentSpeed;
		Vector3 DesiredMove; // Vector3
		void* HitInfo; // RaycastHit
		void* OnStartSprint; // UnityEvent
		void* OnStartWalk; // UnityEvent
	};

	// Assembly-Csharp-firstpass.FirstPersonController
	struct FirstPersonController
	{
		void* Clazz; // FirtsPersonControllerClass
		void* Monitor; // MonitorData
		FirstPersonControllerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(FirstPersonController_Update, void (*)(FirstPersonController* firstPersonController, MethodInfo* methodInfo), 0x430E20);
}
