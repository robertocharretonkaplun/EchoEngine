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
#include "Transform.h"
#include "DeviceContext.h"

void 
Transform::translate(const EngineUtilities::Vector3& translation) {
  position = position + translation;
}

void
Transform::init() {
  scale.x = 1;
  scale.y = 1;
  scale.z = 1;

  matrix = XMMatrixIdentity();
}

void 
Transform::update(float deltaTime) {
  // Aplicar escala
  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);

  // Aplicar rotación con deltaTime en todas las componentes
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(
    rotation.x,
    rotation.y,
    rotation.z
  );

  // Aplicar traslación
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Componer la matriz final en el orden: scale -> rotation -> translation
  matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void Transform::render(DeviceContext deviceContext)
{
}

void
Transform::destroy() {
}

void
Transform::ui(std::string wName) {
  ImGui::Begin(wName.c_str());

  // Draw the structure
  UI.vec3Control("Position", const_cast<float*>(position.data()));
  UI.vec3Control("Rotation", const_cast<float*>(rotation.data()));
  UI.vec3Control("Scale", const_cast<float*>(scale.data()));

  ImGui::End();
}

void
Transform::ui_noWindow(std::string wName) {
  ImGui::PushID(wName.c_str());

  // Draw the structure
  UI.vec3Control("Position", const_cast<float*>(position.data()));
  UI.vec3Control("Rotation", const_cast<float*>(rotation.data()));
  UI.vec3Control("Scale", const_cast<float*>(scale.data()));

  ImGui::PopID();
}
