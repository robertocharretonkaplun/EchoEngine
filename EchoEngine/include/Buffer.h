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
#include "Prerequisites.h"

class Device;
class DeviceContext;
class MeshComponent;

class 
Buffer {
public:
	Buffer() = default;
	~Buffer() = default;
  
  // Inicializa Vertex e Index Buffers 
	void 
  init(Device device, MeshComponent mesh, unsigned int bindFlag);

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