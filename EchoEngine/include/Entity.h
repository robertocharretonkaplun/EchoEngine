#pragma once
#include "PreRequisites.h"
#include "Component.h"
#include "Transform.h"

class DeviceContext;

class 
Entity {
public:
  Entity() = default;
  virtual ~Entity() = default;

  // Métodos básicos
  virtual void 
  update(float deltaTime) = 0;
  
  virtual void 
  render(DeviceContext deviceContext) = 0;

  void 
  addComponent(std::shared_ptr<Component> component)
  {
    m_components.push_back(component);
  }

  std::shared_ptr<Component> 
  getComponent(ComponentType type) const
  {
    auto it = std::find_if(m_components.begin(), m_components.end(),
      [&type](const std::shared_ptr<Component>& component) {
        return component->getType() == type;
      });

    if (it != m_components.end())
    {
      return *it;
    }
    return nullptr;
  }

protected:
  // Estado
  bool m_isActive;
  std::string m_id;

  std::vector<std::shared_ptr<Component>> m_components;
};