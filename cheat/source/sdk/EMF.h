#pragma once
#include "sdk.h"

namespace SDK
{
	enum class EMFType : int32_t
	{
		Interaction,
		ObjectMoved,
		WindowKnock,
		MidGhostWrite,
		BreakerSwitch,
		Planchette,
		RockingChair,
		GeneralIntEffect,
		LightSwitched,
		SoundEffect,
		CrucifixFire
	};
}
