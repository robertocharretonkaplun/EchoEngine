#pragma once
#include "PreRequisites.h"
#include "Component.h"
#include "DeviceContext.h"

/**
 * @class MeshComponent
 * @brief Componente que representa una malla en el juego.
 *
 * La clase MeshComponent hereda de Component y representa una malla con vértices e índices,
 * permitiendo su actualización y renderizado.
 */
class MeshComponent : public Component {
public:
  /**
   * @brief Constructor por defecto.
   *
   * Inicializa el componente de malla con tipo `ComponentType::MESH` y valores por defecto.
   */
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

  /**
   * @brief Destructor virtual.
   */
  virtual ~MeshComponent() = default;

  /**
   * @brief Actualiza el componente de malla.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   */
  void update(float deltaTime) override {}

  /**
   * @brief Renderiza el componente de malla.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void render(DeviceContext deviceContext) override {}

public:
  std::string m_name; ///< Nombre de la malla.
  std::vector<SimpleVertex> m_vertex; ///< Vértices de la malla.
  std::vector<unsigned int> m_index; ///< Índices de la malla.
  int m_numVertex; ///< Número de vértices.
  int m_numIndex; ///< Número de índices.
};
