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
#include "DeviceContext.h"

void 
DeviceContext::destroy() {
	SAFE_RELEASE(m_deviceContext);
}

void 
DeviceContext::RSSetViewports(unsigned int NumViewports, 
															const D3D11_VIEWPORT* pViewports) {
	if (pViewports == nullptr) {
		ERROR("DeviceContext", "RSSetViewports", "CHECK FOR const D3D11_VIEWPORT* pViewports")
		exit(1);
	}
	else {
		m_deviceContext->RSSetViewports(NumViewports, pViewports);
	}
}

void 
DeviceContext::PSSetShaderResources(unsigned int StartSlot, 
																		unsigned int NumViews, 
																		ID3D11ShaderResourceView* const* ppShaderResourceViews) {
	if (ppShaderResourceViews == nullptr) {
		ERROR("DeviceContext", "PSSetShaderResources", "CHECK FOR ID3D11ShaderResourceView* const* ppShaderResourceViews")
		exit(1);
	}
	else {
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void 
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
	if (pInputLayout == nullptr) {
		ERROR("DeviceContext", "IASetInputLayout", "CHECK FOR ID3D11InputLayout* pInputLayout");
		exit(1);
	}
	else {
		m_deviceContext->IASetInputLayout(pInputLayout);
	}
}

void 
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, 
													 ID3D11ClassInstance* const* ppClassInstances, 
													 unsigned int NumClassInstances) {
	if (pVertexShader == nullptr)	{
		ERROR("DeviceContext", "VSSetShader", "CHECK FOR ID3D11VertexShader* pVertexShader");
		exit(1);
	}
	else {
		m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
	}
}

void 
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, 
													 ID3D11ClassInstance* const* ppClassInstances, 
													 unsigned int NumClassInstances) {
	if (pPixelShader == nullptr) {
		ERROR("DeviceContext", "PSSetShader", "CHECK FOR ID3D11PixelShader* pPixelShader");
		exit(1);
	}
	else {
		m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
	}
}

void 
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, 
															   unsigned int DstSubresource, 
															   const D3D11_BOX* pDstBox, 
															   const void* pSrcData, 
															   unsigned int SrcRowPitch, 
															   unsigned int SrcDepthPitch) {
	m_deviceContext->UpdateSubresource(pDstResource,
																		 DstSubresource, 
																		 pDstBox, 
																		 pSrcData, 
																		 SrcRowPitch, 
																		 SrcDepthPitch);
}

void 
DeviceContext::IASetVertexBuffers(unsigned int StartSlot, 
																	unsigned int NumBuffers, 
																	ID3D11Buffer* const* ppVertexBuffers, 
																	const unsigned int* pStrides, 
																	const unsigned int* pOffsets) {
	m_deviceContext->IASetVertexBuffers(StartSlot, 
																			NumBuffers, 
																			ppVertexBuffers, 
																			pStrides, 
																			pOffsets);
}

void 
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, 
																DXGI_FORMAT Format, 
																unsigned int Offset) {
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void 
DeviceContext::PSSetSamplers(unsigned int StartSlot, 
														 unsigned int NumSamplers, 
														 ID3D11SamplerState* const* ppSamplers) {
	if (ppSamplers == nullptr) {
		ERROR("DeviceContext", "PSSetSamplers", "CHECK FOR ID3D11SamplerState* const* ppSamplers");
	}
	else {
		m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
	}
}
