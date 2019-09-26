#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Components/TransformComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game() 
{
    this->isRunning = false;
}

Game::~Game()
{}

bool Game::IsRunning() const 
{
    return this->isRunning;
}

void Game::Initialize(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initilializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    
    if (!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    // -1 below means get the default driver for renderer, 0 means don't set any flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    
    if (!renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber)
{
    // Add entities and add components to the entities
    Entity& newEntity(manager.AddEntity("projectile"));
    newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    //manager.print();

    /* Entity& newEntity2(manager.AddEntity("projectile 2"));
    newEntity2.AddComponent<TransformComponent>(30, 0, 20, 20, 32, 32, 1); */
}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT: 
        {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
        }
        default: 
        {
            break;
        }
    }
}

void Game::Update()
{
    // Wait until 16ms has elapsed since last frame - 16 b/c fps is 60
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp delta time to a maximum value so it doesn't get arbitrarily large
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks fro the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    // Here we call the manager.update to update all entities as a function of deltatime
    manager.Update(deltaTime);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // TODO:
    // Here we call the manager.render to render all entities
    if (manager.HasNoEntities())
    {
        return; 
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}