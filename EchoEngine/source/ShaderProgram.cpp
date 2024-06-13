#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

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
