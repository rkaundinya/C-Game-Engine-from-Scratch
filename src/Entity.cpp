#include "./Entity.h"

Entity::Entity(EntityManager& manager): entityManager(manager) 
{
    this->isActive = true; 
}

Entity::Entity(EntityManager& manager, std::string name): 
    entityManager(manager), entityName(name)
{
    this->isActive = true; 
}

/* std::string Entity::print()
{
    std::cout << "Entity name: " << entityName << std::endl;
    //std::cout << 
} */

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