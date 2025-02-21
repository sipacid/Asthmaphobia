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
		MouseLook* MouseLook;
		bool UseFovKick;
		void* FovKick; // FOVKick
		bool UseHeadBob;
		bool ToggleSprint;
		void* HeadBob; // CurveControlledBob
		float StepInterval;
		Camera* Camera;
		Vector2 Input;
		Vector3 MoveDir;
		void* CharacterController; // PhysicsCharacterController
		bool Crouching;
		float CurrentSpeed;
		Vector3 DesiredMove;
		RaycastHit HitInfo;
		void* OnStartSprint; // UnityEvent
		void* OnStartWalk; // UnityEvent
	};

	struct FirstPersonController
	{
		void* Clazz; // FirtsPersonControllerClass
		void* Monitor; // MonitorData
		FirstPersonControllerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(FirstPersonController_Update, void (*)(FirstPersonController* firstPersonController, MethodInfo* methodInfo), 0xFCF4A0);
}
