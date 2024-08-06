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

class Device;
class DeviceContext;

class 
Texture {
public:
	Texture() = default;
	~Texture() = default;

	/// <summary>
	/// Brief: Crea una textura a partir de una imagen (.dds) desde nuestro ordenador.
	/// </summary>
	/// <param name="device">: Llamamos al device para poder generar los recursos en memoria. </param>
	/// <param name="textureName">: Almacenamos el nombre de la textura, para cargala desde memoria. </param>
  HRESULT
  init(Device device,
    std::string textureName,
    ExtensionType extensionType);

	/// <summary>
  /// Brief: This method is responsible for creating a 2D Texture from the data provided
  /// by the developer.
  /// </summary>
  /// <param name="device">: It is in charge of providing the resources to create the 2D texture.</param>
  /// <param name="width">: It will take the width of our window.</param>
  /// <param name="height">: It will take the height of our window.</param>
  /// <param name="Format">: It is a classifier that will allow bit spaces to be created correctly in memory.</param>
  /// <param name="BindFlags">: It is a characteristic to classify the type of texture that is being created.</param>
  void
  init(Device device,
       unsigned int width, 
       unsigned int height, 
       DXGI_FORMAT Format, 
       unsigned int BindFlags);

  /// <summary>
  /// Brief: This method is in charge of updating the logic of the texture
  /// </summary>
  void
  update();

  
  /// <summary>
  /// Brief: This method is in charge of drawing the resources on the screen. (only if necessary)
  /// </summary>
  /// <param name="deviceContext">: It is in charge of assigning resources to be used.</param>
  /// <param name="StartSlot">: It is in charge of assigning the starting point in memory. 
  /// We recommend checking that it is not spliced ??in memory with other resources.</param>
  void 
  render(DeviceContext & deviceContext, unsigned int StartSlot, unsigned int NumViews);

  /// <summary>
  /// Brief: This method is in charge of releasing the resources stored in the class's memory.
  /// </summary>
  void 
  destroy();
  

public:
  // This variable is in charge of handle a texture resource as data
  ID3D11Texture2D* m_texture = nullptr;
  // This variable is in charge of handle a texture resource as image data
  ID3D11ShaderResourceView* m_textureFromImg;
};