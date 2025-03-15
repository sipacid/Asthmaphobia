#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelController;

	struct GameControllerFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields; // MonoBehaviourPunCallbacks derived class field
		void* Field0; // UnityEvent
		void* Field01; // ???
		void* Field1; // UnityEvent
		void* Field2; // UnityEvent
		void* Field3; // UnityEvent
		void* Field31; // ???
		void* Field32; // ???
		void* Field4; // UnityEvent
		void* Field5; // UnityEvent
		void* Field51; // ???
		void* Field6; // UnityEvent
		void* Field7; // ???
		void* Field8; // ???
		void* Field9; // ???
		void* Field10; // ???
		void* Field101; // ???
		float Field11;
		void* Field12; // SpeechRecognitionController
		LevelController* LevelController; // LevelController
		void* Field14; // MultiplayerController
		bool Field15;
		int Field16;
		void* Field17; // Material
		bool Field18;
		void* Field19; // SpeechRecognizer
	};

	struct GameController
	{
		void* Clazz; // GameControllerClass
		void* Monitor; // MonitorData
		GameControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(GameController_Exit, void(*)(GameController* gameController, void* photoMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "GameController", "Exit", 1);
	DECLARE_METHOD_POINTER(GameController_GetAveragePlayerInsanity, float(*)(GameController* gameController, MethodInfo* methodInfo), "Assembly-CSharp", "", "GameController", "GetAveragePlayerInsanity", 0);
}
