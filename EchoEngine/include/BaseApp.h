#pragma once
#include "PreRequisites.h"
#include "EETimer.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "SwapChain.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "ModelLoader.h"
#include "Actor.h"
#include "UserInterface.h"

class 
BaseApp {
public:
	BaseApp() = default;
	~BaseApp() = default;

	HRESULT
	init();
	
	void 
	update();
	
	void 
	render();
	
	void 
	destroy();

	int 
	run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc);

	void 
	CreateGrid(int width, int depth, float spacing);
private:
	Window															m_window;
	EETimer															m_timer;
	Device															m_device;
	DeviceContext												m_deviceContext;
	SwapChain														m_swapchain;
	Texture															m_backBuffer;
	Texture															m_depthStencil;
	DepthStencilView										m_depthStencilView;
	RenderTargetView										m_renderTargetView;
	Viewport														m_viewport;
	ShaderProgram												m_shaderProgram;
	Buffer															m_CBBufferNeverChanges;
	Buffer															m_CBBufferChangeOnResize;
	ModelLoader													m_model;
	UserInterface												m_userInterface;

	XMMATRIX                            m_View;
	XMMATRIX                            m_Projection;
	XMFLOAT4                            m_vMeshColor;

	// Grid Actor
	MeshComponent												MC;
	EngineUtilities::TSharedPointer<Actor> AGrid;

	// Vela Actor
	EngineUtilities::TSharedPointer<Actor> AVela;
	std::vector<Texture>								gridTexs;

	Texture m_default;
	std::vector<Texture>								modelTextures;

	CBNeverChanges											cbNeverChanges;
	CBChangeOnResize										cbChangesOnResize;
	CBChangesEveryFrame									cb;
};
