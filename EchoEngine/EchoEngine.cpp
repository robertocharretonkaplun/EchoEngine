//--------------------------------------------------------------------------------------
// File: EchoEngine.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "SwapChain.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "ModelLoader.h"
//#include "fbxsdk.h"
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

Window															g_window;
Device															g_device;
DeviceContext												g_deviceContext;
SwapChain														g_swapchain;
Texture															g_backBuffer;
Texture															g_depthStencil;
DepthStencilView										g_depthStencilView;
RenderTargetView										g_renderTargetView;
Viewport														g_viewport;
ShaderProgram												g_shaderProgram;
//Buffer                              g_vertexBuffer;
std::vector<Buffer>                 g_vertexBuffers;
//Buffer                              g_indexBuffer;
std::vector<Buffer>                 g_indexBuffers;
Buffer															g_CBBufferNeverChanges;
Buffer															g_CBBufferChangeOnResize;
Buffer															g_CBBufferChangesEveryFrame;
Texture															g_modelTexture;
SamplerState												g_sampler;
ModelLoader													g_model;


XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

Mesh																g_mesh;

std::vector<Texture> modelTextures;

CBNeverChanges cbNeverChanges;
CBChangeOnResize cbChangesOnResize;
CBChangesEveryFrame cb;
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();
void Update(float DeltaTime);


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//baseapp.run();
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(g_window.init(hInstance, nCmdShow, WndProc)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Update our time
			static float t = 0.0f;
			if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
			{
				t += (float)XM_PI * 0.0125f;
			}
			else
			{
				static DWORD dwTimeStart = 0;
				DWORD dwTimeCur = GetTickCount();
				if (dwTimeStart == 0)
					dwTimeStart = dwTimeCur;
				t = (dwTimeCur - dwTimeStart) / 1000.0f;
			}
			Update(t);
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}



//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	// Create Swapchain
	g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);

	// Create render target view
	g_renderTargetView.init(g_device, 
													g_backBuffer, 
													DXGI_FORMAT_R8G8B8A8_UNORM);

	// Create depth stencil texture
	g_depthStencil.init(g_device, 
											g_window.m_width, 
											g_window.m_height, 
											DXGI_FORMAT_D24_UNORM_S8_UINT, 
											D3D11_BIND_DEPTH_STENCIL);
	
	// Create the depth stencil view
	g_depthStencilView.init(g_device, 
													g_depthStencil, 
													DXGI_FORMAT_D24_UNORM_S8_UINT);

	
	// Setup the viewport
	g_viewport.init(g_window);

	// Define the input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	D3D11_INPUT_ELEMENT_DESC position;
	position.SemanticName = "POSITION";
	position.SemanticIndex = 0;
	position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	position.InputSlot = 0;
	position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	position.InstanceDataStepRate = 0;
	Layout.push_back(position);

	D3D11_INPUT_ELEMENT_DESC texcoord;
	texcoord.SemanticName = "TEXCOORD";
	texcoord.SemanticIndex = 0;
	texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
	texcoord.InputSlot = 0;
	texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texcoord.InstanceDataStepRate = 0;
	Layout.push_back(texcoord);

	g_shaderProgram.init(g_device, "EchoEngine.fx", Layout);

	// Load Model
	g_model.LoadModel("Models/makeshift.fbx");

	for (auto& mesh : g_model.meshes) {
		// Crear vertex buffer
		Buffer vertexBuffer;
		vertexBuffer.init(g_device, mesh, D3D11_BIND_VERTEX_BUFFER);
		g_vertexBuffers.push_back(vertexBuffer);

		// Crear index buffer
		Buffer indexBuffer;
		indexBuffer.init(g_device, mesh, D3D11_BIND_INDEX_BUFFER);
		g_indexBuffers.push_back(indexBuffer);

		// Cargar la textura asociada con esta malla
		//Texture texture;
		//std::string texturePath = "Textures/" + mesh.name + ".dds";
		//texture.init(g_device, texturePath.c_str());
		//g_textures.push_back(texture);
	}

	// Create vertex buffer
	//g_mesh.name = "MakeShift";
	//g_mesh.vertex = g_model.GetVertices();
	//g_mesh.numVertex = static_cast<unsigned int>(g_mesh.vertex.size());

	// Create vertex buffer
	//g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);

	// Create index buffer
	//g_mesh.index = g_model.GetIndices();
	
	//g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());

	//g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);

	// Inicialización de Constant Buffers
	g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

	g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

	g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));

	// Load the Textures from the model
	//std::vector<std::string> textureFileNames = g_model.GetTextureFileNames();
	
	//for (const auto& textureFileName : textureFileNames) {
	//	Texture texture;
	//	if (!textureFileName.empty()) {
	//		texture.init(g_device, textureFileName.c_str());
	//	}
	//	else {
	//		// Load a default texture or handle error
	//		texture.init(g_device, "seafloor.dds");
	//	}
	//	modelTextures.push_back(texture);
	//}
	Texture Head_Diffuse;
	Head_Diffuse.init(g_device, "Textures/Head_Diffuse.dds");
	
	Texture Torso_Diffuse;
	Torso_Diffuse.init(g_device, "Textures/Torso_Diffuse.dds");
	
	Texture Legs_Diffuse;
	Legs_Diffuse.init(g_device, "Textures/Legs_Diffuse.dds");
	
	Texture Tanks_Diffuse;
	Tanks_Diffuse.init(g_device, "Textures/Tanks_Diffuse.dds");

	modelTextures.push_back(Head_Diffuse);
	modelTextures.push_back(Legs_Diffuse);
	modelTextures.push_back(Torso_Diffuse);
	modelTextures.push_back(Tanks_Diffuse);
	// Load the Texture
	//g_modelTexture.init(g_device, "seafloor.dds");

	// Create the sample state
	g_sampler.init(g_device);

	// Initialize the world matrices
	g_World = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	
	cbNeverChanges.mView = XMMatrixTranspose(g_View);

	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

	g_sampler.destroy();
	g_modelTexture.destroy();
	g_CBBufferNeverChanges.destroy();
	g_CBBufferChangeOnResize.destroy();
	g_CBBufferChangesEveryFrame.destroy();
	//g_vertexBuffer.destroy();
	//g_indexBuffer.destroy();

	for (auto& vertexBuffer : g_vertexBuffers) {
		vertexBuffer.destroy();
	}
	
	for (auto& indexBuffer : g_indexBuffers) {
		indexBuffer.destroy();
	}
	g_shaderProgram.destroy();
	g_depthStencil.destroy();
	g_depthStencilView.destroy();
	g_renderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	g_device.destroy();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Update everyFrame
