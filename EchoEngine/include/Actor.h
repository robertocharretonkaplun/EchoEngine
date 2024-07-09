#pragma once
#include "PreRequisites.h"
#include "Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SamplerState.h"
class Device;
class MeshComponent;

class Actor : public Entity
{
public:
	Actor() = default;
	Actor(Device device);
	virtual ~Actor() = default;

	void 
	update(float deltaTime, DeviceContext deviceContext) override;
	
	void 
	render(DeviceContext deviceContext) override;

	void
	destroy();

	template <typename T>
	std::shared_ptr<T> getComponent();

	void 
	setMesh(Device device, std::vector<MeshComponent> meshes);

	void
	setTextures(std::vector<Texture> textures);

	std::string 
	getName() { return m_name; }
private:
	std::vector<MeshComponent> m_meshes;
	std::vector<Texture> m_textures;

	SamplerState m_sampler;
	std::vector<Buffer>                 m_vertexBuffers;
	std::vector<Buffer>                 m_indexBuffers;
	Buffer															m_modelBuffer;
	CBChangesEveryFrame model;
	std::string m_name= "Actor";
};

template<typename T>
inline std::shared_ptr<T>
Actor::getComponent()
{
	for (auto& component : components) {
		std::shared_ptr<T> specificComponent = std::dynamic_pointer_cast<T>(component);
		if (specificComponent) {
			return specificComponent;
		}
	}
	return nullptr;
}
