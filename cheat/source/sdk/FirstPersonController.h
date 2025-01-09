#pragma once
#include "sdk.h"

namespace SDK
{


	struct MouseLookFields
	{
	float XSensitivity;                // Horizontal sensitivity
	float YSensitivity;                // Vertical sensitivity
	bool clampVerticalRotation;        // Whether to clamp vertical rotation
	float MinimumX;                    // Minimum horizontal rotation angle
	float MaximumX;                    // Maximum horizontal rotation angle
	bool smooth;                        // Whether smooth movement is enabled
	float smoothTime;                  // Smooth time for interpolation
	bool lockCursor;                   // Whether the cursor is locked
	bool m_cursorIsLocked;             // Whether the cursor is currently locked
	float horizontalLook;              // Horizontal look angle
	float verticalLook;                // Vertical look angle
	};


	struct MouseLook {
	void* klass;
	void* monitor;
	MouseLookFields Fields;
	};

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
