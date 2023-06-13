#include <core/engine.hpp>
#include <render/light.hpp>

std::vector<Render::DirectionalLight*> Render::lights;

Render::DirectionalLight::DirectionalLight(
    glm::vec3 lightColor, float ambientStrength,
    float specularStrength
){
    Render::lights.push_back(this);
    this->ambientStrength = ambientStrength;
    this->specularStrength = specularStrength;
    this->lightColor = lightColor;
}