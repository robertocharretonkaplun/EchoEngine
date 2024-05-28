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
public:
	ID3D11Device* m_device = nullptr;
};