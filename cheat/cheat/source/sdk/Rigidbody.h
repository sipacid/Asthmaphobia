#pragma once
#include "sdk.h"

namespace SDK
{
	enum class RigidbodyConstraints : int32_t
	{
		None = 0,
		FreezePositionX = 2,
		FreezePositionY = 4,
		FreezePositionZ = 8,
		FreezePosition = 14,
		FreezeRotationX = 16,
		FreezeRotationY = 32,
		FreezeRotationZ = 64,
		FreezeRotation = 112,
		FreezeAll = 126
	};

	struct Rigidbody
	{
	};

	DECLARE_METHOD_POINTER(Rigidbody_Set_IsKinematic, void(*)(Rigidbody* rigidbody, bool isKinematic, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine",
	                       "Rigidbody", "set_isKinematic", 1);

	DECLARE_METHOD_POINTER(Rigidbody_Get_Constraints, RigidbodyConstraints(*)(Rigidbody* rigidbody, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine",
	                       "Rigidbody", "get_constraints", 0);

	DECLARE_METHOD_POINTER(Rigidbody_Set_Constraints, void(*)(Rigidbody* rigidbody, RigidbodyConstraints contraints, MethodInfo* methodInfo), "UnityEngine.PhysicsModule",
	                       "UnityEngine", "Rigidbody", "set_constraints", 1);
}
