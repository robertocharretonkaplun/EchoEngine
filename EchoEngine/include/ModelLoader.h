#pragma once
#include "PreRequisites.h"
#include "fbxsdk.h"
#include "MeshComponent.h"

class 
ModelLoader {
public:
  ModelLoader();
  ~ModelLoader();

  bool 
  LoadModel(const std::string& filePath);

  const std::vector<SimpleVertex>& 
  GetVertices() const { return vertices; }

  const std::vector<uint32_t>& 
  GetIndices() const { return indices; }

  std::vector<std::string> 
  GetTextureFileNames() const { return textureFileNames; }



  void 
  ProcessNode(FbxNode* node);

  void 
  ProcessMesh(FbxNode* node);

  void 
  ProcessMaterials(FbxSurfaceMaterial* material);

private:
  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<SimpleVertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<std::string> textureFileNames;
public:
  std::vector<MeshComponent> meshes;

};
