#pragma once
#include "MouseLook.h"
#include "sdk.h"

namespace SDK
{
	struct FirstPersonControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		bool CanMove;
		bool CanTurn;
		bool IsSprinting;
		bool IsMoving;
		bool canSprint;
		float RunstepLength; // range 0 - 1
		float StickToGroundForce;
		float GravityMultiplier;
		MouseLook* MouseLook; // MouseLook
		bool UseFovKick;
		void* FovKick; // FOVKick
		bool UseHeadBob;
		bool ToggleSprint;
		void* HeadBob; // CurveControlledBob
		float StepInterval;
		Camera* Camera; // Camera
		Vector2 Input; // Vector2
		Vector3 MoveDir; // Vector3
		void* CharacterController; // PhysicsCharacterController
		bool Field0;
		bool Crouching;
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

	DECLARE_FUNCTION_POINTER(FirstPersonController_Update, void (*)(FirstPersonController* firstPersonController, MethodInfo* methodInfo), 0x100ABD0);
}
