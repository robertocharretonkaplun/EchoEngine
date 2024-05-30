#pragma once
#include "PreRequisites.h"

class 
DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() = default;

	void
	init();
	
	void 
	update();
	
	void 
	render();
	
	void 
	destroy();


private:

public:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};