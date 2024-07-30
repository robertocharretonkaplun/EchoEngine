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
