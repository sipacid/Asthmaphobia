#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelController;

	struct GameControllerFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields; // MonoBehaviourPunCallbacks derived class field
		void* OnAllPlayersConnected; // UnityEvent
		void* OnPlayerSpawned; // ???
		void* OnGhostSpawned; // UnityEvent
		void* OnHuntStarted; // UnityEvent
		void* OnHuntEnded; // UnityEvent
		void* OnPlayerChangedRoom; // ???
		void* OnGhostChangedRoom; // ???
		void* OnLocalPlayerExitTruck; // UnityEvent
		void* OnLocalPlayerEnterTruck; // UnityEvent
		void* OnPlayerDied; // UnityEvent
		void* OnLocalPlayerDied; // ???
		void* OnFuseBoxUse; // UnityEvent
		void* OnPlayerEnteredOrExitTruck; // ???
		void* OnPhotoTaken; // ???
		void* OnPhotoRemoved; // ???
		void* OnPhotoVote; // ???
		float CurrentAverageSanity;
		void* SpeechRecognitionController; // SpeechRecognitionController
		LevelController* LevelController;
		void* MultiplayerController; // MultiplayerController
		bool AllPlayersAreConnected;
		int PlayerReadyCount;
		void* HandMaterial; // Material
		bool HasDrawnHighPriestess;
		void* SpeechRecognizer; // SpeechRecognizer
	};

	struct GameController
	{
		void* Clazz;
		void* Monitor;
		GameControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(GameController_Exit, void(*)(GameController* gameController, void* photoMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "GameController",
	                       "Exit", 1);

	DECLARE_METHOD_POINTER(GameController_GetAveragePlayerInsanity, float(*)(GameController* gameController, MethodInfo* methodInfo), "Assembly-CSharp", "", "GameController",
	                       "GetAveragePlayerInsanity", 0);
}
