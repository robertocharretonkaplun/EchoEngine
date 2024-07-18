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