void Update(float DeltaTime) {
	// Rotate cube around the origin
	XMVECTOR translation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f); // Traslación en x=1, y=2, z=3
	XMVECTOR rotation = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(260), XMConvertToRadians(DeltaTime * 50), 0.0f); // Rotación en X=180, Y=180, Z=0
	XMVECTOR scale = XMVectorSet(2.0f, 2.0f, 2.0f, 0.0f); // Escala por 2 en x, y, z

	// Combinar las transformaciones en una matriz de mundo
	g_World = XMMatrixScalingFromVector(scale) * XMMatrixRotationQuaternion(rotation) * XMMatrixTranslationFromVector(translation);
	//g_World = XMMatrixRotationX(180) * XMMatrixRotationY(XMConvertToRadians(180.0f)) * XMMatrixRotationZ(0);

	// Modify the color
	//g_vMeshColor.x = (sinf(DeltaTime * 1.0f) + 1.0f) * 0.5f;
	//g_vMeshColor.y = (cosf(DeltaTime * 3.0f) + 1.0f) * 0.5f;
	//g_vMeshColor.z = (sinf(DeltaTime * 5.0f) + 1.0f) * 0.5f;

	// Update constant Buffers
	g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	// Actualizar info logica del mesh
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.vMeshColor = g_vMeshColor;
	g_CBBufferChangesEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Clear the back buffer
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

	// Set Viewport
	g_viewport.render(g_deviceContext);
	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	g_depthStencilView.render(g_deviceContext);

	//
	// Update variables that change once per frame
	//

	// Render the cube
	g_shaderProgram.render(g_deviceContext);
	//g_vertexBuffer.render(g_deviceContext, 0, 1);
	//g_indexBuffer.render(g_deviceContext, DXGI_FORMAT_R32_UINT);

	for (size_t i = 0; i < g_model.meshes.size(); i++) {
		g_vertexBuffers[i].render(g_deviceContext, 0, 1);
		g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
		modelTextures[i].render(g_deviceContext, 0, 1);
		g_sampler.render(g_deviceContext, 0, 1);

		// Actualizar constant buffers
		g_CBBufferNeverChanges.render(g_deviceContext, 0, 1);
		g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1);
		g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1);

		g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].numIndex, 0, 0);
	}

	//g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
	//g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
	//g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
	//g_modelTexture.render(g_deviceContext, 0, 1);
	//for (size_t i = 0; i < modelTextures.size(); ++i) {
	//	modelTextures[i].render(g_deviceContext, static_cast<unsigned int>(i), 1);
	//}
	//g_sampler.render(g_deviceContext, 0, 1);
	// Set primitive topology
	//g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//
	//g_deviceContext.m_deviceContext->DrawIndexed(g_mesh.numIndex, 0, 0);
	//
	// Present our back buffer to our front buffer
	//

	g_swapchain.present();
}
