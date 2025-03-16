#pragma once
#include "sdk.h"

namespace SDK
{
	struct Matrix4x4;
}

namespace SDK
{
	struct Camera
	{
	};

	DECLARE_METHOD_POINTER(Camera_Get_WorldToCameraMatrix, Matrix4x4(*)(Camera* camera, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Camera",
	                       "get_worldToCameraMatrix", 0);

	DECLARE_METHOD_POINTER(Camera_Get_ProjectionMatrix, Matrix4x4(*)(Camera* camera, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Camera",
	                       "get_projectionMatrix", 0);
}
