#pragma once
#include "source/common.h"

namespace Asthmaphobia
{
	class Menu
	{
	public:
		static void Initialize();
		static void Render();
		void Toggle();

		bool Initialized;
		bool Open;

	private:
		SDK::CursorLockMode PreviousCursorLockMode;
	};

	inline Menu menu;
}
