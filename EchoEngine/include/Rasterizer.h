#pragma once
#include "PreRequisites.h"
class Device;
class DeviceContext;

class 
Rasterizer {
public:
	Rasterizer()  = default;
	~Rasterizer() = default;

	void
  init(Device device);

  void 
  update();
  
  void 
  render(DeviceContext& deviceContext);
  
  void 
  destroy();

private:
  ID3D11RasterizerState* m_rasterizerState = nullptr;
};