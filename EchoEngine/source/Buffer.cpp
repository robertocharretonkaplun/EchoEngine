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
#include "Buffer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "MeshComponent.h"
#include "Buffer.h"
#include "Device.h"
#include "DeviceContext.h"

// Private method to create buffer
void 
Buffer::createBuffer(Device& device, 
                     D3D11_BUFFER_DESC& desc, 
                     D3D11_SUBRESOURCE_DATA* initData) {
  HRESULT hr = device.CreateBuffer(&desc, initData, &m_buffer);
  if (FAILED(hr)) {
    ERROR("Buffer", "createBuffer", "CHECK FOR method createBuffer()");
  }
}

void 
Buffer::init(Device device, MeshComponent mesh, unsigned int bindFlag) {
  if (device.m_device == nullptr) {
    ERROR("Buffer", "init", "CHECK FOR Device device");
  }

  // Validate mesh data based on bindFlag
  if ((bindFlag == D3D11_BIND_VERTEX_BUFFER && mesh.m_vertex.empty()) ||
    (bindFlag == D3D11_BIND_INDEX_BUFFER && mesh.m_index.empty())) {
    ERROR("Buffer", "init", "CHECK FOR Mesh mesh");
  }

  D3D11_BUFFER_DESC desc = {};
  D3D11_SUBRESOURCE_DATA InitData = {};

  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.CPUAccessFlags = 0;
  m_bindFlag = bindFlag;

  if (bindFlag == D3D11_BIND_VERTEX_BUFFER) {
    m_stride = sizeof(SimpleVertex);
    desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_vertex.size());
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    InitData.pSysMem = mesh.m_vertex.data();
  }
  else if (bindFlag == D3D11_BIND_INDEX_BUFFER) {
    m_stride = sizeof(unsigned int);
    desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_index.size());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    InitData.pSysMem = mesh.m_index.data();
  }

  createBuffer(device, desc, &InitData);
}

void 
Buffer::init(Device device, unsigned int ByteWidth) {
  if (device.m_device == nullptr || ByteWidth == 0) {
    ERROR("Buffer", "init", "CHECK FOR parameters");
  }

  m_stride = ByteWidth;

  D3D11_BUFFER_DESC desc = {};
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.ByteWidth = ByteWidth;
  desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  m_bindFlag = desc.BindFlags;

  createBuffer(device, desc, nullptr);
}

void 
Buffer::update(DeviceContext& deviceContext, 
               unsigned int DstSubresource, 
               const D3D11_BOX* pDstBox, 
               const void* pSrcData, 
               unsigned int SrcRowPitch, 
               unsigned int SrcDepthPitch) {
  deviceContext.UpdateSubresource(m_buffer, 
                                  DstSubresource, 
                                  pDstBox, 
                                  pSrcData, 
                                  SrcRowPitch, 
                                  SrcDepthPitch);
}

void 
Buffer::render(DeviceContext& deviceContext, 
               unsigned int StartSlot, 
               unsigned int NumBuffers) {
  switch (m_bindFlag) {
  case D3D11_BIND_VERTEX_BUFFER:
    deviceContext.IASetVertexBuffers(StartSlot, 
                                     NumBuffers, 
                                     &m_buffer, 
                                     &m_stride, 
                                     &m_offset);
    break;
  case D3D11_BIND_CONSTANT_BUFFER:
    deviceContext.m_deviceContext->VSSetConstantBuffers(StartSlot, 
                                                        NumBuffers, 
                                                        &m_buffer);
    break;
  default:
    ERROR("Buffer", "render", "CHECK FOR Unsupported BindFlag");
    break;
  }
}

void 
Buffer::render(DeviceContext& deviceContext, DXGI_FORMAT format) {
  if (m_bindFlag == D3D11_BIND_INDEX_BUFFER) {
    deviceContext.IASetIndexBuffer(m_buffer, format, m_offset);
  }
  else {
    ERROR("Buffer", "render", "CHECK FOR Unsupported BindFlag");  
  }
}

void 
Buffer::renderModel(DeviceContext& deviceContext, 
                    unsigned int StartSlot, 
                    unsigned int NumBuffers) {
  deviceContext.m_deviceContext->VSSetConstantBuffers(StartSlot, 
                                                      NumBuffers, 
                                                      &m_buffer);

  deviceContext.m_deviceContext->PSSetConstantBuffers(StartSlot, 
                                                      NumBuffers, 
                                                      &m_buffer);
}

void 
Buffer::destroy() {
  SAFE_RELEASE(m_buffer);
}
