#pragma once
#include "Prerequisites.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <imgui_internal.h>

class Window;
class SwapChain;
class Texture;
//class Model;

class 
UserInterface {
public:
  UserInterface();
  ~UserInterface();

  void 
  init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

  void 
  update();
  
  void 
  render();
  
  void 
  destroy();

  void
  vec3Control(const std::string& label,
              float* values,
              float resetValues = 0.0f,
              float columnWidth = 100.0f);

  void 
  menuBar(Window window, SwapChain swapChain, Texture& backBuffer);

  void
  Renderer(Window window, ID3D11ShaderResourceView* renderTexture);

  //void
  //Inspector(std::vector<Model> & models, int index);

  void 
  inspectorContainer();

  void
  output();

  void
  darkStyle();
  
  void
  greyStyle();

  void
  GameMakerStyle();

  void
  visualStudioStyle();

  void
  ToolTip(std::string icon, std::string tip);
  void
  ToolTip( std::string tip);

  void
  toolTipData();

  void 
  ToolBar();

  void 
  closeApp();

  void
  RenderFullScreenTransparentWindow();
private:
  bool checkboxValue = true;
  bool checkboxValue2 = false;
  std::vector<const char*> m_objectsNames;
  std::vector<const char*> m_tooltips;

  bool show_exit_popup = false; // Variable de estado para el popup

};
