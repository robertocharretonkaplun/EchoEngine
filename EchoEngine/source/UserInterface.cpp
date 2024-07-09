#include "UserInterface.h"
#include "Screenshot.h"
#include "Window.h"
#include "SwapChain.h"
#include "Texture.h"
//#include "Model.h"

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
}

void 
UserInterface::init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
  //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
  //io.ConfigViewportsNoAutoMerge = true;
  //io.ConfigViewportsNoTaskBarIcon = true;
  //io.ConfigViewportsNoDefaultParent = true;
  //io.ConfigDockingAlwaysTabBar = true;
  //io.ConfigDockingTransparentPayload = true;
  //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
  //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  //greyStyle();
  //darkStyle();
  GameMakerStyle();

  //greyStyle();
  //visualStudioStyle();
  // Setup Platform/Renderer backends
  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);

  // Init ToolTips
  toolTipData();
}

void 
UserInterface::update() {
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void 
UserInterface::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();
  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
}

void 
UserInterface::destroy() {
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void UserInterface::vec3Control(const std::string& label, float* values, float resetValue, float columnWidth) {
  ImGuiIO& io = ImGui::GetIO();
  auto boldFont = io.Fonts->Fonts[0];

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

  float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
  ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Z", buttonSize)) values[2] = resetValue;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Z", &values[2], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();
  ImGui::Columns(1);

  ImGui::PopID();
}


void 
UserInterface::menuBar(Window window, SwapChain swapChain, Texture& backBuffer) {
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      ImGui::MenuItem("New", "Ctrl+N");
      ImGui::MenuItem("Open", "Ctrl+O");
      ImGui::MenuItem("Save", "Ctrl+S");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
      ImGui::MenuItem("Copy", "Ctrl+C");
      ImGui::MenuItem("Paste", "Ctrl+V");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Capture screenshoot"))
    {
      //Screenshot sc;
      //sc.captureScreenshot(window,swapChain, backBuffer );
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

}

void 
UserInterface::Renderer(Window window, ID3D11ShaderResourceView* renderTexture) {
  bool Stage = true;
  ImGui::Begin("Renderer", &Stage, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
  ImTextureID texId = (ImTextureID)renderTexture;
  ImGui::Image(texId, ImVec2(window.m_width / 2, window.m_height / 2));
  ImGui::End();
}

//void 
//UserInterface::Inspector(std::vector<Model> & models, int index) {
//  static char post_text[1024] = "";
//  char inputValue[64] = "GameObject";
//  
//  
//  ImGui::Begin("Inspector");
//  // Agregar el checkbox a la izquierda del input text
//  ImGui::Checkbox("##s", &checkboxValue);
//  ToolTip(m_tooltips[1]);
//
//
//  ImGui::SameLine();
//  ImGui::SetNextItemWidth(475);
//  ImGui::InputText("##ObjectName", inputValue, IM_ARRAYSIZE(inputValue), 64);
//
//  // Agregar el texto "Static" a la derecha del input text
//  //ImGui::SameLine(0, ImGui::GetWindowWidth() - ImGui::GetCursorPosX() - 100);
//  ImGui::SameLine();
//  ImGui::Checkbox("Static", &checkboxValue2);
//  static const char* items[] = { "Item 1", "Item 2", "Item 3" };
//  
//  
//  static int currentItem = 0;
//  ImGui::Text("obj");
//  ToolTip(m_tooltips[0]);
//  ImGui::SameLine();
//  ImGui::SetNextItemWidth(258);
//  ImGui::Combo("##TagCombo", &currentItem, items, IM_ARRAYSIZE(items));
//  index = currentItem;
//  models[index].setActive(checkboxValue);
//  models[index].setStatic(checkboxValue2);
//  ImGui::SameLine();
//  ImGui::Text("Layer");
//  ImGui::SameLine();
//  ImGui::SetNextItemWidth(258);
//  ImGui::Combo("##LayerCombo", &currentItem, items, IM_ARRAYSIZE(items));
//
//
//  ImGui::Separator();
//  // Transform Component
//  ImGui::SetNextItemWidth(200);
//  
//  if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
//    //models[index].m_transform.ui_noWindow("");
//
//  }
//  
//    
//  ImGui::Separator();
//  // Mesh Component
//  if (ImGui::CollapsingHeader("Static Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {
//    ImGui::Text("Mesh: ");
//    ImGui::SameLine();
//    static char str0[128] = "Hello, world!";
//    ImGui::InputText("##Input", models[index].m_loadData.name.data(), IM_ARRAYSIZE(str0));
//    ImGui::Text("Vertices: ");
//    ImGui::SameLine();
//    ImGui::Text(std::to_string(models[index].m_loadData.numVertex).c_str());
//    ImGui::Text("Indices: ");
//    ImGui::SameLine();
//    ImGui::Text(std::to_string(models[index].m_loadData.numIndex).c_str());
//    ImGui::Text("VERTICES");
//    if (ImGui::Button("Load Vertex Data")) {
//      std::string vertexPositions;
//      for (int i = 0; i < models[index].m_loadData.vertex.size(); i++) {
//        vertexPositions += "(" + 
//          std::to_string(models[index].m_loadData.vertex[i].Pos.x) + ", " +
//          std::to_string(models[index].m_loadData.vertex[i].Pos.y) + ", " +
//          std::to_string(models[index].m_loadData.vertex[i].Pos.z) + ") \n ";
//      }
//    }
//
//
//  }
//  ImGui::Separator();
//  ImGui::End();
//}

void 
UserInterface::inspectorContainer() {
  
}

void 
UserInterface::output() {
  bool Stage = true;
  ImGui::Begin("Output", &Stage, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
  ImGui::End();
}

void 
UserInterface::darkStyle() {
  ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border] = ImVec4(0.04f, 0.04f, 0.04f, 0.04f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  for (int i = 0; i < ImGuiCol_COUNT; ++i)
  {
    colors[i].x += 0.015f; colors[i].y += 0.025f; colors[i].z += 0.020f;
  }
}

void 
UserInterface::greyStyle() {
  ImGuiStyle& style = ImGui::GetStyle();
  ImVec4* colors = style.Colors;

  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
  colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
  colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

  style.PopupRounding = 3;

  style.WindowPadding = ImVec2(4, 4);
  style.FramePadding = ImVec2(6, 4);
  style.ItemSpacing = ImVec2(6, 2);

  style.ScrollbarSize = 18;

  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = 2;

  style.WindowRounding = 3;
  style.ChildRounding = 3;
  style.FrameRounding = 3;
  style.ScrollbarRounding = 2;
  style.GrabRounding = 3;

  style.TabBorderSize = 2;
  style.TabRounding = 3;

  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
}

void 
UserInterface::GameMakerStyle() {
  ImGuiStyle& style = ImGui::GetStyle();
  // Material Flat style by ImJC1C from ImThemes
  style.Alpha = 1.0f;
  //style.DisabledAlpha = 0.5f;
  style.WindowPadding = ImVec2(8.0f, 8.0f);
  style.WindowRounding = 0.0f;
  style.WindowBorderSize = 1.0f;
  style.WindowMinSize = ImVec2(32.0f, 32.0f);
  style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
  style.WindowMenuButtonPosition = ImGuiDir_Left;
  style.ChildRounding = 0.0f;
  style.ChildBorderSize = 1.0f;
  style.PopupRounding = 0.0f;
  style.PopupBorderSize = 1.0f;
  style.FramePadding = ImVec2(4.0f, 3.0f);
  style.FrameRounding = 0.0f;
  style.FrameBorderSize = 0.0f;
  style.ItemSpacing = ImVec2(8.0f, 4.0f);
  style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
  style.CellPadding = ImVec2(4.0f, 2.0f);
  style.IndentSpacing = 21.0f;
  style.ColumnsMinSpacing = 6.0f;
  style.ScrollbarSize = 14.0f;
  style.ScrollbarRounding = 0.0f;
  style.GrabMinSize = 10.0f;
  style.GrabRounding = 0.0f;
  style.TabRounding = 0.0f;
  style.TabBorderSize = 0.0f;
  style.TabMinWidthForCloseButton = 0.0f;
  style.ColorButtonPosition = ImGuiDir_Left;
  style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
  style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

  style.Colors[ImGuiCol_Text] = ImVec4(0.8313725590705872f, 0.8470588326454163f, 0.8784313797950745f, 1.0f);
  style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.8313725590705872f, 0.8470588326454163f, 0.8784313797950745f, 0.501960813999176f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1725490242242813f, 0.1921568661928177f, 0.2352941185235977f, 1.0f);
  style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.1587982773780823f);
  style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1725490242242813f, 0.1921568661928177f, 0.2352941185235977f, 1.0f);
  style.Colors[ImGuiCol_Border] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 1.0f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 0.501960813999176f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.0f);
  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.5333333611488342f, 0.5333333611488342f, 0.5333333611488342f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3333333432674408f, 0.3333333432674408f, 0.3333333432674408f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
  style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.239215686917305f, 0.5215686559677124f, 0.8784313797950745f, 1.0f);
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9803921580314636f, 1.0f);
  style.Colors[ImGuiCol_Button] = ImVec4(0.3529411822557449f, 0.4125490242242813f, 0.4417647081613541f, 0.501960813999176f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_Header] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
  style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
  style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
  style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 0.7799999713897705f);
  style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
  style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_Tab] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
  style.Colors[ImGuiCol_TabHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
  style.Colors[ImGuiCol_TabActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
  style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
  style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
  style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 1.0f);
  style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 0.5021458864212036f);
  style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
  style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.03862661123275757f);
  style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 1.0f);
  style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
  style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
  style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 0.7529411911964417f);
  style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 0.7529411911964417f);
  style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 0.7529411911964417f);

}

