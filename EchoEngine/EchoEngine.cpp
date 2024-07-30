//--------------------------------------------------------------------------------------
// File: EchoEngine.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequisites.h"
#include "EETimer.h"
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
#include "Actor.h"
#include "UserInterface.h"

//#include "fbxsdk.h"
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
EETimer															g_timer;
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
Buffer															g_CBBufferNeverChanges;
Buffer															g_CBBufferChangeOnResize;
ModelLoader													g_model;
UserInterface												g_userInterface;

XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

std::vector<SimpleVertex> gridVertices;
std::vector<UINT> gridIndices;
MeshComponent MC;
//Mesh																g_mesh;

EngineUtilities::TSharedPointer<Actor> grid;
EngineUtilities::TSharedPointer<Actor> AVela;

Texture g_default;
std::vector<Texture> modelTextures;
std::vector<Texture> gridTexs;

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
void Update(double DeltaTime);


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
	{
		g_timer.Start();
		return 0;
	}

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
			std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Simula aproximadamente 60 FPS
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

			g_timer.Tick();
			double deltaTime = g_timer.GetDeltaTime();

			Update(deltaTime);
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}

void CreateGrid(int width, int depth, float spacing)
{
	gridVertices.clear();
	gridIndices.clear();
	float halfLineWidth = .8 * 0.5f;

	for (int i = -width; i <= width; ++i)
	{
		// Create vertices for a vertical line as two triangles
		gridVertices.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, -depth * spacing), XMFLOAT2(0.0f, 0.0f) });
		gridVertices.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, -depth * spacing), XMFLOAT2(0.0f, 0.0f) });
		gridVertices.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, depth * spacing), XMFLOAT2(0.0f, 0.0f) });
		gridVertices.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, depth * spacing), XMFLOAT2(0.0f, 0.0f) });

		gridIndices.push_back(gridVertices.size() - 4);
		gridIndices.push_back(gridVertices.size() - 3);
		gridIndices.push_back(gridVertices.size() - 2);

		gridIndices.push_back(gridVertices.size() - 3);
		gridIndices.push_back(gridVertices.size() - 2);
		gridIndices.push_back(gridVertices.size() - 1);
	}

	for (int i = -depth; i <= depth; ++i)
	{
		// Create vertices for a horizontal line as two triangles
		gridVertices.push_back({ XMFLOAT3(-width * spacing, 0, i * spacing - halfLineWidth), XMFLOAT2(0.0f, 0.0f) });
		gridVertices.push_back({ XMFLOAT3(width * spacing, 0, i * spacing - halfLineWidth), XMFLOAT2(0.0f, 0.0f) });
		gridVertices.push_back({ XMFLOAT3(-width * spacing, 0, i * spacing + halfLineWidth), XMFLOAT2(0.0f, 0.0f) });
		gridVertices.push_back({ XMFLOAT3(width * spacing, 0, i * spacing + halfLineWidth), XMFLOAT2(0.0f, 0.0f) });

		gridIndices.push_back(gridVertices.size() - 4);
		gridIndices.push_back(gridVertices.size() - 3);
		gridIndices.push_back(gridVertices.size() - 2);

		gridIndices.push_back(gridVertices.size() - 3);
		gridIndices.push_back(gridVertices.size() - 2);
		gridIndices.push_back(gridVertices.size() - 1);
	}
	MC.m_vertex = gridVertices;
	MC.m_index = gridIndices;
	MC.m_numVertex = gridVertices.size();
	MC.m_numIndex = gridIndices.size();


}

