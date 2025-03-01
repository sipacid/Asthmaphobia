#pragma once
#include "source/common.h"
#include "hooks/hooks.h"
#include "libraries/detours/include/detours.h"

namespace Asthmaphobia
{
	class Hooking
	{
		friend Hooks;

	public:
		explicit Hooking();
		~Hooking();

		void AddHook(const std::string& functionName, PVOID* originalFunction, PVOID hookFunction);
		void ApplyHooks() const;

		Id3DPresent OriginalPresent{};
		WNDPROC OriginalWndproc{};

	private:
		std::vector<std::tuple<std::string, PVOID*, PVOID>> hooks_;
		void RemoveHooks() const;
	};

	inline Hooking* hooking{};
}