void 
UserInterface::visualStudioStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  // Colors
  ImVec4* colors = style.Colors;

  const ImVec4 discord_purple = ImVec4(0.447f, 0.227f, 0.635f, 1.000f);
  const ImVec4 discord_darker_purple = ImVec4(0.337f, 0.157f, 0.486f, 1.000f);
  const ImVec4 discord_light_gray = ImVec4(0.741f, 0.765f, 0.780f, 1.000f);
  const ImVec4 discord_darker_gray = ImVec4(0.169f, 0.188f, 0.204f, 1.000f);
  const ImVec4 discord_blue = ImVec4(0.192f, 0.545f, 0.906f, 1.000f);
  const ImVec4 discord_green = ImVec4(0.129f, 0.694f, 0.403f, 1.000f);
  const ImVec4 discord_yellow = ImVec4(1.000f, 0.741f, 0.000f, 1.000f);
  const ImVec4 discord_red = ImVec4(0.757f, 0.169f, 0.169f, 1.000f);
  ImVec4 discord_light_blue = ImVec4(0.29f, 0.56f, 0.89f, 1.00f);
  ImVec4 discord_dark_gray = ImVec4(0.16f, 0.18f, 0.21f, 1.00f);
  ImVec4 discord_darker_green = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
  ImVec4 discord_darker_blue = ImVec4(0.05f, 0.11f, 0.19f, 1.00f);
  ImVec4 discord_lighter_gray = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);

  // Main
  colors[ImGuiCol_Text] = discord_light_gray;
  colors[ImGuiCol_TextDisabled] = discord_darker_gray;
  colors[ImGuiCol_WindowBg] = discord_purple;
  colors[ImGuiCol_ChildBg] = discord_purple;
  colors[ImGuiCol_PopupBg] = discord_purple;
  colors[ImGuiCol_Border] = discord_darker_gray;
  colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
  colors[ImGuiCol_FrameBg] = discord_darker_purple;
  colors[ImGuiCol_FrameBgHovered] = discord_blue;
  colors[ImGuiCol_FrameBgActive] = discord_blue;
  colors[ImGuiCol_TitleBg] = discord_darker_purple;
  colors[ImGuiCol_TitleBgActive] = discord_blue;
  colors[ImGuiCol_TitleBgCollapsed] = discord_darker_gray;
  colors[ImGuiCol_MenuBarBg] = discord_darker_purple;
  colors[ImGuiCol_ScrollbarBg] = discord_darker_purple;
  colors[ImGuiCol_ScrollbarGrab] = discord_light_gray;
  colors[ImGuiCol_ScrollbarGrabHovered] = discord_darker_gray;
  colors[ImGuiCol_ScrollbarGrabActive] = discord_blue;
  colors[ImGuiCol_CheckMark] = discord_green;
  colors[ImGuiCol_SliderGrab] = discord_green;
  colors[ImGuiCol_SliderGrabActive] = discord_darker_green;
  colors[ImGuiCol_Button] = discord_green;
  colors[ImGuiCol_ButtonHovered] = discord_blue;
  colors[ImGuiCol_ButtonActive] = discord_darker_blue;
  colors[ImGuiCol_Header] = discord_green;
  colors[ImGuiCol_HeaderHovered] = discord_blue;
  colors[ImGuiCol_HeaderActive] = discord_darker_blue;
  colors[ImGuiCol_Separator] = discord_darker_gray;
  colors[ImGuiCol_SeparatorHovered] = discord_blue;
  colors[ImGuiCol_SeparatorActive] = discord_darker_blue;
  colors[ImGuiCol_ResizeGrip] = discord_light_gray;
  colors[ImGuiCol_ResizeGripHovered] = discord_lighter_gray;
  colors[ImGuiCol_ResizeGripActive] = discord_lighter_gray;
  colors[ImGuiCol_Tab] = discord_dark_gray;
  colors[ImGuiCol_TabHovered] = discord_darker_blue;
  colors[ImGuiCol_TabActive] = discord_darker_blue;
  colors[ImGuiCol_TabUnfocused] = discord_darker_gray;
  colors[ImGuiCol_TabUnfocusedActive] = discord_lighter_gray;
  colors[ImGuiCol_DockingPreview] = discord_lighter_gray;
  colors[ImGuiCol_DockingEmptyBg] = discord_dark_gray;
  colors[ImGuiCol_PlotLines] = discord_lighter_gray;
  colors[ImGuiCol_PlotLinesHovered] = discord_light_blue;
  colors[ImGuiCol_PlotHistogram] = discord_lighter_gray;
  colors[ImGuiCol_PlotHistogramHovered] = discord_light_blue;
  colors[ImGuiCol_TextSelectedBg] = discord_light_blue;
  colors[ImGuiCol_DragDropTarget] = discord_light_blue;
  colors[ImGuiCol_NavHighlight] = discord_light_blue;
  colors[ImGuiCol_NavWindowingHighlight] = discord_light_blue;
  colors[ImGuiCol_NavWindowingDimBg] = discord_darker_gray;
  colors[ImGuiCol_ModalWindowDimBg] = discord_darker_gray;


}

void 
UserInterface::ToolTip(std::string icon, std::string tip) {
  ImGui::SameLine();
  ImGui::Text(icon.c_str());
  if (ImGui::IsItemHovered()) {
    ImGui::SetTooltip(tip.c_str());
  }
}

void 
UserInterface::ToolTip(std::string tip) {
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(tip.c_str());
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void 
UserInterface::toolTipData() {
  // ToolTip #1: Information about the Gameobject selector in the Inspector.
  m_tooltips.push_back(
    "You can change the current GameObject that is active to be used in the Inspector. \n"
    "\n"
    "NOTE:\n"
    "* This feature is WIP consider that it's possible that some things might not work correctly.\n");
  // ToolTip #2: Information about the render state of the GameObject in the Inspector.
  m_tooltips.push_back(
    "You can change the drawing state of the GameObject by activating or deactivating the checkbox. \n"
    "\n"
    "NOTE:\n"
    "* This feature is WIP consider that it's possible that some things might not work correctly.\n");
}
