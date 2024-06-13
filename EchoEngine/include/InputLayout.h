#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class 
InputLayout {
public:
	InputLayout() = default;
	~InputLayout() = default;

	void
  init(Device device, 
       std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, 
       ID3DBlob* VertexShaderData);

  void 
  update();
  
  void 
  render(DeviceContext& deviceContext);
  
  void 
  destroy();

public:
	ID3D11InputLayout* m_inputLayout = nullptr;
};