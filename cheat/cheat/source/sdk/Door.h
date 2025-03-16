#pragma once
#include "sdk.h"

namespace SDK
{
	struct Door;

	struct DoorFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool Field0;
		bool Field1;
		bool Field2;
		void* DoorLockClips; // AudioClip[]
		void* DoorUnlockClips; // AudioClip[]
		void* Field3; // AudioClip[]
		void* Field4; // AudioClip[]
		float ClosedVolume;
		float UnlockVolume;
		void* LoopSource; // AudioSource
		void* Field5; // OcclusionPortal
		void* Field6; // Volume
		bool Field7;
		bool Field8;
		bool Field9;
		void* Field10; // PhotonView
		Rigidbody* Rigidbody;
		void* Field11; // PhotonObjectInteract
		void* Field12; // Fingerprint
		Collider* Field13;
		float Field14;
		void* Noise; // Noise
		void* Field15; // ConfigurableJoint
		void* Field16; // Renderer[]
		bool IsDoorRotationBackwards;
		int32_t Field17; // Enum: hinge, slide, cloth
		int32_t Field18; // Enum: wood, Metal, Locker, Fabric
		int32_t Axis; // Enum: None, X, Y, Z (0, 1, 2, 4)
		bool SlideForwards;
		Vector3 Field19;
		Vector3 Field20;
		Vector3 ForwardDirection;
		Door* Field21;
		int32_t Field22; // Enum: None, Main, Secondary, PermanentLock
		void* HuntCollider; // BoxCollider
		void* ClothDoor; // ClothDoor
		Transform* Field23; // Transform
		float Field24;
		void* CollideWithColliders; // Collider[]
		float CloseDoorDistance;
		void* Field25; // UnityEvent
		void* Field26; // UnityEvent
		bool Field27;
		float LoopSoundVelocityThreshold;
		float LoopVolumeMultiplier;
		void* Field28; // HashSet<GameObject>
		float Field29;
		float Field30;
		float Field31; // const = 3f;
		float Field32; // const = 0.001f;
	};

	struct Door
	{
		void* Clazz;
		void* Monitor;
		DoorFields Fields;
	};

	struct DoorArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		Door* Vector[65535];
	};

	DECLARE_METHOD_POINTER(Door_DisableOrEnableCollider, void(*)(Door* door, bool collisionEnabled, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door",
	                       "DisableOrEnableCollider", 1);

	DECLARE_METHOD_POINTER(Door_DisableOrEnableDoor, void(*)(Door* door, bool a1, bool a2, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "DisableOrEnableDoor", 2);

	DECLARE_METHOD_POINTER(Door_LockDoorForTime, void(*)(Door* door, float time, bool locked, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "LockDoorForTime", 2);
}
