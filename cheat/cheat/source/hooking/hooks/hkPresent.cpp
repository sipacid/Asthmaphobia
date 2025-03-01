#include "source/common.h"
#include "source/hooking/hooking.h"
#include "source/menu/menu.h"

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_impl_win32.h"
#include "libraries/imgui/imgui_impl_dx11.h"

using namespace Asthmaphobia;

HRESULT __stdcall Hooks::HkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!menu.Initialized)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&renderer->Device))))
		{
			Renderer::Swapchain = pSwapChain;
			pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&Renderer::Device));
			Renderer::Device->GetImmediateContext(&Renderer::Context);

			DXGI_SWAP_CHAIN_DESC description;
			pSwapChain->GetDesc(&description);

			ImGui::CreateContext();
			Renderer::Window = description.OutputWindow;

			ImGui_ImplWin32_Init(Renderer::Window);
			ImGui_ImplDX11_Init(Renderer::Device, Renderer::Context);
			ImGui::GetIO().ImeWindowHandle = Renderer::Window;
			ImGui::LoadIniSettingsFromDisk((Helper::GetAsthmaphobiaDirectory() + "\\menu.ini").c_str());
			ImGui::GetIO().FontGlobalScale = dpiScale;

			ID3D11Texture2D* pBackBuffer;

			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));
			Renderer::Device->CreateRenderTargetView(pBackBuffer, nullptr, &Renderer::TargetView);
			pBackBuffer->Release();

			hooking->OriginalWndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Renderer::Window, GWLP_WNDPROC,
			                                                                      reinterpret_cast<LONG_PTR>(HkWndProc)));
			Menu::Initialize();
		}
		else
			return hooking->OriginalPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (menu.Open)
	{
		Menu::Render();
	}

	// destroying featureManager before this, will become nullptr
	if (globalRunning)
	{
		featureManager->OnDraw();
		Notifications::RenderNotifications();
	}

	ImGui::EndFrame();
	ImGui::Render();

	Renderer::Context->OMSetRenderTargets(1, &Renderer::TargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return hooking->OriginalPresent(pSwapChain, SyncInterval, Flags);
}
