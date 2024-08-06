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

#include <chrono>

/**
 * @class EETimer
 * @brief Clase para medir el tiempo transcurrido y el tiempo entre actualizaciones.
 *
 * Esta clase utiliza la biblioteca <chrono> para medir el tiempo con alta resolución.
 */
class EETimer {
public:
  /**
   * @brief Constructor de la clase EETimer.
   *
   * Inicializa las variables de tiempo.
   */
  EETimer();

  /**
   * @brief Inicia el temporizador.
   *
   * Establece el tiempo de inicio y el tiempo de la última actualización a la hora actual.
   */
  void 
  Start();

  /**
   * @brief Actualiza el temporizador.
   *
   * Calcula el tiempo transcurrido desde la última actualización y actualiza el tiempo de la última actualización.
   */
  void 
  Tick();

  /**
   * @brief Reinicia el temporizador.
   *
   * Reinicia el tiempo de inicio y de la última actualización a la hora actual.
   */
  void 
  Reset();

  /**
   * @brief Obtiene el tiempo transcurrido entre la última actualización y la anterior.
   *
   * @return Tiempo transcurrido en segundos.
   */
  double 
  GetDeltaTime() const;

  /**
   * @brief Obtiene el tiempo total transcurrido desde el inicio del temporizador.
   *
   * @return Tiempo total transcurrido en segundos.
   */
  double 
  GetElapsedTime() const;

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;  ///< Tiempo de inicio del temporizador.
  std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;   ///< Tiempo de la última actualización.
  double deltaTime;   ///< Tiempo transcurrido entre la última actualización y la anterior, en segundos.
  double elapsedTime; ///< Tiempo total transcurrido desde el inicio del temporizador, en segundos.
};
