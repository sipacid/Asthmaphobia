#pragma once
#include <cstdint>

#include "sdk.h"

namespace SDK
{
	struct PhysicsCharacterControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		RaycastHit GroundCheckHitInfo;
		Vector3 SurfaceNormal;
		float SlopeAngle;
		bool IsSurfaceWalkable;
		Vector3 InputVelocity;
		bool HasNewInput;
		float FallSpeed;
		int32_t RigidbodyLayerMask; // LayerMask
		int32_t PlayerLayer;
		void* SweepHits; // RaycastHit[]
		void* OverlapCapsuleColliders; // Collider[]
		RaycastHit PenetrationHitInfo;
		Vector3 P1;
		Vector3 P2;
		Rigidbody* Rigidbody;
		void* Collider; // CapsuleCollider
		int32_t MaxIterationCount;
		int32_t NumPenetrationProbes;
		float MinMoveDistance;
	};

	struct PhysicsCharacterController
	{
		void* Clazz;
		void* Monitor;
		PhysicsCharacterControllerFields Fields;
	};
}
