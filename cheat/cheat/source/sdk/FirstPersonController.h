#pragma once
#include "MouseLook.h"
#include "sdk.h"

namespace SDK
{
	struct FirstPersonControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool CanMove;
		bool CanTurn;
		bool IsSprinting;
		bool IsMoving;
		bool CanSprint;
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
		PhysicsCharacterController* CharacterController;
		bool Crouching;
		float CurrentSpeed;
		Vector3 DesiredMove;
		RaycastHit HitInfo;
		void* OnStartSprint; // UnityEvent
		void* OnStartWalk; // UnityEvent
	};

	struct FirstPersonController
	{
		void* Clazz;
		void* Monitor;
		FirstPersonControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(FirstPersonController_Update, void (*)(FirstPersonController* firstPersonController, MethodInfo* methodInfo), "Assembly-CSharp", "",
	                       "FirstPersonController", "Update", 0);
}
