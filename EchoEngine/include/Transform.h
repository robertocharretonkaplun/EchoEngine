#pragma once
#include "PreRequisites.h"
#include "UserInterface.h"
#include "Component.h"

// Clase que maneja las transformaciones de un objeto en el espacio 3D
class Transform : public Component {
public:
  // Constructor que inicializa posici�n, rotaci�n y escala por defecto
  Transform() : position(), rotation(), scale(), matrix() {}

  // M�todos de acceso a los datos de posici�n
  // Retorna la posici�n actual
  const Vector3f& 
  getPosition() const { return position; }

  // Establece una nueva posici�n
  void 
  setPosition(const Vector3f& newPos) { position = newPos; }

  // M�todos de acceso a los datos de rotaci�n
  // Retorna la rotaci�n actual
  const Vector3f& 
  getRotation() const { return rotation; }

  // Establece una nueva rotaci�n
  void 
  setRotation(const Vector3f& newRot) { rotation = newRot; }

  // M�todos de acceso a los datos de escala
  // Retorna la escala actual
  const Vector3f& 
  getScale() const { return scale; }

  // Establece una nueva escala
  void 
  setScale(const Vector3f& newScale) { scale = newScale; }

  // M�todo para trasladar la posici�n del objeto
  // @param translation: Vector que representa la cantidad de traslado en cada eje
  void 
  translate(const Vector3f& translation);

  // M�todos para inicializaci�n, actualizaci�n, renderizado y destrucci�n
  // Inicializa el objeto Transform
  void 
  init();

  // Actualiza el estado del objeto Transform basado en el tiempo transcurrido
  // @param deltaTime: Tiempo transcurrido desde la �ltima actualizaci�n
  void 
  update(float deltaTime);

  // Renderiza el objeto Transform
  // @param deviceContext: Contexto del dispositivo de renderizado
  void 
  render(DeviceContext deviceContext);

  // Destruye el objeto Transform y libera recursos
  void 
  destroy();

  // M�todos para la interfaz de usuario
  // Muestra la interfaz de usuario en una ventana
  // @param wName: Nombre de la ventana
  void
  ui(std::string wName);

  // Muestra la interfaz de usuario sin ventana
  // @param wName: Nombre de la secci�n
  void 
  ui_noWindow(std::string wName);

private:
  Vector3f position;  // Posici�n del objeto
  Vector3f rotation;  // Rotaci�n del objeto
  Vector3f scale;     // Escala del objeto
  UserInterface UI;   // Interfaz de usuario para manipular el objeto

public:
  XMMATRIX matrix;    // Matriz de transformaci�n
};
