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
#include "BaseApp.h"

HRESULT
BaseApp::init() {
	HRESULT hr = S_OK;

	// Create Swapchain
	m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);

	// Create render target view
	m_renderTargetView.init(m_device,
		m_backBuffer,
		DXGI_FORMAT_R8G8B8A8_UNORM);

	// Create depth stencil texture
	m_depthStencil.init(m_device,
		m_window.m_width,
		m_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		D3D11_BIND_DEPTH_STENCIL);

	// Create the depth stencil view
	m_depthStencilView.init(m_device,
		m_depthStencil,
		DXGI_FORMAT_D24_UNORM_S8_UINT);


	// Setup the viewport
	m_viewport.init(m_window);

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

	m_shaderProgram.init(m_device, "EchoEngine.fx", Layout);

	// Create Grid 
	CreateGrid(50, 50, 25.0f);

	// Load Model
	m_model.LoadModel("Models/Vela2.fbx");

	// Inicialización de Constant Buffers
	m_CBBufferNeverChanges.init(m_device, sizeof(CBNeverChanges));

	m_CBBufferChangeOnResize.init(m_device, sizeof(CBChangeOnResize));

	// Load the Texture
	Texture Vela_Char_BaseColor;
	Vela_Char_BaseColor.init(m_device,
		"Textures/Vela/Vela_Char_BaseColor.png",
		ExtensionType::PNG);

	Texture Vela_Corneas_BaseColor;
	Vela_Corneas_BaseColor.init(m_device,
		"Textures/Vela/Vela_Corneas_BaseColor.png",
		ExtensionType::PNG);

	Texture Vela_Gun_BaseColor;
	Vela_Gun_BaseColor.init(m_device,
		"Textures/Vela/Vela_Gun_BaseColor.png",
		ExtensionType::PNG);

	Texture Vela_Legs_BaseColor;
	Vela_Legs_BaseColor.init(m_device,
		"Textures/Vela/Vela_Legs_BaseColor.png",
		ExtensionType::PNG);

	Texture Vela_Mechanical_BaseColor;
	Vela_Mechanical_BaseColor.init(m_device,
		"Textures/Vela/Vela_Mechanical_BaseColor.png",
		ExtensionType::PNG);

	Texture Vela_Plate_BaseColor;
	Vela_Plate_BaseColor.init(m_device,
		"Textures/Vela/Vela_Plate_BaseColor.png",
		ExtensionType::PNG);

	Texture Vela_Visor_BaseColor;
	Vela_Visor_BaseColor.init(m_device,
		"Textures/Vela/Vela_Visor_BaseColor.png",
		ExtensionType::PNG);

	modelTextures.push_back(Vela_Corneas_BaseColor);		// 1 
	modelTextures.push_back(Vela_Gun_BaseColor);				// 2
	modelTextures.push_back(Vela_Visor_BaseColor);			// 3
	modelTextures.push_back(Vela_Legs_BaseColor);				// 4
	modelTextures.push_back(Vela_Mechanical_BaseColor); // 5
	modelTextures.push_back(Vela_Char_BaseColor);				// 6
	modelTextures.push_back(Vela_Plate_BaseColor);			// 7

	m_default.init(m_device, "Textures/Default.png", ExtensionType::PNG);


	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_View = XMMatrixLookAtLH(Eye, At, Up);


	cbNeverChanges.mView = XMMatrixTranspose(m_View);

	// Initialize the projection matrix
	m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4,
		m_window.m_width / (FLOAT)m_window.m_height,
		0.001f,
		100.0f);

	cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);

	// Set Vela Actor
	AVela = EngineUtilities::MakeShared<Actor>(m_device);

	if (!AVela.isNull()) {

		AVela->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(-0.9f,
			-2.0f,
			2.0f));
		AVela->getComponent<Transform>()->setRotation(EngineUtilities::Vector3(XM_PI / -2.0f,
			0.0f,
			XM_PI / 2.0f));
		AVela->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f,
			.03f,
			.03f));
		AVela->setMesh(m_device, m_model.meshes);
		AVela->setTextures(modelTextures);
		MESSAGE("Actor", "Actor", "Actor accessed successfully.")
	}
	else {
		MESSAGE("Actor", "vela", "Actor resource not found.")
	}

	// Set Grid Actor
	AGrid = EngineUtilities::MakeShared<Actor>(m_device);
	if (!AGrid.isNull()) {
		std::vector<MeshComponent> gridMesh;
		gridMesh.push_back(MC);
		AGrid->setMesh(m_device, gridMesh);
		gridTexs.push_back(m_default);
		AGrid->setTextures(gridTexs);
		AGrid->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(0.0f,
			-2.0f,
			0.0f));
		AGrid->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f,
			.03f,
			.03f));
		MESSAGE("Actor", "AGrid", "Actor created successfully.")
	}
	else {
		MESSAGE("Actor", "AGrid", "Actor resource not found.")
	}

	// Initialize User Interface
	m_userInterface.init(m_window.m_hWnd,
		m_device.m_device,
		m_deviceContext.m_deviceContext);

	return S_OK;
}

