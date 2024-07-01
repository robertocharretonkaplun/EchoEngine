#pragma once
#include "PreRequisites.h"
#include "Component.h"

class DeviceContext;

class 
Transform : public Component {
public:
  Transform() : Component(ComponentType::TRANSFORM) {}
	virtual ~Transform() = default;

	void 
  init();

  void 
  update(float deltaTime) override;
  
  void 
  render(DeviceContext deviceContext) override;
  
  void 
  destroy();

  //void 
  //ui(std::string wName);
  //
  //void 
  //ui_noWindow(std::string wName);
public:
	Vector3f m_position;
	Vector3f m_rotation;
	Vector3f m_scale;
  XMMATRIX m_matrix;
  //UserInterface UI;
  float* m_pos;
private:
  // UI data
  float* m_rot;
  float* m_sca;
};