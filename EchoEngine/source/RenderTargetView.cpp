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
