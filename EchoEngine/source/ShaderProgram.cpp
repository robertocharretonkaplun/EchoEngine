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
#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

void 
ShaderProgram::init(Device device, 
                    std::string fileName, 
                    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
	if (device.m_device == nullptr) {
		ERROR("ShaderProgram", "init", "CHECK FOR Device device");
		exit(1);
	}
	else if (Layout.size() <= 1) {
		ERROR("ShaderProgram", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout.size()");
		exit(1);
	}
	// Store the shade file name
	m_shaderFileName = fileName;
	// Create the vertex shader
	CreateShader(device, ShaderType::VERTEX_SHADER);
	// Create the Input Layout
	CreateInputLayout(device, Layout);
	// Create the pixel shader
	CreateShader(device, ShaderType::PIXEL_SHADER);
}

void 
ShaderProgram::update() {
}

void 
ShaderProgram::render(DeviceContext& deviceContext) {
	// Establecer el InputLayout
	m_inputLayout.render(deviceContext);
	// // Establecer los shaders
	deviceContext.VSSetShader(m_VertexShader, nullptr, 0);
	deviceContext.PSSetShader(m_PixelShader, nullptr, 0);
}

void 
ShaderProgram::destroy() {
	SAFE_RELEASE(m_VertexShader);
	m_inputLayout.destroy();
	SAFE_RELEASE(m_PixelShader);
}

HRESULT
ShaderProgram::CompileShaderFromFile(char* szFileName, 
																		 LPCSTR szEntryPoint, 
																		 LPCSTR szShaderModel, 
																		 ID3DBlob** ppBlobOut) {
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

void 
ShaderProgram::CreateInputLayout(Device device, 
																 std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
	m_inputLayout.init(device, Layout, m_vertexShaderData);
	m_vertexShaderData->Release();
}

void 
ShaderProgram::CreateShader(Device device, ShaderType type) {
  HRESULT hr = S_OK;
  ID3DBlob* shaderData = nullptr;
  const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";
  const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0";

  // Compile the shader
  hr = CompileShaderFromFile(m_shaderFileName.data(), 
														 shaderEntryPoint, 
														 shaderModel, 
														 &shaderData);
  if (FAILED(hr)) {
    MessageBox(nullptr, "The FX file cannot be compiled. Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
    ERROR("ShaderProgram", "CreateShader", "CHECK FOR CompileShaderFromFile()");
    exit(1);
  }

  // Create the shader
  if (type == PIXEL_SHADER) {
    hr = device.CreatePixelShader(shaderData->GetBufferPointer(),
																	shaderData->GetBufferSize(),
																	nullptr,
																	&m_PixelShader);
  }
  else {
    hr = device.CreateVertexShader(shaderData->GetBufferPointer(),
																	 shaderData->GetBufferSize(),
																	 nullptr,
																	 &m_VertexShader);
  }

  if (FAILED(hr)) {
    shaderData->Release();
    ERROR("ShaderProgram", "CreateShader", "CHECK FOR device.CreateShader()");
    exit(1);
  }

  // Store the compiled shader data
  if (type == PIXEL_SHADER) {
    m_pixelShaderData = shaderData;
  }
  else {
    m_vertexShaderData = shaderData;
  }
}
