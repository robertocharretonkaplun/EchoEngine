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
#pragma once
#include "PreRequisites.h"

class 
Device {
public:
	Device() = default;
	~Device()= default;

	void
	init();
	
	void 
	update();
	
	void 
	render();
	
	void 
	destroy();

	/// <summary>
	/// A function that creates a view of a resource, typically a texture, 
	/// that can be used as a render target for rendering operations. 
	/// A render target view allows the graphics pipeline to write rendering 
	/// output directly to the specified resource, enabling efficient rendering 
	/// and processing of visual data.
	/// </summary>
	/// <param name="pResource"></param>
	/// <param name="pDesc"></param>
	/// <param name="ppRTView"></param>
	/// <returns></returns>
	HRESULT 
	CreateRenderTargetView(ID3D11Resource* pResource,
												 const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
												 ID3D11RenderTargetView** ppRTView);

	HRESULT 
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
									const D3D11_SUBRESOURCE_DATA* pInitialData,
									ID3D11Texture2D** ppTexture2D);

	HRESULT 
	CreateDepthStencilView(ID3D11Resource* pResource,
												 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
												 ID3D11DepthStencilView** ppDepthStencilView);

	HRESULT 
	CreateVertexShader(const void* pShaderBytecode,
										 unsigned int BytecodeLength,
										 ID3D11ClassLinkage* pClassLinkage,
										 ID3D11VertexShader** ppVertexShader);

	HRESULT 
	CreateInputLayout(D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
										unsigned int NumElements,
										const void *pShaderBytecodeWithInputSignature,
										unsigned int BytecodeLength,
										ID3D11InputLayout **ppInputLayout);

	HRESULT
	CreatePixelShader(const void* pShaderBytecode,
										unsigned int BytecodeLength,
										ID3D11ClassLinkage* pClassLinkage,
										ID3D11PixelShader** ppPixelShader);

	HRESULT 
	CreateBuffer(const D3D11_BUFFER_DESC *pDesc,
							 const D3D11_SUBRESOURCE_DATA *pInitialData,
							 ID3D11Buffer **ppBuffer);

	HRESULT
	CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
										 ID3D11SamplerState** ppSamplerState);
public:
	ID3D11Device* m_device = nullptr;
};