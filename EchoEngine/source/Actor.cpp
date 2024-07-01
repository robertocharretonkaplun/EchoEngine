#include "Actor.h"
#include "MeshComponent.h"

Actor::Actor() {
	std::shared_ptr<Transform> transform = std::make_shared<Transform>();
	addComponent(transform);
	std::shared_ptr<MeshComponent> Mesh = std::make_shared<MeshComponent>();
	addComponent(Mesh);
}
