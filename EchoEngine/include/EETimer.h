#pragma once

#include <chrono>

class EETimer {
public:
  EETimer();

  void Start();
  void Tick();
  void Reset();

  double GetDeltaTime() const;
  double GetElapsedTime() const;

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
  std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
  double deltaTime;
  double elapsedTime;
};