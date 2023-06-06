#include <core/obj.hpp>
#include <core/engine.hpp>

#include <iostream>

Core::ObjLoader::ObjLoader(
    std::string path
){
    FILE * file = fopen(path.c_str(), "r");
    if(file == NULL){
        throw LOG(fopen(path.c_str(), "r"), "ERROR", "impossible to open the file!");
    }

    while(true){
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "p") == 0){
            glm::vec3 get;
            fscanf(file, "%f %f %f\n", &get.x, &get.y, &get.z);
            positions.push_back(get.x);
            positions.push_back(get.y);
            positions.push_back(get.z);
        } else if (strcmp(lineHeader, "i") == 0){
            glm::vec3 get;
            fscanf(file, "%f %f %f\n", &get.x, &get.y, &get.z);
            indices.push_back(get.x);
            indices.push_back(get.y);
            indices.push_back(get.z);
        } else if (strcmp(lineHeader, "c") == 0){
            glm::vec4 get;
            fscanf(file, "%f %f %f %f\n", &get.x, &get.y, &get.z, &get.w);
            colors.push_back(get.x);
            colors.push_back(get.y);
            colors.push_back(get.z);
            colors.push_back(get.w);
        } else if (strcmp(lineHeader, "u") == 0){
            glm::vec2 get;
            fscanf(file, "%f %f\n", &get.x, &get.y);
            uv.push_back(get.x);
            uv.push_back(get.y);
        }
    }
}