void
BaseApp::update() {
	m_userInterface.update();
	bool show_demo_window = true;
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
	AGrid->getComponent<Transform>()->ui_noWindow("Grid Transform");

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
	m_CBBufferNeverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	m_CBBufferChangeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	// Actualizar info logica del mesh
	AVela->update(0, m_deviceContext);
	AGrid->update(0, m_deviceContext);
	//EngineUtilities::Vector3 translation(0.0f, 0.0f, DeltaTime);
	//AVela->getComponent<Transform>()->translate(translation);
	//AVela->getComponent<Transform>()->setRotation(Vector3f(XM_PI / -2.0f, DeltaTime, XM_PI / 2.0f));
}

void
BaseApp::render() {
	// Clear the back buffer
	float ClearColor[4] = { 0.85f, 0.85f, 0.85f, 1.0f }; // red, green, blue, alpha
	m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

	// Set Viewport
	m_viewport.render(m_deviceContext);
	// Clear the depth buffer to 1.0 (max depth)
	m_depthStencilView.render(m_deviceContext);

	// Render the cube
	m_shaderProgram.render(m_deviceContext);

	// Render the models
	AVela->render(m_deviceContext);
	AGrid->render(m_deviceContext);

	// Actualizar constant buffers
	m_CBBufferNeverChanges.render(m_deviceContext, 0, 1);
	m_CBBufferChangeOnResize.render(m_deviceContext, 1, 1);

	m_userInterface.render();

	m_swapchain.present();
}

void
BaseApp::destroy() {
	if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

	AVela->destroy();
	AGrid->destroy();

	//m_default.destroy();
	m_CBBufferNeverChanges.destroy();
	m_CBBufferChangeOnResize.destroy();

	m_shaderProgram.destroy();
	m_depthStencil.destroy();
	m_depthStencilView.destroy();
	m_renderTargetView.destroy();
	m_swapchain.destroy();
	m_deviceContext.destroy();
	// Release UI
	m_userInterface.destroy();

	m_device.destroy();
}

int
BaseApp::run(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPWSTR lpCmdLine,
						 int nCmdShow, 
						 WNDPROC wndproc) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicializa la ventana
	if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
		return 0;

	// Inicializa los recursos de la aplicacion
	if (FAILED(init()))
	{
		destroy();
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
			update();
			render();
		}
	}

	destroy();

	return (int)msg.wParam;
}

void 
BaseApp::CreateGrid(int width, int depth, float spacing) {
	MC.m_vertex.clear();
	MC.m_index.clear();
	float halfLineWidth = .8 * 0.5f;

	for (int i = -width; i <= width; ++i)
	{
		// Create vertices for a vertical line as two triangles
		MC.m_vertex.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, -depth * spacing),
														XMFLOAT2(0.0f, 0.0f) });
		MC.m_vertex.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, -depth * spacing),
														XMFLOAT2(0.0f, 0.0f) });
		MC.m_vertex.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, depth * spacing),
														XMFLOAT2(0.0f, 0.0f) });
		MC.m_vertex.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, depth * spacing),
														XMFLOAT2(0.0f, 0.0f) });

		MC.m_index.push_back(MC.m_vertex.size() - 4);
		MC.m_index.push_back(MC.m_vertex.size() - 3);
		MC.m_index.push_back(MC.m_vertex.size() - 2);

		MC.m_index.push_back(MC.m_vertex.size() - 3);
		MC.m_index.push_back(MC.m_vertex.size() - 2);
		MC.m_index.push_back(MC.m_vertex.size() - 1);
	}

	for (int i = -depth; i <= depth; ++i)
	{
		// Create vertices for a horizontal line as two triangles
		MC.m_vertex.push_back({ XMFLOAT3(-width * spacing, 0, i * spacing - halfLineWidth),
														XMFLOAT2(0.0f, 0.0f) });
		MC.m_vertex.push_back({ XMFLOAT3(width * spacing, 0, i * spacing - halfLineWidth),
														XMFLOAT2(0.0f, 0.0f) });
		MC.m_vertex.push_back({ XMFLOAT3(-width * spacing, 0, i * spacing + halfLineWidth),
														XMFLOAT2(0.0f, 0.0f) });
		MC.m_vertex.push_back({ XMFLOAT3(width * spacing, 0, i * spacing + halfLineWidth),
														XMFLOAT2(0.0f, 0.0f) });

		MC.m_index.push_back(MC.m_vertex.size() - 4);
		MC.m_index.push_back(MC.m_vertex.size() - 3);
		MC.m_index.push_back(MC.m_vertex.size() - 2);

		MC.m_index.push_back(MC.m_vertex.size() - 3);
		MC.m_index.push_back(MC.m_vertex.size() - 2);
		MC.m_index.push_back(MC.m_vertex.size() - 1);
	}

	MC.m_numVertex = MC.m_vertex.size();
	MC.m_numIndex = MC.m_index.size();
}
