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
