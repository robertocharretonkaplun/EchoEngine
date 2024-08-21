#pragma once
#include "PreRequisites.h"
class Device;
class DeviceContext;

class 
BlendState {
public:
	BlendState() = default;
	~BlendState() = default;

	void
  init(Device device);

  void 
  update();
  
  void 
  render(DeviceContext& deviceContext);
  
  void 
  destroy();

private:
	ID3D11BlendState* m_blendState = nullptr;
};