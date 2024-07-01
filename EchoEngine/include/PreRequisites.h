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

struct
Vector3f {
  Vector3f() = default;
  Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
};

struct
Vector4f {
  Vector4f(float _x, float _y, float _z, float _w ) : x(_x), y(_y), z(_z), w(_w) {}
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float w = 0.0f;
};

