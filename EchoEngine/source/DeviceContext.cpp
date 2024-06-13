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
