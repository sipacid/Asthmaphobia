#include "hooking.h"

using namespace Asthmaphobia;

Hooking::Hooking()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	hooking = this;
}

Hooking::~Hooking()
{
	this->RemoveHooks();
	SetWindowLongPtr(renderer->Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(this->OriginalWndproc));

	hooking = nullptr;
}

void Hooking::AddHook(const std::string& functionName, PVOID* originalFunction, PVOID hookFunction)
{
	this->hooks_.emplace_back(functionName, originalFunction, hookFunction);
}

void Hooking::ApplyHooks() const
{
	for (const auto& hook : this->hooks_)
	{
		std::ostringstream oss;
		oss << "Applying hook: " << std::get<0>(hook) << "\n";
		LOG_DEBUG(oss.str());

		DetourAttach(std::get<1>(hook), std::get<2>(hook));
	}
	DetourTransactionCommit();
}

void Hooking::RemoveHooks() const
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	for (const auto& hook : this->hooks_)
	{
		std::ostringstream oss;
		oss << "Restoring hook: " << std::get<0>(hook) << "\n";
		LOG_DEBUG(oss.str());

		DetourDetach(std::get<1>(hook), std::get<2>(hook));
	}
	DetourTransactionCommit();
}
