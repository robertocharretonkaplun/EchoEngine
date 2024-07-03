#pragma once
#include "PreRequisites.h"
#include "Component.h"
#include "Transform.h"

class DeviceContext;

class 
Entity {
public:
  virtual ~Entity() = default;

  // Métodos básicos
  virtual void 
  update(float deltaTime, DeviceContext deviceContext) = 0;
  
  virtual void 
  render(DeviceContext deviceContext) = 0;

  template <typename T>
  void addComponent(std::shared_ptr<T> component) {
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    components.push_back(component);
  }

  template <typename T>
  std::shared_ptr<T> getComponent() {
    for (auto& component : components) {
      std::shared_ptr<T> specificComponent = std::dynamic_pointer_cast<T>(component);
      if (specificComponent) {
        return specificComponent;
      }
    }
    return nullptr;
  }

protected:
  // Estado
  bool isActive;
  std::string id;

  std::vector<std::shared_ptr<Component>> components;
};