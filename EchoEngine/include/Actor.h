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
#include "Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SamplerState.h"
#include "Transform.h"

class Device;
class MeshComponent;

/**
 * @class Actor
 * @brief Clase que representa un actor en el juego.
 *
 * La clase Actor hereda de Entity y representa un objeto en el juego que puede tener mallas,
 * texturas y varios componentes. Proporciona m�todos para actualizar, renderizar y destruir el actor.
 */
class Actor : public Entity {
public:
  /**
   * @brief Constructor por defecto.
   */
  Actor() = default;

  /**
   * @brief Constructor que inicializa el actor con un dispositivo.
   * @param device El dispositivo con el cual se inicializa el actor.
   */
  Actor(Device device);

  /**
   * @brief Destructor virtual.
   */
  virtual ~Actor() = default;

  /**
   * @brief Actualiza el actor.
   * @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n.
   * @param deviceContext Contexto del dispositivo para operaciones gr�ficas.
   */
  void update(float deltaTime, DeviceContext deviceContext) override;

  /**
   * @brief Renderiza el actor.
   * @param deviceContext Contexto del dispositivo para operaciones gr�ficas.
   */
  void render(DeviceContext deviceContext) override;

  /**
   * @brief Destruye el actor y libera los recursos asociados.
   */
  void destroy();

  /**
   * @brief Obtiene un componente espec�fico del actor.
   * @tparam T Tipo del componente que se va a obtener.
   * @return Puntero compartido al componente, o nullptr si no se encuentra.
   */
  template <typename T>
  std::shared_ptr<T> getComponent();

  /**
   * @brief Establece las mallas del actor.
   * @param device El dispositivo con el cual se inicializan las mallas.
   * @param meshes Vector de componentes de malla que se van a establecer.
   */
  void setMesh(Device device, std::vector<MeshComponent> meshes);

  /**
   * @brief Establece las texturas del actor.
   * @param textures Vector de texturas que se van a establecer.
   */
  void setTextures(std::vector<Texture> textures);

  /**
   * @brief Obtiene el nombre del actor.
   * @return El nombre del actor.
   */
  std::string getName() { return m_name; }

private:
  std::vector<MeshComponent> m_meshes; ///< Vector de componentes de malla.
  std::vector<Texture> m_textures; ///< Vector de texturas.

  SamplerState m_sampler; ///< Estado del muestreador.
  std::vector<Buffer> m_vertexBuffers; ///< Buffers de v�rtices.
  std::vector<Buffer> m_indexBuffers; ///< Buffers de �ndices.
  Buffer m_modelBuffer; ///< Buffer del modelo.
  CBChangesEveryFrame model; ///< Constante del buffer para cambios en cada frame.
  std::string m_name = "Actor"; ///< Nombre del actor.
};

/**
 * El prop�sito de esta funci�n es buscar y devolver un componente espec�fico de un actor, 
 * utilizando el tipo de componente especificado como argumento de la plantilla. 
 * Si el componente no se encuentra, la funci�n devuelve nullptr.
*/
template<typename T>
inline std::shared_ptr<T> Actor::getComponent() {
  for (auto& component : components) {
    std::shared_ptr<T> specificComponent = std::dynamic_pointer_cast<T>(component);
    if (specificComponent) {
      return specificComponent;
    }
  }
  return nullptr;
}
