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
#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

void 
InputLayout::init(Device device, 
									std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, 
									ID3DBlob* VertexShaderData) {
	if (Layout.size() == 0) {
		ERROR("InputLayout", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout");
		exit(1);
	}
	else if (VertexShaderData == nullptr) {
		ERROR("InputLayout", "init", "CHECK FOR ID3DBlob* VertexShaderData");
		exit(1);
	}

	HRESULT hr = S_OK;

	hr = device.CreateInputLayout(Layout.data(),
													 Layout.size(),
													 VertexShaderData->GetBufferPointer(),
													 VertexShaderData->GetBufferSize(),
													 &m_inputLayout);

	if (FAILED(hr)) {
		ERROR("InputLayout", "init", "CHECK FOR CreateInputLayout()");
		exit(1);
	}
}

void 
InputLayout::update() {
}

void 
InputLayout::render(DeviceContext& deviceContext) {
	deviceContext.IASetInputLayout(m_inputLayout);
}

void 
InputLayout::destroy() {
	SAFE_RELEASE(m_inputLayout);
}
