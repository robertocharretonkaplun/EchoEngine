#include "Transform.h"
#include "DeviceContext.h"

void
Transform::init() {
  scale.x = 1;
  scale.y = 1;
  scale.z = 1;

  matrix = XMMatrixIdentity();
}

void 
Transform::update(float deltaTime) {
  matrix = XMMatrixScaling(scale.x,
    scale.y,
    scale.z) *
    XMMatrixRotationRollPitchYaw(rotation.x,
      rotation.y,
      rotation.z) *
    XMMatrixTranslation(position.x,
      position.y,
      position.z);
}

void Transform::render(DeviceContext deviceContext)
{
}

void
Transform::destroy() {
}

//void
//Transform::ui(std::string wName) {
//  ImGui::Begin(wName.c_str());
//  // Get the position
//  m_pos[0] = m_position.x;
//  m_pos[1] = m_position.y;
//  m_pos[2] = m_position.z;
//
//  m_rot[0] = m_rotation.x;
//  m_rot[1] = m_rotation.y;
//  m_rot[2] = m_rotation.z;
//
//  m_sca[0] = m_scale.x;
//  m_sca[1] = m_scale.y;
//  m_sca[2] = m_scale.z;
//
//
//  // Draw the structure
//  UI.vec3Control("Position", m_pos);
//  UI.vec3Control("Rotation", m_rot);
//  UI.vec3Control("Scale", m_sca);
//
//  // Set the position 
//  m_position.x = m_pos[0];
//  m_position.y = m_pos[1];
//  m_position.z = m_pos[2];
//
//  m_rotation.x = m_rot[0];
//  m_rotation.y = m_rot[1];
//  m_rotation.z = m_rot[2];
//
//  m_scale.x = m_sca[0];
//  m_scale.y = m_sca[1];
//  m_scale.z = m_sca[2];
//
//  ImGui::End();
//}
//
//void
//Transform::ui_noWindow(std::string wName) {
//  // Get the position
//  m_pos[0] = m_position.x;
//  m_pos[1] = m_position.y;
//  m_pos[2] = m_position.z;
//
//  m_rot[0] = m_rotation.x;
//  m_rot[1] = m_rotation.y;
//  m_rot[2] = m_rotation.z;
//
//  m_sca[0] = m_scale.x;
//  m_sca[1] = m_scale.y;
//  m_sca[2] = m_scale.z;
//
//
//  // Draw the structure
//  UI.vec3Control("Position", m_pos);
//  UI.vec3Control("Rotation", m_rot);
//  UI.vec3Control("Scale", m_sca);
//
//  // Set the position 
//  m_position.x = m_pos[0];
//  m_position.y = m_pos[1];
//  m_position.z = m_pos[2];
//
//  m_rotation.x = m_rot[0];
//  m_rotation.y = m_rot[1];
//  m_rotation.z = m_rot[2];
//
//  m_scale.x = m_sca[0];
//  m_scale.y = m_sca[1];
//  m_scale.z = m_sca[2];
//
//}
