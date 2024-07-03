#pragma once
#include "PreRequisites.h"
class DeviceContext;

enum 
ComponentType {
  NONE = 0,
  TRANSFORM = 1,
  MESH = 2,
  MATERIAL = 3 
};

// Clase base abstracta para todos los componentes
class Component
{
public:
  Component() = default;
  Component(const ComponentType type) : m_type(type) {}
  virtual ~Component() = default;

  // Métodos virtuales puros que deben ser implementados por las clases derivadas
  virtual void 
  update(float deltaTime) = 0;
  
  virtual void 
  render(DeviceContext deviceContext) = 0;

  // Obtener el tipo del componente
  ComponentType 
  getType() const { return m_type; }

protected:
  ComponentType m_type;
};