#include "Rasterizer.h"
#include "Device.h"
#include "DeviceContext.h"

void 
Rasterizer::init(Device device) {
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.AntialiasedLineEnable = false;

	HRESULT hr = S_OK;
	hr = device.CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);

	if (FAILED(hr)) {
		ERROR("Rasterizer", "init", "CHECK FOR CreateRasterizerState()");
	}
}

void 
Rasterizer::update() {
}

void 
Rasterizer::render(DeviceContext& deviceContext) {
	deviceContext.RSSetState(m_rasterizerState);
}

void 
Rasterizer::destroy() {
	SAFE_RELEASE(m_rasterizerState);
}
