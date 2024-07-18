#include "Transform.h"
#include "DeviceContext.h"

void 
Transform::translate(const Vector3f& translation) {
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
