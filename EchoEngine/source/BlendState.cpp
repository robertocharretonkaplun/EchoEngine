#include "BlendState.h"
#include "Device.h"
#include "DeviceContext.h"

void 
BlendState::init(Device device) {
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = S_OK;
	hr = device.CreateBlendState(&blendDesc, &m_blendState);

	if (FAILED(hr)) {
		ERROR("Rasterizer", "init", "CHECK FOR CreateBlendState()");
	}
}

void 
BlendState::update() {
}

void 
BlendState::render(DeviceContext& deviceContext) {
	FLOAT blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
	unsigned int sampleMask = 0xffffffff;
	deviceContext.OMSetBlendState(m_blendState, blendFactor, sampleMask);
}

void 
BlendState::destroy() {
	SAFE_RELEASE(m_blendState);
}
