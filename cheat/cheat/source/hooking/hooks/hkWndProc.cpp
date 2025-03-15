#include "source/common.h"
#include "source/hooking/hooking.h"
#include "source/menu/menu.h"

#include "libraries/imgui/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace Asthmaphobia;

LRESULT __stdcall Hooks::HkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(Renderer::Window, &mPos);

	ImGui::GetIO().MousePos.x = mPos.x;
	ImGui::GetIO().MousePos.y = mPos.y;

	if (uMsg == WM_KEYUP && wParam == VK_INSERT)
	{
		menu.Toggle();
	}

	if (menu.Open)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(GetHookingInstance().OriginalWndproc, hWnd, uMsg, wParam, lParam);
}
