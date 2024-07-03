#pragma once
// Librerias STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <memory>
// Librerias DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"

// Third Parties

// MACRO for safe release of resources
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// * To check monster
#define OutputLOG(_ClassName, _FunctionName, _OutputMessage)	   	\
OutputDebugStringA(_ClassName);											              \
OutputDebugStringA(" : In Function : ");								          \
OutputDebugStringA(_FunctionName);										            \
OutputDebugStringA(" : ");												                \
OutputDebugStringA(_OutputMessage);										            \
OutputDebugStringA("\n");

#define WARNING( s )                         \
{                                            \
   std::wostringstream os_;                  \
   os_ << s;                                 \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

// Structures
struct 
SimpleVertex {
  XMFLOAT3 Pos;
  XMFLOAT2 Tex;
};

struct 
CBNeverChanges {
  XMMATRIX mView;
};

struct 
CBChangeOnResize {
  XMMATRIX mProjection;
};

struct 
CBChangesEveryFrame {
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};

enum ShaderType {
  PIXEL_SHADER = 0,
  VERTEX_SHADER = 1
};

struct Mesh {
  std::string name;
  std::vector <SimpleVertex> vertex;
  std::vector <unsigned int> index;
  int numVertex;
  int numIndex;
};

/*
 * Uso de constexpr: Permite que las funciones sean evaluadas en tiempo de compilación cuando sea posible.
 * Inicialización uniforme: Inicializa los miembros directamente en la declaración, lo que asegura que siempre tendrán valores definidos.
 * Sobrecarga de operadores: Facilita operaciones aritméticas comunes con vectores (suma, resta, multiplicación y división).
 */
struct Vector3f {
  // Constructor predeterminado
  constexpr Vector3f() = default;

  // Constructor con inicialización de componentes
  constexpr Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

  // Inicialización de los componentes
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  // Método para obtener un puntero a los datos como un arreglo
  float* data() { return &x; }
  const float* data() const { return &x; }

  // Sobrecarga del operador de suma
  constexpr Vector3f operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
  }

  // Sobrecarga del operador de resta
  constexpr Vector3f operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
  }

  // Sobrecarga del operador de multiplicación por un escalar
  constexpr Vector3f operator*(float scalar) const {
    return Vector3f(x * scalar, y * scalar, z * scalar);
  }

  // Sobrecarga del operador de división por un escalar
  constexpr Vector3f operator/(float scalar) const {
    return Vector3f(x / scalar, y / scalar, z / scalar);
  }
};

struct Vector4f {
  // Constructor predeterminado
  constexpr Vector4f() = default;

  // Constructor con inicialización de componentes
  constexpr Vector4f(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

  // Inicialización de los componentes
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float w = 0.0f;

  // Método para obtener un puntero a los datos como un arreglo
  float* data() { return &x; }
  const float* data() const { return &x; }

  // Sobrecarga del operador de suma
  constexpr Vector4f operator+(const Vector4f& other) const {
    return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  // Sobrecarga del operador de resta
  constexpr Vector4f operator-(const Vector4f& other) const {
    return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  // Sobrecarga del operador de multiplicación por un escalar
  constexpr Vector4f operator*(float scalar) const {
    return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  // Sobrecarga del operador de división por un escalar
  constexpr Vector4f operator/(float scalar) const {
    return Vector4f(x / scalar, y / scalar, z / scalar, w / scalar);
  }
};
