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