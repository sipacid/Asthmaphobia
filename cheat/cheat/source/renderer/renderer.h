#pragma once
#include "source/common.h"
#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")

namespace Asthmaphobia
{
	using Id3DPresent = HRESULT(__stdcall*)(IDXGISwapChain* this_, UINT sync_, UINT flags_);

	class Renderer
	{
		const D3D_DRIVER_TYPE KDriverType[4] = {
			D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP
		};

		IDXGISwapChain* Swapchain{nullptr};
		ID3D11Device* Device{nullptr};
		ID3D11DeviceContext* Context{nullptr};
		ID3D11RenderTargetView* TargetView{nullptr};
		Id3DPresent PresentFunction{nullptr};

		bool GameResourcesInitialized{false};

	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;

		explicit Renderer();
		~Renderer();

		void SetGameResources(IDXGISwapChain* swapChain, ID3D11Device* device, ID3D11DeviceContext* context);
		bool CreateRenderTargetView();

		bool InitializeSwapChain();
		Id3DPresent GetPresent() const;

		IDXGISwapChain* GetSwapchain() const { return Swapchain; }
		ID3D11Device* GetDevice() const { return Device; }
		ID3D11DeviceContext* GetContext() const { return Context; }
		ID3D11RenderTargetView* GetTargetView() const { return TargetView; }

		void Cleanup();

		HWND Window{nullptr};
	};

	Renderer& GetRendererInstance();
}
