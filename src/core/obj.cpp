#include <core/obj.hpp>
#include <core/engine.hpp>

#include <OBJ_Loader.h>

#include <iostream>

Core::ObjLoader::ObjLoader(
    Core::ModelType type, std::string path
){
    if(type == Core::MODEL_BWM){
        loadBwm(path);
    } else if(type == Core::MODEL_OBJ){
        loadObj(path);
    }
}

void Core::ObjLoader::loadBwm(std::string path){
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
        } else if (strcmp(lineHeader, "n") == 0){
            glm::vec3 get;
            fscanf(file, "%f %f %f\n", &get.x, &get.y, &get.z);
            normals.push_back(get.x);
            normals.push_back(get.y);
            normals.push_back(get.z);
        } else if (strcmp(lineHeader, "u") == 0){
            glm::vec2 get;
            fscanf(file, "%f %f\n", &get.x, &get.y);
            uv.push_back(get.x);
            uv.push_back(get.y);
        }
    }
}

void Core::ObjLoader::loadObj(std::string path){
    objl::Loader Loader;
	LOG(bool loadout = Loader.LoadFile(path), "INFO",
        "loading obj model");

    if(!loadout)
        throw LOG(!loadout, "ERROR", "impossible to open the file!");

    for (int i = 0; i < Loader.LoadedMeshes.size(); i++){

        objl::Mesh currentMesh = Loader.LoadedMeshes[i];

        for (int j = 0; j < currentMesh.Vertices.size(); j++){
			positions.push_back(currentMesh.Vertices[j].Position.X);
            positions.push_back(currentMesh.Vertices[j].Position.Y);
            positions.push_back(currentMesh.Vertices[j].Position.Z);

            normals.push_back(currentMesh.Vertices[j].Normal.X);
            normals.push_back(currentMesh.Vertices[j].Normal.Y);
            normals.push_back(currentMesh.Vertices[j].Normal.Z);

            uv.push_back(currentMesh.Vertices[j].TextureCoordinate.X);
            uv.push_back(currentMesh.Vertices[j].TextureCoordinate.Y);
        }

        for (int j = 0; j < currentMesh.Indices.size(); j += 3){
            indices.push_back(currentMesh.Indices[j]);
            indices.push_back(currentMesh.Indices[j + 1]);
            indices.push_back(currentMesh.Indices[j + 2]);
        }

    }
}