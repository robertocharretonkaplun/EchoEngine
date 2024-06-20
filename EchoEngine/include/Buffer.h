#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class 
Buffer {
public:
	Buffer() = default;
	~Buffer() = default;
  
  // Inicializa Vertex e Index Buffers 
	void 
  init(Device device, Mesh mesh, unsigned int bindFlag);

  // Inicializa Constant Buffers
  void
  init(Device device, unsigned int ByteWidth);

  // Actualizamos la logica del Constant Buffer
  void
  update(DeviceContext& deviceContext, 
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);
  
  // Actualiza en render el Vertex 
  void 
  render(DeviceContext& deviceContext, 
         unsigned int StartSlot, 
         unsigned int NumBuffers);
  
  // Actualiza en render Index Buffer
  void
  render(DeviceContext& deviceContext, DXGI_FORMAT format);
  
  // Actualiza en render el constant Buffer
  void
  renderModel(DeviceContext& deviceContext, 
              unsigned int StartSlot, 
              unsigned int NumBuffers);

  void 
  destroy();

private:
  void 
  createBuffer(Device& device, 
               D3D11_BUFFER_DESC& desc, 
               D3D11_SUBRESOURCE_DATA* initData);

private:
	ID3D11Buffer* m_buffer = nullptr;
  unsigned int m_stride = 0;
  unsigned int m_offset = 0;
  unsigned int m_bindFlag = 0;
};