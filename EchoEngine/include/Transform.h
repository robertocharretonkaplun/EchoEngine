#pragma once
#include "PreRequisites.h"
#include "UserInterface.h"
#include "Component.h"

// Clase que maneja las transformaciones de un objeto en el espacio 3D
class Transform : public Component {
public:
  // Constructor que inicializa posición, rotación y escala por defecto
  Transform() : position(), rotation(), scale(), matrix() {}

  // Métodos de acceso a los datos de posición
  // Retorna la posición actual
  const Vector3f& 
  getPosition() const { return position; }

  // Establece una nueva posición
  void 
  setPosition(const Vector3f& newPos) { position = newPos; }

  // Métodos de acceso a los datos de rotación
  // Retorna la rotación actual
  const Vector3f& 
  getRotation() const { return rotation; }

  // Establece una nueva rotación
  void 
  setRotation(const Vector3f& newRot) { rotation = newRot; }

  // Métodos de acceso a los datos de escala
  // Retorna la escala actual
  const Vector3f& 
  getScale() const { return scale; }

  // Establece una nueva escala
  void 
  setScale(const Vector3f& newScale) { scale = newScale; }

  // Método para trasladar la posición del objeto
  // @param translation: Vector que representa la cantidad de traslado en cada eje
  void 
  translate(const Vector3f& translation);

  // Métodos para inicialización, actualización, renderizado y destrucción
  // Inicializa el objeto Transform
  void 
  init();

  // Actualiza el estado del objeto Transform basado en el tiempo transcurrido
  // @param deltaTime: Tiempo transcurrido desde la última actualización
  void 
  update(float deltaTime);

  // Renderiza el objeto Transform
  // @param deviceContext: Contexto del dispositivo de renderizado
  void 
  render(DeviceContext deviceContext);

  // Destruye el objeto Transform y libera recursos
  void 
  destroy();

  // Métodos para la interfaz de usuario
  // Muestra la interfaz de usuario en una ventana
  // @param wName: Nombre de la ventana
  void
  ui(std::string wName);

  // Muestra la interfaz de usuario sin ventana
  // @param wName: Nombre de la sección
  void 
  ui_noWindow(std::string wName);

private:
  Vector3f position;  // Posición del objeto
  Vector3f rotation;  // Rotación del objeto
  Vector3f scale;     // Escala del objeto
  UserInterface UI;   // Interfaz de usuario para manipular el objeto

public:
  XMMATRIX matrix;    // Matriz de transformación
};