void CreateGridBuffers()
{
	CreateGrid(50, 50, 15.0f); // Cambia los parámetros según tus necesidades
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
	CreateGridBuffers();

	// Load Model
	g_model.LoadModel("Models/Vela2.fbx");

	// Inicialización de Constant Buffers
	g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

	g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

	// Load the Texture
	Texture Vela_Char_BaseColor;
	Vela_Char_BaseColor.init(g_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Corneas_BaseColor;
	Vela_Corneas_BaseColor.init(g_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Gun_BaseColor;
	Vela_Gun_BaseColor.init(g_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Legs_BaseColor;
	Vela_Legs_BaseColor.init(g_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Mechanical_BaseColor;
	Vela_Mechanical_BaseColor.init(g_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Plate_BaseColor;
	Vela_Plate_BaseColor.init(g_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Visor_BaseColor;
	Vela_Visor_BaseColor.init(g_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

	modelTextures.push_back(Vela_Corneas_BaseColor);		// 1 
	modelTextures.push_back(Vela_Gun_BaseColor);				// 2
	modelTextures.push_back(Vela_Visor_BaseColor);			// 3
	modelTextures.push_back(Vela_Legs_BaseColor);				// 4
	modelTextures.push_back(Vela_Mechanical_BaseColor); // 5
	modelTextures.push_back(Vela_Char_BaseColor);				// 6
	modelTextures.push_back(Vela_Plate_BaseColor);			// 7

	g_default.init(g_device, "Textures/Default.png", ExtensionType::PNG);


	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);


	cbNeverChanges.mView = XMMatrixTranspose(g_View);

	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, 
																					g_window.m_width / (FLOAT)g_window.m_height, 
																					0.01f, 
																					100.0f);

	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);

	// Set Vela Actor
	AVela = EngineUtilities::MakeShared<Actor>(g_device);

	if (!AVela.isNull()) {
		MESSAGE("Actor", "Actor", "Actor accessed successfully.")

		AVela->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(-0.9f, -2.0f, 2.0f));
		AVela->getComponent<Transform>()->setRotation(EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f));
		AVela->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
		AVela->setMesh(g_device, g_model.meshes);
		AVela->setTextures(modelTextures);
	}
	else {
		MESSAGE("Actor", "Actor", "Actor resource not found.")
	}

	grid = EngineUtilities::MakeShared<Actor>(g_device);
	if (!grid.isNull()) {
		MESSAGE("Actor", "Actor", "Actor accessed successfully.")
			std::vector<MeshComponent> gridMesh;
		gridMesh.push_back(MC);
		grid->setMesh(g_device, gridMesh);
		gridTexs.push_back(g_default);
		grid->setTextures(gridTexs);
		grid->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(0.0f, -2.0f, 0.0f));
		grid->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
	}
	else {
		MESSAGE("Actor", "Actor", "Actor resource not found.")
	}

	// Initialize User Interface
	g_userInterface.init(g_window.m_hWnd,
		g_device.m_device,
		g_deviceContext.m_deviceContext);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

	AVela->destroy();
	grid->destroy();

	//g_default.destroy();
	g_CBBufferNeverChanges.destroy();
	g_CBBufferChangeOnResize.destroy();

	g_shaderProgram.destroy();
	g_depthStencil.destroy();
	g_depthStencilView.destroy();
	g_renderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	// Release UI
	g_userInterface.destroy();

	g_device.destroy();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
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
void Update(double DeltaTime) {
	g_userInterface.update();
	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
	//g_userInterface.vec3Control("Transform", AVela->getComponent<Transform>()->getPosition().data());
	ImGui::Begin("Inspector");
	// Checkbox para Static
	bool isStatic = false;
	ImGui::Checkbox("##Static", &isStatic);
	ImGui::SameLine();

	// Input text para el nombre del objeto
	char objectName[128] = "Cube";
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.6f);
	ImGui::InputText("##ObjectName", objectName, IM_ARRAYSIZE(objectName));
	ImGui::SameLine();

	// Icono (este puede ser una imagen, aquí solo como ejemplo de botón)
	if (ImGui::Button("Icon")) {
		// Lógica del botón de icono aquí
	}

	// Separador horizontal
	ImGui::Separator();

	// Dropdown para Tag
	const char* tags[] = { "Untagged", "Player", "Enemy", "Environment" };
	static int currentTag = 0;
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.5f);
	ImGui::Combo("Tag", &currentTag, tags, IM_ARRAYSIZE(tags));
	ImGui::SameLine();

	// Dropdown para Layer
	const char* layers[] = { "Default", "TransparentFX", "Ignore Raycast", "Water", "UI" };
	static int currentLayer = 0;
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.5f);
	ImGui::Combo("Layer", &currentLayer, layers, IM_ARRAYSIZE(layers));

	ImGui::Separator();

	AVela->getComponent<Transform>()->ui_noWindow("Transform");
	ImGui::Separator();
	grid->getComponent<Transform>()->ui_noWindow("Grid Transform");

	// Mostrar la textura en la ventana de ImGui
	if (!modelTextures.empty()) {
		ImGui::Text("Model Texture:");
		// Usa el primer SRV de la lista de texturas del modelo
		for (auto& texture : modelTextures) {
			ImGui::ImageButton((void*)texture.m_textureFromImg, ImVec2(64, 64));
			ImGui::SameLine();
		}
	}


	ImGui::End();
	// Update constant Buffers
	g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	// Actualizar info logica del mesh
	AVela->update(0, g_deviceContext);
	grid->update(0, g_deviceContext);
	//EngineUtilities::Vector3 translation(0.0f, 0.0f, DeltaTime);
	//AVela->getComponent<Transform>()->translate(translation);
	//AVela->getComponent<Transform>()->setRotation(Vector3f(XM_PI / -2.0f, DeltaTime, XM_PI / 2.0f));
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Clear the back buffer
	float ClearColor[4] = { 0.85f, 0.85f, 0.85f, 1.0f }; // red, green, blue, alpha
	g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

	// Set Viewport
	g_viewport.render(g_deviceContext);
	// Clear the depth buffer to 1.0 (max depth)
	g_depthStencilView.render(g_deviceContext);

	// Render the cube
	g_shaderProgram.render(g_deviceContext);

	// Render the models
	AVela->render(g_deviceContext);
	grid->render(g_deviceContext);

	//for (size_t i = 0; i < 7; i++) {
	//	//g_vertexBuffers[i].render(g_deviceContext, 0, 1);
		//g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
		//if (i <= modelTextures.size() - 1)
		//{
		//	modelTextures[i].render(g_deviceContext, 0, 1);
		//}
		//else {
		//	g_default.render(g_deviceContext, 0, 1);
		//}
		//g_default.render(g_deviceContext, 0, 1);
		//g_sampler.render(g_deviceContext, 0, 1);
	//
	//
	//	//g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	//g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].m_numIndex, 0, 0);
	//}

	// Actualizar constant buffers
	g_CBBufferNeverChanges.render(g_deviceContext, 0, 1);
	g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1);

	g_userInterface.render();

	g_swapchain.present();
}
