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

void EntityManager::Update(float deltaTime)
{
    for (auto& entity: entities) 
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render()
{
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; ++layerNumber)
    {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
        {
            entity->Render();
        }
    }
}

bool EntityManager::HasNoEntities()
{
    return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer)
{
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity); //emplace_back is the same as push, adds entity to end of vector list
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity*> selectedEntities; 
    
    for (auto& entity : entities)
    {
        if (entity->layer == layer)
        {
            selectedEntities.emplace_back(entity);
        }
    }

    return selectedEntities;
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