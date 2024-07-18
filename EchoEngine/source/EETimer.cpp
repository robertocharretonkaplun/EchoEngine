#include "EETimer.h"

EETimer::EETimer() : deltaTime(0.0), elapsedTime(0.0) {
  Start();
}

void EETimer::Start() {
  startTime = std::chrono::high_resolution_clock::now();
  lastTime = startTime;
}

void EETimer::Tick() {
  auto currentTime = std::chrono::high_resolution_clock::now();
  deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
  elapsedTime = std::chrono::duration<double>(currentTime - startTime).count();
  lastTime = currentTime;
}

void EETimer::Reset() {
  Start();
}

double EETimer::GetDeltaTime() const {
  return deltaTime;
}

double EETimer::GetElapsedTime() const {
  return elapsedTime;
}