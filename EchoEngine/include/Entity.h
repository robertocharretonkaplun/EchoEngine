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
#include "Component.h"

class DeviceContext;

/**
 * @class Entity
 * @brief Clase base para todas las entidades en el juego.
 *
 * La clase Entity representa cualquier objeto del juego que pueda tener componentes
 * y que se pueda actualizar y renderizar.
 */
class Entity {
public:
  /**
   * @brief Destructor virtual.
   */
  virtual ~Entity() = default;

  /**
   * @brief Método virtual puro para actualizar la entidad.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  virtual void update(float deltaTime, DeviceContext deviceContext) = 0;

  /**
   * @brief Método virtual puro para renderizar la entidad.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  virtual void render(DeviceContext deviceContext) = 0;

  /**
   * @brief Agrega un componente a la entidad.
   * @tparam T Tipo del componente, debe derivar de Component.
   * @param component Puntero compartido al componente que se va a agregar.
   */
  template <typename T>
  void addComponent(std::shared_ptr<T> component) {
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    components.push_back(component);
  }

  /**
   * @brief Obtiene un componente de la entidad.
   * @tparam T Tipo del componente que se va a obtener.
   * @return Puntero compartido al componente, o nullptr si no se encuentra.
   */
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
  bool isActive; ///< Indica si la entidad está activa.
  std::string id; ///< Identificador único de la entidad.

  std::vector<std::shared_ptr<Component>> components; ///< Lista de componentes de la entidad.
};
