#include "./EntityManager.h"

/* void EntityManager::print()
{
    for (auto& entity: entities)
    {
        entity->print();
    }
} */

void EntityManager::ClearData()
{
    for (auto& entity: entities)
    {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities()
{
    return entities.size() == 0;
}

void EntityManager::Update(float deltaTime)
{
    for (auto& entity: entities) 
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render()
{
    for (auto& entity: entities)
    {
        entity->Render();
    }
}

Entity& EntityManager::AddEntity(std::string entityName)
{
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity); //emplace_back is the same as push, adds entity to end of vector list
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
    return entities;
}

unsigned int EntityManager::GetEntityCount()
{
    return entities.size();
}

void EntityManager::ListAllEntities() const
{
    unsigned int i = 0;
    for (auto& entity: entities)
    {
        std::cout << "Entity[" << i << "]: " << entity->entityName << std::endl;
        entity->ListAllComponents();
        i++;
    }
}