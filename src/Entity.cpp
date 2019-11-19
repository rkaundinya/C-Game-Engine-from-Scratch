#include <iostream>
#include "./Entity.h"

Entity::Entity(EntityManager& manager): entityManager(manager) 
{
    this->isActive = true; 
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer): 
    entityManager(manager), entityName(name), layer(layer)
{
    this->isActive = true; 
}

void Entity::Update(float deltaTime)
{
    for (auto& component:components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render() 
{
    for (auto& component: components)
    {
        component->Render();
    }
}

void Entity::Destroy() 
{
    this->isActive = false;
}

bool Entity::IsActive() const{
    return this->isActive; 
}

void Entity::ListAllComponents() const
{
    for (auto mapElement: componentTypeMap)
    {
        std::cout << "Component<" << mapElement.first->name() << ">" << std::endl;
    }
}