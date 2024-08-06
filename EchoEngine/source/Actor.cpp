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
#include "Actor.h"
#include "MeshComponent.h"
#include "Device.h"

Actor::Actor(Device device) {
	std::shared_ptr<Transform> transform = std::make_shared<Transform>();
	addComponent(transform);
	std::shared_ptr<MeshComponent> Mesh = std::make_shared<MeshComponent>();
	addComponent(Mesh);

	m_modelBuffer.init(device, sizeof(CBChangesEveryFrame));
	m_sampler.init(device);
}

void 
Actor::update(float deltaTime, DeviceContext deviceContext) {

	getComponent<Transform>()->update(deltaTime);

	model.mWorld = XMMatrixTranspose(getComponent<Transform>()->matrix);
	model.vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	m_modelBuffer.update(deviceContext, 0, nullptr, &model, 0, 0);

}

void 
Actor::render(DeviceContext deviceContext) {
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_vertexBuffers[i].render(deviceContext, 0, 1);
		m_indexBuffers[i].render(deviceContext, DXGI_FORMAT_R32_UINT);
		if (m_textures.size() > 0)
		{
			if (i <= m_textures.size() - 1)
			{
				m_textures[i].render(deviceContext, 0, 1);
			}
			else {
				//m_default.render(deviceContext, 0, 1);
			}
		}
		m_sampler.render(deviceContext, 0, 1);
		m_modelBuffer.renderModel(deviceContext, 2, 1);
		
		deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext.m_deviceContext->DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
	}
}

void 
Actor::destroy() {

	for (auto& vertexBuffer : m_vertexBuffers) {
		vertexBuffer.destroy();
	}

	for (auto& indexBuffer : m_indexBuffers) {
		indexBuffer.destroy();
	}

	for (auto& tex : m_textures) {
		tex.destroy();
	}
	m_modelBuffer.destroy();

	m_sampler.destroy();
}

void 
Actor::setMesh(Device device, std::vector<MeshComponent> meshes) {
	m_meshes = meshes;

	for (auto& mesh : m_meshes) {
		// Crear vertex buffer
		Buffer vertexBuffer;
		vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
		m_vertexBuffers.push_back(vertexBuffer);

		// Crear index buffer
		Buffer indexBuffer;
		indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
		m_indexBuffers.push_back(indexBuffer);
	}
}

void
Actor::setTextures(std::vector<Texture> textures) {
	m_textures = textures;
}