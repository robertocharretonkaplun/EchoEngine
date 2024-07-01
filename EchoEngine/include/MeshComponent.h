#pragma once

#pragma once
#include "PreRequisites.h"
#include "Component.h"
#include "DeviceContext.h"

class 
MeshComponent : public Component {
public:
  MeshComponent() : Component(ComponentType::MESH) {}
	virtual ~MeshComponent() = default;

  void 
  update(float deltaTime) override {}
  
  void 
  render(DeviceContext deviceContext) override {}

public:
  std::string m_name;
  std::vector <SimpleVertex> m_vertex;
  std::vector <unsigned int> m_index;
  int m_numVertex;
  int m_numIndex;
};