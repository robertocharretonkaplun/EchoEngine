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
class DeviceContext;

/**
 * @enum ComponentType
 * @brief Tipos de componentes disponibles en el juego.
 */
enum 
ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformación.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3  ///< Componente de material.
};

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes del juego.
 *
 * La clase Component define la interfaz básica que todos los componentes deben implementar,
 * permitiendo actualizar y renderizar el componente, así como obtener su tipo.
 */
class 
Component {
public:
  /**
   * @brief Constructor por defecto.
   */
  Component() = default;

  /**
   * @brief Constructor con tipo de componente.
   * @param type Tipo del componente.
   */
  Component(const ComponentType type) : m_type(type) {}

  /**
   * @brief Destructor virtual.
   */
  virtual 
  ~Component() = default;

  /**
   * @brief Método virtual puro para actualizar el componente.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   */
  virtual void 
  update(float deltaTime) = 0;

  /**
   * @brief Método virtual puro para renderizar el componente.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  virtual void 
  render(DeviceContext deviceContext) = 0;

  /**
   * @brief Obtiene el tipo del componente.
   * @return El tipo del componente.
   */
  ComponentType 
  getType() const { return m_type; }

protected:
  ComponentType m_type; ///< Tipo del componente.
};
