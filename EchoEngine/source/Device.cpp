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
#include "Device.h"

void Device::init()
{
}

void Device::update()
{
}

void Device::render()
{
}

void 
Device::destroy() {
	SAFE_RELEASE(m_device);
}

HRESULT 
Device::CreateRenderTargetView(ID3D11Resource* pResource, 
															const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
															ID3D11RenderTargetView** ppRTView) {
	HRESULT hr = S_OK;

	// Check if the resource and RTView exist
	if (pResource != nullptr || ppRTView != nullptr) {
		hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);
		MESSAGE("Device","CreateRenderTargetView", "OK")
	}
	else {
		ERROR("Device", "CreateRenderTargetView", "CHECK FOR CREATION METHOD")
		exit(1);
	}
	return hr;
}

HRESULT 
Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, 
												const D3D11_SUBRESOURCE_DATA* pInitialData, 
												ID3D11Texture2D** ppTexture2D) {
	HRESULT hr = S_OK;
	// Check if the descriptor of the texture and the texture exist
	if (pDesc != nullptr || ppTexture2D != nullptr) {
		hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
		MESSAGE("Device", "CreateTexture2D", "OK")
	}
	else {
		ERROR("Device", "CreateTexture2D", "CHECK FOR CREATION METHOD")
		exit(1);
	}
	return hr;
}

HRESULT 
Device::CreateDepthStencilView(ID3D11Resource* pResource, 
															 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, 
															 ID3D11DepthStencilView** ppDepthStencilView) {
	HRESULT hr = S_OK;
	if (pResource == nullptr) {
		ERROR("Device", "CreateDepthStencilView", "CHECK FOR ID3D11Resource* pResource")
		exit(1);
	}
	else if (ppDepthStencilView == nullptr) {
		ERROR("Device", "CreateDepthStencilView", "CHECK FOR ID3D11DepthStencilView** ppDepthStencilView")
		exit(1);
	}
	else {
		hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
		MESSAGE("Device", "CreateDepthStencilView", "OK")
	}
	return hr;
}

HRESULT 
Device::CreateVertexShader(const void* pShaderBytecode, 
													 unsigned int BytecodeLength, 
													 ID3D11ClassLinkage* pClassLinkage, 
													 ID3D11VertexShader** ppVertexShader) {
	HRESULT hr = S_OK;
	if (pShaderBytecode == nullptr) {
		ERROR("Device", "CreateVertexShader", "CHECK FOR const void* pShaderBytecode")
		exit(1);
	}
	else if (ppVertexShader == nullptr) {
		ERROR("Device", "CreateVertexShader", "CHECK FOR ID3D11VertexShader** ppVertexShader")
		exit(1);
	}
	else {
		hr = m_device->CreateVertexShader(pShaderBytecode,
																			BytecodeLength,
																			pClassLinkage,
																			ppVertexShader);
		MESSAGE("Device", "CreateVertexShader", "OK")
	}
	return hr;
}

HRESULT 
Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, 
													unsigned int NumElements, 
													const void* pShaderBytecodeWithInputSignature, 
													unsigned int BytecodeLength, 
													ID3D11InputLayout** ppInputLayout) {
	HRESULT hr = S_OK;
	if (pInputElementDescs == nullptr) {
		ERROR("Device", "CreateInputLayout", "CHECK FOR const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs")
		exit(1);
	}
	else if (pShaderBytecodeWithInputSignature == nullptr) {
		ERROR("Device", "CreateInputLayout", "CHECK FOR const void* pShaderBytecodeWithInputSignature")
		exit(1);
	}
	else if (ppInputLayout == nullptr) {
		ERROR("Device", "CreateInputLayout", "CHECK FOR ID3D11InputLayout** ppInputLayout")
		exit(1);
	}
	else {
		hr = m_device->CreateInputLayout(pInputElementDescs,
			NumElements,
			pShaderBytecodeWithInputSignature,
			BytecodeLength,
			ppInputLayout);
		MESSAGE("Device", "CreateInputLayout", "OK")
	}
	return hr;
}

HRESULT 
Device::CreatePixelShader(const void* pShaderBytecode, 
													unsigned int BytecodeLength, 
													ID3D11ClassLinkage* pClassLinkage, 
													ID3D11PixelShader** ppPixelShader) {
	HRESULT hr = S_OK;

	if (pShaderBytecode == nullptr) {
		ERROR("Device", "CreatePixelShader", "CHECK FOR const void* pShaderBytecode")
		exit(1);
	}
	else if (ppPixelShader == nullptr) {
		ERROR("Device", "CreatePixelShader", "CHECK FOR ID3D11PixelShader** ppPixelShader")
		exit(1);
	}
	else {
		hr = m_device->CreatePixelShader(pShaderBytecode,
			BytecodeLength,
			pClassLinkage,
			ppPixelShader);
		MESSAGE("Device", "CreatePixelShader", "OK")
	}
	return hr;
}

HRESULT 
Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, 
										 const D3D11_SUBRESOURCE_DATA* pInitialData, 
										 ID3D11Buffer** ppBuffer) {
	HRESULT hr = S_OK;

	if (pDesc == nullptr) {
		ERROR("Device", "CreateBuffer", "CHECK FOR const D3D11_BUFFER_DESC* pDesc")
		exit(1);
	}
	else if (ppBuffer == nullptr) {
		ERROR("Device", "CreateBuffer", "CHECK FOR ID3D11Buffer** ppBuffer")
		exit(1);
	}
	else {
		hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
		MESSAGE("Device", "CreateBuffer", "OK")
	}

	return hr;
}

HRESULT 
Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, 
													ID3D11SamplerState** ppSamplerState) {
	HRESULT hr = S_OK;

	if (pSamplerDesc == nullptr) {
		ERROR("Device", "CreateSamplerState", "CHECK FOR const D3D11_SAMPLER_DESC* pSamplerDesc")
		exit(1);
	}
	else if (ppSamplerState == nullptr) {
		ERROR("Device", "CreateSamplerState", "CHECK FOR ID3D11SamplerState** ppSamplerState")
		exit(1);
	}
	else {
		hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
		MESSAGE("Device", "CreateSamplerState", "OK")
	}

	return hr;
}
