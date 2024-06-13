#pragma once
#include "PreRequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

class 
ShaderProgram {
public:
	ShaderProgram() = default;
	~ShaderProgram() = default;

	void
  init(Device device, 
       std::string fileName, 
       std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  void 
  update();
  
  void 
  render(DeviceContext& deviceContext);
  
  void 
  destroy();

  HRESULT
  CompileShaderFromFile(char* szFileName, 
                        LPCSTR szEntryPoint, 
                        LPCSTR szShaderModel, 
                        ID3DBlob** ppBlobOut);

  void
  CreateVertexShader(Device device);

  void
  CreateInputLayout(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  void
  CreatePixelShader(Device device);

  void 
  CreateShader(Device device, void* shaderClass);

public:
  ID3D11VertexShader* m_VertexShader = nullptr;
  ID3D11PixelShader* m_PixelShader = nullptr;
  InputLayout m_inputLayout;
private:
  std::string m_shaderFileName;
  ID3DBlob* m_vertexShaderData = nullptr;
  ID3DBlob* m_pixelShaderData = nullptr;
};
