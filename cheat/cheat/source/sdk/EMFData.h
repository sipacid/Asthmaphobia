#pragma once
#include "sdk.h"

namespace SDK
{
	struct EMFData;
	struct LineRenderer;

	struct EMFDataFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		LineRenderer* Rend;
		void* Screen; // BrokenScreen
		void* GlitchText; // GlitchyText[]
		void* EMFSpots; // List<EMF.???>
		Transform* StartingPos;
	};

	struct EMFData
	{
		void* Clazz;
		void* Monitor;
		EMFDataFields Fields;
	};

	DECLARE_METHOD_POINTER(EMFData_Start, void (*)(EMFData* emfData, MethodInfo* methodInfo), "Assembly-CSharp", "", "EMFData", "Start", 0);
}
