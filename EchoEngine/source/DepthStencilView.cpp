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
#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

void 
DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) {
	if (device.m_device == nullptr) {
		ERROR("DepthStencilView", "init", "CHECK FOR Device device");
		exit(1);
	}
	else if (depthStencil.m_texture == nullptr) {
		ERROR("DepthStencilView", "init", "CHECK FOR ID3D11Resource* depthStencil");
		exit(1);
	}
	HRESULT hr = S_OK;
	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	memset(&descDSV, 0, sizeof(descDSV));
	descDSV.Format = format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_depthStencilView);
	
	if (FAILED(hr)) {
		ERROR("DepthStencilView", "init", "CHECK FOR CreateDepthStencilView()");
		exit(1);
	}
}

void
DepthStencilView::render(DeviceContext& deviceContext) {
	deviceContext.m_deviceContext->ClearDepthStencilView(m_depthStencilView, 
																											 D3D11_CLEAR_DEPTH, 
																											 1.0f, 
																											 0);
}

void 
DepthStencilView::destroy() {
	SAFE_RELEASE(m_depthStencilView);
}
