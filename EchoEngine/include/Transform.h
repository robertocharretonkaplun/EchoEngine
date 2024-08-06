/*
 * MIT License
 *
 * Copyright (c) 2024 Roberto Charreton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * In addition, any project or software that uses this library or class must include
 * the following acknowledgment in the credits:
 *
 * "This project uses software developed by Roberto Charreton and Attribute Overload."
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#pragma once
#include "PreRequisites.h"
#include "Utilities/Vectors/Vector3.h"
#include "UserInterface.h"
#include "Component.h"

// Clase que maneja las transformaciones de un objeto en el espacio 3D
class Transform : public Component {
public:
  // Constructor que inicializa posición, rotación y escala por defecto
  Transform() : position(), rotation(), scale(), matrix(), Component(ComponentType::TRANSFORM) {}

  // Métodos de acceso a los datos de posición
  // Retorna la posición actual
  const EngineUtilities::Vector3&
  getPosition() const { return position; }

  // Establece una nueva posición
  void 
  setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  // Métodos de acceso a los datos de rotación
  // Retorna la rotación actual
  const EngineUtilities::Vector3&
  getRotation() const { return rotation; }

  // Establece una nueva rotación
  void 
  setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  // Métodos de acceso a los datos de escala
  // Retorna la escala actual
  const EngineUtilities::Vector3&
  getScale() const { return scale; }

  // Establece una nueva escala
  void 
  setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  // Método para trasladar la posición del objeto
  // @param translation: Vector que representa la cantidad de traslado en cada eje
  void 
  translate(const EngineUtilities::Vector3& translation);

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
  EngineUtilities::Vector3 position;  // Posición del objeto
  EngineUtilities::Vector3 rotation;  // Rotación del objeto
  EngineUtilities::Vector3 scale;     // Escala del objeto
  UserInterface UI;   // Interfaz de usuario para manipular el objeto

public:
  XMMATRIX matrix;    // Matriz de transformación
};
