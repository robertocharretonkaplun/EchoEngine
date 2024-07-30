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
 * texturas y varios componentes. Proporciona métodos para actualizar, renderizar y destruir el actor.
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
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void update(float deltaTime, DeviceContext deviceContext) override;

  /**
   * @brief Renderiza el actor.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void render(DeviceContext deviceContext) override;

  /**
   * @brief Destruye el actor y libera los recursos asociados.
   */
  void destroy();

  /**
   * @brief Obtiene un componente específico del actor.
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
  std::vector<Buffer> m_vertexBuffers; ///< Buffers de vértices.
  std::vector<Buffer> m_indexBuffers; ///< Buffers de índices.
  Buffer m_modelBuffer; ///< Buffer del modelo.
  CBChangesEveryFrame model; ///< Constante del buffer para cambios en cada frame.
  std::string m_name = "Actor"; ///< Nombre del actor.
};

/**
 * El propósito de esta función es buscar y devolver un componente específico de un actor, 
 * utilizando el tipo de componente especificado como argumento de la plantilla. 
 * Si el componente no se encuentra, la función devuelve nullptr.
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
