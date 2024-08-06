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
