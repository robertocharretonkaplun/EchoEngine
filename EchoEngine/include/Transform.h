#pragma once
#include "PreRequisites.h"
#include "Component.h"

class Transform : public Component {
public:
  Transform() : position(), rotation(), scale(), matrix() {}

  // Métodos de acceso a los datos
  const Vector3f& 
  getPosition() const { return position; }
  
  void 
  setPosition(const Vector3f& newPos) { position = newPos; }

  const Vector3f& 
  getRotation() const { return rotation; }
  
  void 
  setRotation(const Vector3f& newRot) { rotation = newRot; }

  const Vector3f& 
  getScale() const { return scale; }
  
  void 
  setScale(const Vector3f& newScale) { scale = newScale; }

  // Métodos para transformación y renderizado
  void 
  init();
  
  void 
  update(float deltaTime);
  
  void 
  render(DeviceContext deviceContext);
  
  void 
  destroy();

private:
  Vector3f position;
  Vector3f rotation;
  Vector3f scale;
public:
  XMMATRIX matrix;
};
