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
#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "DepthStencilView.h"

void 
RenderTargetView::init(Device device, Texture backBuffer, DXGI_FORMAT Format) {
	if (device.m_device == nullptr)	{
		ERROR("RenderTargetView", "init", "CHECK FOR Device device")
		exit(1);
	}
	else if (backBuffer.m_texture == nullptr) {
		ERROR("RenderTargetView", "init", "CHECK FOR Texture backBuffer")
		exit(1);
	}

	HRESULT hr = S_OK;
	
	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = Format;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = device.CreateRenderTargetView(backBuffer.m_texture, 
																		 &desc, 
																		 &m_renderTargetView);

	if (FAILED(hr)) {
		ERROR("RenderTargetView", "init", "CHECK FOR CreateRenderTargetView()")
		exit(1);
	}
}

void 
RenderTargetView::update() {
}

void 
RenderTargetView::render(DeviceContext& deviceContext, 
												 DepthStencilView& depthStencilView, 
												 unsigned int numViews, 
												 float ClearColor[4]) {
	deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
	deviceContext.m_deviceContext->OMSetRenderTargets(numViews, 
																										&m_renderTargetView, 
																										depthStencilView.m_depthStencilView);
}

void 
RenderTargetView::destroy() {
	SAFE_RELEASE(m_renderTargetView);
}
