#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

void 
Viewport::init(Window window) {
	if (window.m_hWnd == nullptr) {
		ERROR("Viewport", "init", "CHECK FOR Window window")
		exit(1);;
	}
	m_viewport.Width = (float)window.m_width;
	m_viewport.Height = (float)window.m_height;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
}

void 
Viewport::update() {
}

void 
Viewport::render(DeviceContext& deviceContext) {
	deviceContext.RSSetViewports(1, &m_viewport);
}

void 
Viewport::destroy() {
}
