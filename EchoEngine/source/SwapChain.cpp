/*
 * MIT License
 *
 * Copyright (c) 2024 Roberto Charreton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * In addition, any project or software that uses this library or class must include
 * the following acknowledgment in the credits:
 *
 * "This project uses software developed by Roberto Charreton and Attribute Overload."
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include "SwapChain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Window.h"
#include "Texture.h"	

void
SwapChain::init(Device& device,
								DeviceContext& deviceContext,
								Texture& backBuffer,
								Window window) {
	// Check if window resource exists
	if (window.m_hWnd == nullptr) {
		ERROR("SwapChain", "init", "CHECK FOR Window window")
			exit(1);
	}

	unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
	};
	unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT hr = S_OK;

	// Create device and device context (no swap chain yet)
	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr,
			m_driverType,
			nullptr,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&device.m_device,
			&m_featureLevel,
			&deviceContext.m_deviceContext);
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		ERROR("SwapChain", "init", "CHECK FOR D3D11CreateDevice()")
			exit(1);
	}
	m_sampleCount = 4;
	m_qualityLevels = 0;

	// Check if MSAA is supported
	hr = device.m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_sampleCount, &m_qualityLevels);
	if (FAILED(hr) || m_qualityLevels == 0) {
		ERROR("SwapChain", "init", "MSAA not supported or invalid quality level");
		exit(1);
	}

	// Setup swap chain description
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = window.m_width;
	sd.BufferDesc.Height = window.m_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window.m_hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Set MSAA options in swap chain descriptor
	sd.SampleDesc.Count = m_sampleCount;
	sd.SampleDesc.Quality = m_qualityLevels - 1;  // Use maximum quality

	// Create the swap chain
	hr = device.m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgiDevice));
	if (FAILED(hr)) {
		ERROR("SwapChain", "init", "CHECK FOR QueryInterface IDXGIDevice")
			exit(1);
	}
	hr = m_dxgiDevice->GetAdapter(&m_dxgiAdapter);
	if (FAILED(hr)) {
		ERROR("SwapChain", "init", "CHECK FOR GetAdapter IDXGIAdapter")
			exit(1);
	}
	hr = m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_dxgiFactory));
	if (FAILED(hr)) {
		ERROR("SwapChain", "init", "CHECK FOR GetParent IDXGIFactory")
			exit(1);
	}
	hr = m_dxgiFactory->CreateSwapChain(device.m_device, &sd, &m_swapChain);
	if (FAILED(hr)) {
		ERROR("SwapChain", "init", "CHECK FOR CreateSwapChain")
			exit(1);
	}

	// Create a render target view
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.m_texture);
	if (FAILED(hr)) {
		ERROR("SwapChain", "init", "CHECK FOR m_swapChain->GetBuffer()")
			exit(1);
	}
}


void 
SwapChain::update() {
}

void 
SwapChain::render() {
}

void 
SwapChain::destroy() {
	SAFE_RELEASE(m_swapChain);
}

void 
SwapChain::present() {
	m_swapChain->Present(0, 0);
}
