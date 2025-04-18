#pragma once
#include "sdk.h"

namespace SDK
{
	struct Door;

	struct DoorFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool Locked;
		bool Closed;
		bool HasBeenGrabbedByPlayer;
		void* DoorLockClips; // AudioClip[]
		void* DoorUnlockClips; // AudioClip[]
		void* DoorClosedClips; // AudioClip[]
		void* DoorOpenClips; // AudioClip[]
		float ClosedVolume;
		float UnlockVolume;
		void* LoopSource; // AudioSource
		void* OcclusionPortal; // OcclusionPortal
		void* DeadPostProcessVolume; // Volume
		bool HasBeenUnlocked;
		bool CanBeGrabbed;
		bool CanBeOpenedByGhostsInHunts;
		void* View; // PhotonView
		Rigidbody* Body;
		void* PhotonInteract; // PhotonObjectInteract
		void* Fingerprint; // Fingerprint
		Collider* Col;
		float ClosedYRot;
		void* Noise; // Noise
		void* Hinge; // ConfigurableJoint
		void* Rends; // Renderer[]
		bool IsDoorRotationBackwards;
		int32_t DoorType; // Enum: hinge, slide, cloth
		int32_t DoorMaterialType; // Enum: wood, Metal, Locker, Fabric
		int32_t SlideAxis; // Enum: None, X, Y, Z (0, 1, 2, 4)
		bool SlideForwards;
		Vector3 StartLocalPosition;
		Vector3 StartWorldPosition;
		Vector3 ForwardDirection;
		Door* OtherDoor;
		Door* DoubleDoor;
		int32_t KeyType; // Enum: None, Main, Secondary, PermanentLock
		void* HuntCollider; // BoxCollider
		void* ClothDoor; // ClothDoor
		Transform* ClothAnchor; // Transform
		float MaxDistanceFromAnchor;
		void* CollideWithColliders; // Collider[]
		float CloseDoorDistance;
		void* OnDoorOpened; // UnityEvent
		void* OnDoorClosed; // UnityEvent
		bool IsLockedForTime;
		float LoopSoundVelocityThreshold;
		float LoopVolumeMultiplier;
		void* PlayerContacts; // HashSet<GameObject>
		float Speed;
		float AngularSpeed;
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
