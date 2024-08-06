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
