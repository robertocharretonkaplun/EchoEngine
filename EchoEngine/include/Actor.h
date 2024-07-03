#pragma once
#include "PreRequisites.h"
#include "Entity.h"

class MeshComponent;

class Actor : public Entity
{
public:
	Actor();
	virtual ~Actor() = default;

	void 
	update(float deltaTime) override;
	
	void 
	render(DeviceContext deviceContext) override;

	template <typename T>
	std::shared_ptr<T> getComponent();


private:

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
