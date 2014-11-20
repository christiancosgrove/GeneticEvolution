//
//  EvolutionSystem.h
//  GeneticEvolution
//
//  Created by Christian Cosgrove on 11/12/14.
//  Copyright (c) 2014 Test. All rights reserved.
//
#pragma once
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include<functional>
#include "SoftBodyAgent.h"
class EvolutionSystem
{
public:
    enum class RenderMode
    {
        POINT_ALL,
        WIRE_ALL,
        POINT_ONE,
        WIRE_ONE,
    } CurrentRenderMode;
    inline void NextRenderMode();
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        Vertex(glm::vec3 pos, glm::vec3 col) : position(pos), color(col) {}
        Vertex(float x, float y, float z, float r, float g, float b) : position(x,y,z), color(r,g,b) {}
    };
    EvolutionSystem(std::string _outputFileLocation);
    void Draw();
    void Update();
    const float TIME_STEP;
    const int NUM_AGENTS;
    int selectedAgent;
    inline void NextSelectedAgent();
    inline void PrevSelectedAgent();
    inline void ToggleAccelerated();
private:
    GLuint vao,vbo;
    void generateBuffers();
    void updateBuffers();
    std::vector<Vertex> vertices;
    std::vector<SoftBodyAgent*> agents;
    std::vector<std::function<float(SoftBodyAgent&)>> performanceFunctions;
    std::size_t currentFunction;
    int currentTime;
    int generationLength;
    void nextGeneration();
    void configurePerformanceFunctions();
    std::string outputFileLocation;
    bool accelerate;
    void updateAgent(SoftBodyAgent* agent);
};

void EvolutionSystem::ToggleAccelerated()
{
    accelerate=!accelerate;
}

void EvolutionSystem::NextRenderMode()
{
    switch (CurrentRenderMode)
    {
        case RenderMode::POINT_ALL:
            CurrentRenderMode=RenderMode::WIRE_ALL;
            break;
        case RenderMode::WIRE_ALL:
            CurrentRenderMode=RenderMode::POINT_ONE;
            break;
        case RenderMode::POINT_ONE:
            CurrentRenderMode=RenderMode::WIRE_ONE;
            break;
        case RenderMode::WIRE_ONE:
            CurrentRenderMode=RenderMode::POINT_ALL;
            break;
    }
}

void EvolutionSystem::NextSelectedAgent()
{
    selectedAgent++;
    if (selectedAgent>=NUM_AGENTS) selectedAgent=0;
}

void EvolutionSystem::PrevSelectedAgent()
{
    selectedAgent--;
    if (selectedAgent<0) selectedAgent=NUM_AGENTS-1;
}