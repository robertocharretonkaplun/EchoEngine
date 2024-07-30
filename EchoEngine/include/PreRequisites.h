#pragma once
// Librerias STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
//#include <memory>
#include <thread>

// Librerias DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"

// Third Parties
#include "Utilities/Memory/TSharedPointer.h"
#include "Utilities/Memory/TWeakPointer.h"

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

enum ExtensionType {
  DDS = 0,
  PNG = 1,
  JPG = 2
};

// DEPRECATED
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

/*
struct Vector3f {
  // Constructor predeterminado
  // Inicializa los componentes del vector a 0
  constexpr Vector3f() = default;

  // Constructor con inicialización de componentes
  // @param _x: Componente en el eje X
  // @param _y: Componente en el eje Y
  // @param _z: Componente en el eje Z
  constexpr Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

  // Variables miembro que representan los componentes del vector
  float x = 0.0f;  // Componente en el eje X
  float y = 0.0f;  // Componente en el eje Y
  float z = 0.0f;  // Componente en el eje Z

  // Método para obtener un puntero a los datos como un arreglo
  // @return: Puntero a los componentes del vector
  float* data() { return &x; }
  const float* data() const { return &x; }

  // Sobrecarga del operador de suma
  // @param other: Otro vector a sumar
  // @return: Resultado de la suma de los vectores
  constexpr Vector3f operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
  }

  // Sobrecarga del operador de resta
  // @param other: Otro vector a restar
  // @return: Resultado de la resta de los vectores
  constexpr Vector3f operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
  }

  // Sobrecarga del operador de multiplicación por un escalar
  // @param scalar: Escalar por el cual multiplicar el vector
  // @return: Resultado de la multiplicación del vector por el escalar
  constexpr Vector3f operator*(float scalar) const {
    return Vector3f(x * scalar, y * scalar, z * scalar);
  }

  // Sobrecarga del operador de división por un escalar
  // @param scalar: Escalar por el cual dividir el vector
  // @return: Resultado de la división del vector por el escalar
  constexpr Vector3f operator/(float scalar) const {
    return Vector3f(x / scalar, y / scalar, z / scalar);
  }
};

struct Vector4f {
  // Constructor predeterminado
  // Inicializa los componentes del vector a 0
  constexpr Vector4f() = default;

  // Constructor con inicialización de componentes
  // @param _x: Componente en el eje X
  // @param _y: Componente en el eje Y
  // @param _z: Componente en el eje Z
  // @param _w: Componente en el eje W
  constexpr Vector4f(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

  // Variables miembro que representan los componentes del vector
  float x = 0.0f;  // Componente en el eje X
  float y = 0.0f;  // Componente en el eje Y
  float z = 0.0f;  // Componente en el eje Z
  float w = 0.0f;  // Componente en el eje W

  // Método para obtener un puntero a los datos como un arreglo
  // @return: Puntero a los componentes del vector
  float* data() { return &x; }
  const float* data() const { return &x; }

  // Sobrecarga del operador de suma
  // @param other: Otro vector a sumar
  // @return: Resultado de la suma de los vectores
  constexpr Vector4f operator+(const Vector4f& other) const {
    return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  // Sobrecarga del operador de resta
  // @param other: Otro vector a restar
  // @return: Resultado de la resta de los vectores
  constexpr Vector4f operator-(const Vector4f& other) const {
    return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  // Sobrecarga del operador de multiplicación por un escalar
  // @param scalar: Escalar por el cual multiplicar el vector
  // @return: Resultado de la multiplicación del vector por el escalar
  constexpr Vector4f operator*(float scalar) const {
    return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  // Sobrecarga del operador de división por un escalar
  // @param scalar: Escalar por el cual dividir el vector
  // @return: Resultado de la división del vector por el escalar
  constexpr Vector4f operator/(float scalar) const {
    return Vector4f(x / scalar, y / scalar, z / scalar, w / scalar);
  }
};

*/