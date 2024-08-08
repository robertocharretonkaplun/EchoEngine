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
#include "DeviceContext.h"

/**
 * @class MeshComponent
 * @brief Componente que representa una malla en el juego.
 *
 * La clase MeshComponent hereda de Component y representa una malla con vértices e índices,
 * permitiendo su actualización y renderizado.
 */
class 
MeshComponent : public Component {
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
  virtual 
  ~MeshComponent() = default;

  /**
   * @brief Actualiza el componente de malla.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   */
  void 
  update(float deltaTime) override {}

  /**
   * @brief Renderiza el componente de malla.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void 
  render(DeviceContext deviceContext) override {}

public:
  std::string m_name; ///< Nombre de la malla.
  std::vector<SimpleVertex> m_vertex; ///< Vértices de la malla.
  std::vector<unsigned int> m_index; ///< Índices de la malla.
  int m_numVertex; ///< Número de vértices.
  int m_numIndex; ///< Número de índices.
};
